include_guard(GLOBAL)
find_package(PkgConfig REQUIRED)

function(dream_enable_alsa target)
    find_package(ALSA REQUIRED)

    target_compile_definitions(${target} PRIVATE USE_ALSA)

    target_sources(${target} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/linux/alsain.cpp
        ${CMAKE_SOURCE_DIR}/src/linux/alsaout.cpp
        ${CMAKE_SOURCE_DIR}/src/linux/alsacommon.cpp
    )

    target_include_directories(${target} PRIVATE ${ALSA_INCLUDE_DIRS})
    target_link_libraries(${target} PRIVATE ${ALSA_LIBRARIES})

    message(STATUS "Audio backend: ALSA enabled")
endfunction()

function(dream_enable_portaudio target)
    pkg_check_modules(PORTAUDIO REQUIRED portaudio-2.0)

    target_compile_definitions(${target} PRIVATE USE_PORTAUDIO)

    target_sources(${target} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/sound/drm_portaudio.cpp
        ${CMAKE_SOURCE_DIR}/src/sound/pa_ringbuffer.c
    )

    target_include_directories(${target} PRIVATE ${PORTAUDIO_INCLUDE_DIRS})
    target_link_libraries(${target} PRIVATE ${PORTAUDIO_LIBRARIES})

    message(STATUS "Audio backend: PortAudio enabled")
endfunction()

function(dream_enable_pulseaudio target)
    pkg_check_modules(PULSE REQUIRED libpulse)

    target_compile_definitions(${target} PRIVATE USE_PULSEAUDIO)

    target_sources(${target} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/sound/drm_pulseaudio.cpp
    )

    target_include_directories(${target} PRIVATE ${PULSE_INCLUDE_DIRS})
    target_link_libraries(${target} PRIVATE ${PULSE_LIBRARIES})

    message(STATUS "Audio backend: PulseAudio enabled")
endfunction()

function(dream_enable_soapy target)
    find_package(SoapySDR REQUIRED)

    target_compile_definitions(${target} PRIVATE USE_SOAPYSDR)

    target_sources(${target} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/sound/drm_soapySDR.cpp
    )

    target_link_libraries(${target} PRIVATE SoapySDR::SoapySDR)

    message(STATUS "SDR backend: SoapySDR enabled")
endfunction()

function(dream_enable_jack target)
    pkg_check_modules(JACK REQUIRED jack)

    target_compile_definitions(${target} PRIVATE USE_JACK)

    target_sources(${target} PRIVATE
        ${CMAKE_SOURCE_DIR}/src/sound/jack.cpp
    )

    target_include_directories(${target} PRIVATE ${JACK_INCLUDE_DIRS})
    target_link_libraries(${target} PRIVATE ${JACK_LIBRARIES})

    message(WARNING "JACK backend enabled, but JACK is known to be unstable")
endfunction()

function(dream_configure_backend target)
    if(ENABLE_ALSA)
        dream_enable_alsa(${target})
    endif()

    if(ENABLE_PORTAUDIO)
        dream_enable_portaudio(${target})
    endif()

    if(ENABLE_PULSEAUDIO)
        dream_enable_pulseaudio(${target})
    endif()

    if(ENABLE_SOAPYSDR)
        dream_enable_soapy(${target})
    endif()    
    
    if(ENABLE_JACK)
        dream_enable_jack(${target})
    endif()

    # Safety check
if(NOT ENABLE_ALSA AND NOT ENABLE_PORTAUDIO AND
   NOT ENABLE_PULSEAUDIO AND NOT ENABLE_SOAPYSDR AND
   NOT ENABLE_JACK)
    message(FATAL_ERROR "No audio backend enabled")
endif()
endfunction()

