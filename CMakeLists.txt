cmake_minimum_required(VERSION 3.16)
project(dream LANGUAGES C CXX)
set(PROJECT_NAME dream)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)


option(USE_QT "Enable Qt support" ON)
set(QT_MAJOR_VERSION 6 CACHE STRING "Prefer Qt major version (5 or 6). Used to select find_package behaviour")
option(CONSOLE "Build console (non-GUI) target" OFF)
option(QTCONSOLE "Build Qt console (CLI with some Qt) target" OFF)
option(CROSS_COMPILE "Cross-compile build (affects some platform checks and messages)" OFF)

# Defaults
option(ENABLE_FDK_AAC "Enable fdk-aac" OFF)
option(ENABLE_OPUS "Enable opus" OFF)
option(ENABLE_SNDFILE "Enable libsndfile" OFF)
option(ENABLE_SPEEXDSP "Enable speexdsp" OFF)
option(ENABLE_GPS "Enable libgps" OFF)
option(ENABLE_HAMLIB "Enable hamlib" OFF)
option(ENABLE_QWT "Enable Qwt support" OFF)
option(ENABLE_ALSA "Enable ALSA support" OFF)
option(ENABLE_PORTAUDIO "Enable PortAudio support" OFF)
option(ENABLE_PULSEAUDIO "Enable PulseAudio support" OFF)
option(ENABLE_SOAPYSDR "Enable SoapySDR support" OFF)
option(ENABLE_JACK "Enable JACK support" OFF)
if(NOT USE_QT)
    set(CONSOLE ON)
endif()


list(APPEND INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")
list(APPEND INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/src")

# not ideal, but works
add_compile_definitions(EXECUTABLE_NAME=${PROJECT_NAME})
add_compile_definitions(QT_DISABLE_DEPRECATED_UP_TO=0x060700)
add_compile_definitions(WARN_ON)

# GLOB_RECURSE includes EVERYTHING by default.
# We have to remove every single ENABLE_ and USE_QT include first.
# needed for ENABLE_ compatibility

# Exclude the optional modules by default:
set(OPTIONAL_MODULES
    jack
    shmsoundin
    drm_portaudio
    drm_pulseaudio
    drm_soapySDR
    fdk_aac_codec
    alsain
    alsaout
    alsacommon
    pa_ringbuffer
    Pacer
    ConsoleIO
)

function(filter_optional MODULE_LIST)
    foreach(MODULE IN LISTS MODULE_LIST)
        if(MODULE STREQUAL "jack" OR MODULE STREQUAL "shmsoundin")
            if(ENABLE_JACK)
                continue()
            endif()
        endif()
        list(FILTER SOURCE_FILES  EXCLUDE REGEX ".*/${MODULE}\\.cpp$")
        list(FILTER HEADER_FILES  EXCLUDE REGEX ".*/${MODULE}\\.h$")
        list(FILTER SOURCE_FILES  EXCLUDE REGEX ".*/${MODULE}\\.c$")
    endforeach()
    # push changes to parent scope
    set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
    set(HEADER_FILES ${HEADER_FILES} PARENT_SCOPE)
endfunction()

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
)



# linking issue when multiple main.cpp files are included
list(REMOVE_ITEM SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/main-Qt/main.cpp
    ${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp
)
filter_optional("${OPTIONAL_MODULES}")

# Remove all GUI files, they should only be added if USE_QT is ON
function(filter_gui_files)
    foreach(DIR IN ITEMS "GUI-QT" "main-Qt" "util-QT")
        list(FILTER SOURCE_FILES EXCLUDE REGEX ".*/${DIR}/.*")
        list(FILTER HEADER_FILES EXCLUDE REGEX ".*/${DIR}/.*")
    endforeach()
endfunction()

filter_gui_files()

if(UNIX)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/linux/Pacer.cpp)
    add_compile_definitions(HAVE_DLFCN_H HAVE_MEMORY_H HAVE_STDINT_H HAVE_STDLIB_H
                            HAVE_STRINGS_H HAVE_STRING_H STDC_HEADERS
                            HAVE_INTTYPES_H HAVE_SYS_STAT_H HAVE_SYS_TYPES_H HAVE_UNISTD_H
                            HAVE_LIBZ)
    list(APPEND CMAKE_REQUIRED_LIBRARIES dl rt)
    list(APPEND EXTRA_LIBS "-lfftw3" "-lz")
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "linux")
    list(APPEND EXTRA_LIBS "-ldl" "-lrt")
endif()


# If Qt GUI support is enabled, add GUI-specific sources & forms
set(FORMS "")
set(GUI_HEADERS "")
set(GUI_SOURCES "")
set(RESOURCES "")
if(USE_QT)

    list(APPEND RESOURCES src/GUI-QT/res/icons.qrc)
    list(APPEND INCLUDE_DIRS
        "${CMAKE_SOURCE_DIR}/src/GUI-QT"
        "${CMAKE_SOURCE_DIR}/src/util-QT"
        "${CMAKE_SOURCE_DIR}/src/main-Qt"
    )
    # BWS and Rig is handled separately.
    file(GLOB FORMS_GLOB "${CMAKE_SOURCE_DIR}/src/GUI-QT/*.ui")
    list(REMOVE_ITEM FORMS_GLOB
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.ui"
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.ui"
    )
    list(APPEND FORMS ${FORMS_GLOB})


    file(GLOB GUI_HEADERS_GLOB "${CMAKE_SOURCE_DIR}/src/GUI-QT/*.h")
    list(REMOVE_ITEM GUI_HEADERS_GLOB
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.h"
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.h"
    )
    list(APPEND GUI_HEADERS ${GUI_HEADERS_GLOB})
    
    file(GLOB GUI_SOURCES_GLOB
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/*.cpp"
    )
    list(REMOVE_ITEM GUI_SOURCES_GLOB
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.cpp"
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.cpp"
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp"
    )
    list(APPEND GUI_SOURCES ${GUI_SOURCES_GLOB})
    
    file(GLOB UTIL_HEADERS_GLOB "${CMAKE_SOURCE_DIR}/src/util-QT/*.h")
    list(REMOVE_ITEM UTIL_HEADERS_GLOB "${CMAKE_SOURCE_DIR}/src/util-QT/Rig.h")
    list(APPEND GUI_HEADERS ${UTIL_HEADERS_GLOB})
    
    file(GLOB UTIL_SOURCES_GLOB "${CMAKE_SOURCE_DIR}/src/util-QT/*.cpp")
    list(REMOVE_ITEM UTIL_SOURCES_GLOB "${CMAKE_SOURCE_DIR}/src/util-QT/Rig.cpp")
    list(APPEND GUI_SOURCES ${UTIL_SOURCES_GLOB})
    
    file(GLOB MAINQT_HEADERS_GLOB "${CMAKE_SOURCE_DIR}/src/main-Qt/*.h")
    list(APPEND GUI_HEADERS ${MAINQT_HEADERS_GLOB})
    
    file(GLOB MAINQT_SOURCES_GLOB "${CMAKE_SOURCE_DIR}/src/main-Qt/*.cpp")
    list(REMOVE_ITEM MAINQT_SOURCES_GLOB "${CMAKE_SOURCE_DIR}/src/main-Qt/main.cpp")
    list(APPEND GUI_SOURCES ${MAINQT_SOURCES_GLOB})
    
    
    list(APPEND SOURCE_FILES ${GUI_SOURCES})
    list(APPEND HEADER_FILES ${GUI_HEADERS})
endif()

if(CONSOLE)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
    list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp)
    # unix:!cross_compile extras
    if(UNIX AND NOT CROSS_COMPILE)
        list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/linux/ConsoleIO.h)
        list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/linux/ConsoleIO.cpp)
        list(APPEND EXTRA_LIBS "-lpthread")
        message(STATUS "Building with terminal user interface (console)")
    endif()
endif()

# Qt console (uses Qt but without GUI)
if(QTCONSOLE)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main-Qt/main.cpp)
    list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp)
    if(UNIX AND NOT CROSS_COMPILE)
        list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/linux/ConsoleIO.h)
        list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/linux/ConsoleIO.cpp)
        message(STATUS "Building Qt console with terminal user interface")
    endif()
endif()

# GUI main (default)
if(NOT CONSOLE AND NOT QTCONSOLE)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp)
endif()
#Optional features (fdk-aac, opus, sndfile, speexdsp, gps, hamlib)
if(ENABLE_FDK_AAC)
    add_compile_definitions(HAVE_LIBFDK_AAC HAVE_USAC)
    list(APPEND EXTRA_LIBS -L/usr/lib64/fdk-aac -lfdk-aac)
    list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/sourcedecoders/fdk_aac_codec.h)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/sourcedecoders/fdk_aac_codec.cpp)
    message(STATUS "with fdk-aac")
endif()

if(ENABLE_OPUS)
    add_compile_definitions(HAVE_LIBOPUS)
    if(UNIX)
        list(APPEND EXTRA_LIBS "-lopus")
    endif()
    message(STATUS "with opus")
endif()

if(ENABLE_SNDFILE)
    add_compile_definitions(HAVE_LIBSNDFILE)
    if(UNIX)
        list(APPEND EXTRA_LIBS sndfile)
    endif()
    message(STATUS "with libsndfile")
endif()

if(ENABLE_SPEEXDSP)
    add_compile_definitions(HAVE_SPEEX)
    list(APPEND EXTRA_LIBS "-lspeexdsp")
    message(STATUS "with speexdsp")
endif()


if(ENABLE_HAMLIB)
    add_compile_definitions(HAVE_LIBHAMLIB)
    if(UNIX)
        list(APPEND EXTRA_LIBS "-lhamlib")
    endif()
    # Remove in case already present
    list(REMOVE_ITEM HEADER_FILES ${CMAKE_SOURCE_DIR}/src/util/Hamlib.h)
    list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/util/Hamlib.cpp)
    list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/util/Hamlib.h)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/util/Hamlib.cpp)
    if(USE_QT)
        list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/util-QT/Rig.h)
        list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/util-QT/Rig.cpp)
    endif()
    if(USE_QT)
        list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.h)
        list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.cpp)
        list(APPEND FORMS ${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.ui)
    endif()
    message(STATUS "with hamlib")
endif()



if(ENABLE_ALSA)
    add_compile_definitions(USE_ALSA)
    list(APPEND HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/linux/alsain.h
        ${CMAKE_SOURCE_DIR}/src/linux/alsaout.h
        ${CMAKE_SOURCE_DIR}/src/linux/alsacommon.h
    )
    list(APPEND SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/linux/alsain.cpp
        ${CMAKE_SOURCE_DIR}/src/linux/alsaout.cpp
        ${CMAKE_SOURCE_DIR}/src/linux/alsacommon.cpp
    )
    list(APPEND EXTRA_LIBS "-lasound")
    message(STATUS "with alsa")
endif()

if(ENABLE_PORTAUDIO)
    add_compile_definitions(USE_PORTAUDIO)
    list(APPEND HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/sound/pa_ringbuffer.h
        ${CMAKE_SOURCE_DIR}/src/sound/drm_portaudio.h
    )
    list(APPEND SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/sound/drm_portaudio.cpp
        ${CMAKE_SOURCE_DIR}/src/sound/pa_ringbuffer.c
    )
    list(APPEND EXTRA_LIBS "-lportaudio")
    message(STATUS "with portaudio")
endif()

if(ENABLE_PULSEAUDIO)
    add_compile_definitions(USE_PULSEAUDIO)
    list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/sound/drm_pulseaudio.h)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/sound/drm_pulseaudio.cpp)
    if(UNIX)
        # bugfix
        # prefer pkg-config libpulse; fallback to -lpulse
        find_package(PkgConfig QUIET)
        if(PKG_CONFIG_FOUND)
            pkg_check_modules(LIBPULSE libpulse QUIET)
            if(LIBPULSE_FOUND)
                list(APPEND EXTRA_LIBS ${LIBPULSE_LIBRARIES})
                list(APPEND INCLUDE_DIRS ${LIBPULSE_INCLUDE_DIRS})
            else()
                list(APPEND EXTRA_LIBS "-lpulse")
            endif()
        else()
            list(APPEND EXTRA_LIBS "-lpulse")
        endif()
    else()
        list(APPEND EXTRA_LIBS "-lpulse")
    endif()
    message(STATUS "with pulseaudio")
endif()

if(ENABLE_SOAPYSDR)
    add_compile_definitions(USE_SOAPYSDR)
    list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/sound/drm_soapySDR.h)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/sound/drm_soapySDR.cpp)

    find_package(PkgConfig QUIET)
    if(PKG_CONFIG_FOUND)
        pkg_check_modules(SOAPYSDR SoapySDR QUIET)
        if(SOAPYSDR_FOUND)
            list(APPEND EXTRA_LIBS ${SOAPYSDR_LIBRARIES})
            list(APPEND INCLUDE_DIRS ${SOAPYSDR_INCLUDE_DIRS})
        else()
            list(APPEND EXTRA_LIBS "-lSoapySDR")
        endif()
    else()
        list(APPEND EXTRA_LIBS "-lSoapySDR")
    endif()

    message(STATUS "with SoapySDR")
endif()

include_directories(${INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

set(ALL_SOURCES ${SOURCE_FILES})
set(ALL_HEADERS ${HEADER_FILES})


add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${RESOURCES})
# Make sure the compiler can find generated ui_*.h files
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/dream_autogen/include
)
# Hardening
target_compile_options(${PROJECT_NAME} PRIVATE
    -fstack-protector-strong
    -fstack-clash-protection
    -D_FORTIFY_SOURCE=2
    -D_GLIBCXX_ASSERTIONS
    -fstrict-flex-arrays=3
    -fPIE
    -pthread
)

target_link_options(${PROJECT_NAME} PRIVATE
    -pie
    -Wl,-z,relro
    -Wl,-z,now
    -Wl,-z,nodlopen
    -Wl,-z,noexecstack
    -Wl,--as-needed
    -Wl,--no-copy-dt-needed-entries
    -pthread
)


# Bugfix: GPS and Qwt must be after add_executable
if(ENABLE_GPS)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_LIBGPS)
    if(UNIX)
        target_link_libraries(${PROJECT_NAME} PRIVATE gps)
    endif()
    message(STATUS "with gps")
endif()

if(ENABLE_QWT)
    find_path(QWT_INCLUDE_DIR qwt_dial.h
              PATHS /usr/include /usr/include/qt6 /usr/include/qwt /usr/include/qt6/qwt)

    find_library(QWT_LIB qwt-qt6 qwt)

    if(QWT_INCLUDE_DIR)
        target_include_directories(${PROJECT_NAME} PRIVATE ${QWT_INCLUDE_DIR})
    endif()

    if(QWT_LIB)
        target_link_libraries(${PROJECT_NAME} PRIVATE ${QWT_LIB})
    endif()
endif()

foreach(LK IN LISTS EXTRA_LIBS)

    #if(LK MATCHES "^-l" OR LK MATCHES "^-L" OR LK MATCHES "^-Wl,")
    #bugfix
    #not the best way to handle this, might rewrite this entirely with two or three lists
    if(LK MATCHES "^-Wl,")
        target_link_options(${PROJECT_NAME} PRIVATE "${LK}")
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE ${LK})
    endif()
endforeach()
if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl rt)
endif()

if(UNIX AND NOT CROSS_COMPILE)
    if(DEFINED ENABLE_LIBPCAP)
        target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_LIBPCAP)
        find_library(PCAP_LIB pcap)
        if(PCAP_LIB)
            target_link_libraries(${PROJECT_NAME} PRIVATE ${PCAP_LIB})
        else()
            # fallback to -lpcap
            target_link_options(${PROJECT_NAME} PRIVATE "-lpcap")
        endif()
    endif()
endif()

# try to find Qt6
if(USE_QT)
    if(QT_MAJOR_VERSION STREQUAL "6")
        find_package(Qt6 COMPONENTS Core Widgets Network Xml Svg WebEngineWidgets Gui REQUIRED QUIET)
        if(Qt6_FOUND)
            message(STATUS "Qt6 found")
            # bugfix
            # Link required components (some configurations might not need all components; link if found)
            if(TARGET Qt6::Widgets)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
            endif()
            if(TARGET Qt6::Network)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)
            endif()
            if(TARGET Qt6::Xml)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Xml)
            endif()
            if(TARGET Qt6::Svg)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Svg)
            endif()
            if(TARGET Qt6::WebEngineWidgets)
                # if webenginewidgets available, add BWSViewer UI/sources as in .pro
                list(APPEND FORMS ${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.ui)
                list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.h)
                list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.cpp)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::WebEngineWidgets)
                message(STATUS "with BWS (Qt WebEngineWidgets)")
            endif()
            # Qt resource & UI handling
	qt_standard_project_setup()

	qt_add_resources(${PROJECT_NAME} "resources"
	    PREFIX "/"
	    FILES ${RESOURCES}
	)
# bugfix for linking issue
	target_sources(${PROJECT_NAME} PRIVATE ${QT_FORMS})
        endif()
    else()
        # Try Qt5
        message(FATAL_ERROR "Qt6 not found!!!")
    endif()
endif()

if(UNIX)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/bin)
    if(EXISTS "${CMAKE_SOURCE_DIR}/linux/dream.1")
        install(FILES "${CMAKE_SOURCE_DIR}/linux/dream.1" DESTINATION /usr/share/man/man1)
    endif()
endif()

# qmake type messages
if(USE_QT)
    message(STATUS "Qt modules enabled")
else()
    message(STATUS "No Qt (console mode)")
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
if(CONSOLE)
    message(STATUS "UI: console mode")
elseif(QTCONSOLE)
    message(STATUS "UI: qtconsole mode")
else()
    message(STATUS "UI: GUI mode")
endif()

if(NOT ENABLE_PULSEAUDIO AND NOT ENABLE_PORTAUDIO AND NOT ENABLE_ALSA AND NOT ENABLE_SOAPYSDR)
    message(WARNING "No usable audio interface configured (pulseaudio/portaudio/alsa/SoapySDR). Set ENABLE_PULSEAUDIO or ENABLE_PORTAUDIO or ENABLE_ALSA or ENABLE_SOAPYSDR.")
    # In the original .pro an error() would stop qmake
    # might be importart if only soapySDR is used (TODO!)
    #message(FATAL_ERROR "no usable audio interface found - install pulseaudio or portaudio dev package")
endif()
if(ENABLE_SOAPYSDR)
     message(WARNING "ENABLE_SOAPYSDR detected, expect runtime bugs.")
endif()
if(ENABLE_JACK)
     message(WARNING "ENABLE_JACK detected, JACK isn't supported currently, it probably won't run / compile at all.")
endif()

set(DREAM_INCLUDE_DIRS ${INCLUDE_DIRS} CACHE INTERNAL "dream include dirs")
set(DREAM_EXTRA_LIBS ${EXTRA_LIBS} CACHE INTERNAL "dream extra libs")
