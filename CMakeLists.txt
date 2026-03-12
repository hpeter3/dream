cmake_minimum_required(VERSION 3.16)
project(dream LANGUAGES C CXX)
set(PROJECT_NAME dream)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
find_package(PkgConfig REQUIRED)

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
option(ENABLE_HARDENING "Enable compiler/linker hardening flags" ON)
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

# Exclude the optional modules (ENABLE_xyz and USE_QT) by default:
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
        list(FILTER SOURCE_FILES  EXCLUDE REGEX ".*/${MODULE}\\.c$")
    endforeach()
    # push changes to parent scope
    set(SOURCE_FILES ${SOURCE_FILES} PARENT_SCOPE)
endfunction()

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
    	find_package(FFTW3 REQUIRED)
	if(FFTW3_FOUND)
    list(APPEND INCLUDE_DIRS ${FFTW3_INCLUDE_DIRS})
    list(APPEND EXTRA_LIBS ${FFTW3_LIBRARIES})
	endif()
	find_package(ZLIB REQUIRED)
    list(APPEND EXTRA_LIBS ZLIB::ZLIB)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "linux")
    list(APPEND EXTRA_LIBS "-ldl" "-lrt")
endif()


# If Qt GUI support is enabled, add GUI-specific sources & forms
set(FORMS "")
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
    
    file(GLOB GUI_SOURCES_GLOB
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/*.cpp"
    )
    list(REMOVE_ITEM GUI_SOURCES_GLOB
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.cpp"
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.cpp"
        "${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp"
    )
    list(APPEND GUI_SOURCES ${GUI_SOURCES_GLOB})
    
    file(GLOB UTIL_SOURCES_GLOB "${CMAKE_SOURCE_DIR}/src/util-QT/*.cpp")
    list(REMOVE_ITEM UTIL_SOURCES_GLOB "${CMAKE_SOURCE_DIR}/src/util-QT/Rig.cpp")
    list(APPEND GUI_SOURCES ${UTIL_SOURCES_GLOB})
    
    
    file(GLOB MAINQT_SOURCES_GLOB "${CMAKE_SOURCE_DIR}/src/main-Qt/*.cpp")
    list(REMOVE_ITEM MAINQT_SOURCES_GLOB "${CMAKE_SOURCE_DIR}/src/main-Qt/main.cpp")
    list(APPEND GUI_SOURCES ${MAINQT_SOURCES_GLOB})
    
    
    list(APPEND SOURCE_FILES ${GUI_SOURCES})
endif()

if(CONSOLE)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
    list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp)
    # unix:!cross_compile extras
    if(UNIX AND NOT CROSS_COMPILE)
        list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/linux/ConsoleIO.cpp)
        message(STATUS "Building with terminal user interface (console)")
    endif()
endif()

# Qt console (uses Qt but without GUI)
if(QTCONSOLE)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main-Qt/main.cpp)
    list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp)
    if(UNIX AND NOT CROSS_COMPILE)
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

    pkg_check_modules(FDKAAC fdk-aac)

    if(FDKAAC_FOUND)
        list(APPEND INCLUDE_DIRS ${FDKAAC_INCLUDE_DIRS})

        # Fedora hack: if pkg-config gives -lfdk-aac but the unversioned .so doesn't exist
        # probably an issue with the RPMFusion provided fdk-aac package
        set(FDKAAC_SO "/usr/lib64/libfdk-aac.so")
        if(NOT EXISTS "${FDKAAC_SO}" AND EXISTS "/usr/lib64/libfdk-aac.so.2")
            message(STATUS "fdk-aac workaround: linking against libfdk-aac.so.2")
            list(APPEND EXTRA_LIBS /usr/lib64/libfdk-aac.so.2)
        else()
            list(APPEND EXTRA_LIBS ${FDKAAC_LIBRARIES})
        endif()
    else()
        # fallback
        if(EXISTS "/usr/lib64/libfdk-aac.so.2" AND EXISTS "/usr/include/fdk-aac")
            list(APPEND INCLUDE_DIRS /usr/include/fdk-aac)
            list(APPEND EXTRA_LIBS /usr/lib64/libfdk-aac.so.2)
        else()
            message(FATAL_ERROR "FDK-AAC requested but library not found")
        endif()
    endif()
    
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/sourcedecoders/fdk_aac_codec.cpp)
    message(STATUS "with fdk-aac")
endif()

if(ENABLE_OPUS)
    add_compile_definitions(HAVE_LIBOPUS)
    pkg_check_modules(OPUS opus)
    if(OPUS_FOUND)
        list(APPEND INCLUDE_DIRS ${OPUS_INCLUDE_DIRS})
        list(APPEND EXTRA_LIBS ${OPUS_LIBRARIES})
    endif()
    message(STATUS "with opus")
endif()

if(ENABLE_SNDFILE)
    add_compile_definitions(HAVE_LIBSNDFILE)
	pkg_check_modules(SNDFILE sndfile)

	if(SNDFILE_FOUND)
        list(APPEND INCLUDE_DIRS ${SNDFILE_INCLUDE_DIRS})
        list(APPEND EXTRA_LIBS ${SNDFILE_LIBRARIES})
	endif()
    message(STATUS "with libsndfile")
endif()

if(ENABLE_SPEEXDSP)
    pkg_check_modules(SPEEXDSP speexdsp)
    if(SPEEXDSP_FOUND)
        list(APPEND INCLUDE_DIRS ${SPEEXDSP_INCLUDE_DIRS})
        list(APPEND EXTRA_LIBS ${SPEEXDSP_LIBRARIES})
    endif()
endif()


if(ENABLE_HAMLIB)
    add_compile_definitions(HAVE_LIBHAMLIB)
	pkg_check_modules(HAMLIB hamlib)

	if(HAMLIB_FOUND)
        list(APPEND INCLUDE_DIRS ${HAMLIB_INCLUDE_DIRS})
        list(APPEND EXTRA_LIBS ${HAMLIB_LIBRARIES})
	endif()
    # Remove in case already present
    list(REMOVE_ITEM SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/util/Hamlib.cpp)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/util/Hamlib.cpp)
    if(USE_QT)
        list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/util-QT/Rig.cpp)
    endif()
    if(USE_QT)
        list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.cpp)
        list(APPEND FORMS ${CMAKE_SOURCE_DIR}/src/GUI-QT/RigDlg.ui)
    endif()
    message(STATUS "with hamlib")
endif()

if(ENABLE_GPS)

	pkg_check_modules(GPS libgps)

	if(GPS_FOUND)
        list(APPEND INCLUDE_DIRS ${GPS_INCLUDE_DIRS})
        list(APPEND EXTRA_LIBS ${GPS_LIBRARIES})
	endif()
	add_compile_definitions(HAVE_LIBGPS)
    message(STATUS "with gps")
endif()


include_directories(${INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)

set(ALL_SOURCES ${SOURCE_FILES})

####################################################################################
add_executable(${PROJECT_NAME} ${ALL_SOURCES} ${RESOURCES})
# Make sure the compiler can find generated ui_*.h files
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}/dream_autogen/include
)
####################################################################################
include(cmake/hardening.cmake)
include(cmake/audiobackends.cmake)
dream_configure_backend(dream)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${EXTRA_LIBS})

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

if(UNIX AND NOT CROSS_COMPILE)
    if(DEFINED ENABLE_LIBPCAP)
        target_compile_definitions(${PROJECT_NAME} PRIVATE HAVE_LIBPCAP)
        find_library(PCAP_LIB pcap)
        if(PCAP_LIB)
            target_link_libraries(${PROJECT_NAME} PRIVATE ${PCAP_LIB})
        endif()
    endif()
endif()

# try to find Qt6
if(USE_QT AND QT_MAJOR_VERSION STREQUAL "6")
	find_package(Qt6 COMPONENTS Core Widgets Network Xml Svg WebEngineWidgets Gui REQUIRED)
	
    if(TARGET Qt6::WebEngineWidgets)
        list(APPEND FORMS
            ${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.ui
        )
        list(APPEND SOURCE_FILES
            ${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.cpp
        )
    endif()
    qt_standard_project_setup()

    target_link_libraries(dream PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
        Qt6::Xml
        Qt6::Svg
    )
    if(TARGET Qt6::WebEngineWidgets)
        target_link_libraries(dream PRIVATE Qt6::WebEngineWidgets)
    endif()
endif()

if(CONSOLE AND UNIX AND NOT CROSS_COMPILE)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
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

if(ENABLE_HARDENING)
    message(STATUS "Hardening enabled")
endif()


set(DREAM_INCLUDE_DIRS ${INCLUDE_DIRS} CACHE INTERNAL "dream include dirs")
set(DREAM_EXTRA_LIBS ${EXTRA_LIBS} CACHE INTERNAL "dream extra libs")
