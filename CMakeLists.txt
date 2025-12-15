cmake_minimum_required(VERSION 3.16)

# LANGUAGES "C" is a bugfix for Journaline linking issue: dabdgdec_impl.c
#dabdgdec_impl.c is VERY weird
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

if(NOT USE_QT)
    set(CONSOLE ON)
endif()


list(APPEND INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")
list(APPEND INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/src/GUI-QT" "${CMAKE_SOURCE_DIR}/src/util-QT" "${CMAKE_SOURCE_DIR}/src/main-Qt")


add_compile_definitions(EXECUTABLE_NAME="${PROJECT_NAME}")
add_compile_definitions(QT_DISABLE_DEPRECATED_UP_TO=0x060700)
add_compile_definitions(WARN_ON)

set(HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/AMDemodulation.h
    ${CMAKE_SOURCE_DIR}/src/AMSSDemodulation.h
    ${CMAKE_SOURCE_DIR}/src/chanest/ChanEstTime.h
    ${CMAKE_SOURCE_DIR}/src/chanest/ChannelEstimation.h
    ${CMAKE_SOURCE_DIR}/src/chanest/IdealChannelEstimation.h
    ${CMAKE_SOURCE_DIR}/src/chanest/TimeLinear.h
    ${CMAKE_SOURCE_DIR}/src/chanest/TimeWiener.h
    ${CMAKE_SOURCE_DIR}/src/creceivedata.h
    ${CMAKE_SOURCE_DIR}/src/ctransmitdata.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/DABMOT.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/DataDecoder.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/DataEncoder.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/epgutil.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/Experiment.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/cpplog.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/crc_8_16.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/dabdatagroupdecoder.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/dabdgdec_impl.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/Journaline.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/log.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/newsobject.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/newssvcdec.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/newssvcdec_impl.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/NML.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/Splitter.h
    ${CMAKE_SOURCE_DIR}/src/datadecoding/MOTSlideShow.h
    ${CMAKE_SOURCE_DIR}/src/DataIO.h
    ${CMAKE_SOURCE_DIR}/src/drmchannel/ChannelSimulation.h
    ${CMAKE_SOURCE_DIR}/src/DrmReceiver.h
    ${CMAKE_SOURCE_DIR}/src/DrmSimulation.h
    ${CMAKE_SOURCE_DIR}/src/DrmTransceiver.h
    ${CMAKE_SOURCE_DIR}/src/DrmTransmitter.h
    ${CMAKE_SOURCE_DIR}/src/FAC/FAC.h
    ${CMAKE_SOURCE_DIR}/src/GlobalDefinitions.h
    ${CMAKE_SOURCE_DIR}/src/InputResample.h
    ${CMAKE_SOURCE_DIR}/src/interleaver/BlockInterleaver.h
    ${CMAKE_SOURCE_DIR}/src/interleaver/SymbolInterleaver.h
    ${CMAKE_SOURCE_DIR}/src/IQInputFilter.h
    ${CMAKE_SOURCE_DIR}/src/matlib/Matlib.h
    ${CMAKE_SOURCE_DIR}/src/matlib/MatlibSigProToolbox.h
    ${CMAKE_SOURCE_DIR}/src/matlib/MatlibStdToolbox.h
    ${CMAKE_SOURCE_DIR}/src/MDI/AFPacketGenerator.h
    ${CMAKE_SOURCE_DIR}/src/MDI/MDIDecode.h
    ${CMAKE_SOURCE_DIR}/src/MDI/MDIDefinitions.h
    ${CMAKE_SOURCE_DIR}/src/MDI/MDIInBuffer.h
    ${CMAKE_SOURCE_DIR}/src/MDI/MDIRSCI.h
    ${CMAKE_SOURCE_DIR}/src/MDI/MDITagItemDecoders.h
    ${CMAKE_SOURCE_DIR}/src/MDI/MDITagItems.h
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketInOut.h
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketSinkFile.h
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketSocket.h
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketSourceFile.h
    ${CMAKE_SOURCE_DIR}/src/MDI/Pft.h
    ${CMAKE_SOURCE_DIR}/src/MDI/RCITagItems.h
    ${CMAKE_SOURCE_DIR}/src/MDI/RSCITagItemDecoders.h
    ${CMAKE_SOURCE_DIR}/src/MDI/RSISubscriber.h
    ${CMAKE_SOURCE_DIR}/src/MDI/TagItemDecoder.h
    ${CMAKE_SOURCE_DIR}/src/MDI/TagPacketDecoder.h
    ${CMAKE_SOURCE_DIR}/src/MDI/TagPacketDecoderMDI.h
    ${CMAKE_SOURCE_DIR}/src/MDI/TagPacketDecoderRSCIControl.h
    ${CMAKE_SOURCE_DIR}/src/MDI/TagPacketGenerator.h
    ${CMAKE_SOURCE_DIR}/src/mlc/BitInterleaver.h
    ${CMAKE_SOURCE_DIR}/src/mlc/ChannelCode.h
    ${CMAKE_SOURCE_DIR}/src/mlc/ConvEncoder.h
    ${CMAKE_SOURCE_DIR}/src/mlc/EnergyDispersal.h
    ${CMAKE_SOURCE_DIR}/src/mlc/Metric.h
    ${CMAKE_SOURCE_DIR}/src/mlc/MLC.h
    ${CMAKE_SOURCE_DIR}/src/mlc/QAMMapping.h
    ${CMAKE_SOURCE_DIR}/src/mlc/ViterbiDecoder.h
    ${CMAKE_SOURCE_DIR}/src/MSCMultiplexer.h
    ${CMAKE_SOURCE_DIR}/src/ofdmcellmapping/CellMappingTable.h
    ${CMAKE_SOURCE_DIR}/src/ofdmcellmapping/OFDMCellMapping.h
    ${CMAKE_SOURCE_DIR}/src/OFDM.h
    ${CMAKE_SOURCE_DIR}/src/Parameter.h
    ${CMAKE_SOURCE_DIR}/src/PlotManager.h
    ${CMAKE_SOURCE_DIR}/src/ReceptLog.h
    ${CMAKE_SOURCE_DIR}/src/resample/ResampleFilter.h
    ${CMAKE_SOURCE_DIR}/src/resample/Resample.h
    ${CMAKE_SOURCE_DIR}/src/Scheduler.h
    ${CMAKE_SOURCE_DIR}/src/SDC/SDC.h
    ${CMAKE_SOURCE_DIR}/src/SDC/audioparam.h
    ${CMAKE_SOURCE_DIR}/src/ServiceInformation.h
    ${CMAKE_SOURCE_DIR}/src/sound/audiofilein.h
    ${CMAKE_SOURCE_DIR}/src/sound/selectioninterface.h
    ${CMAKE_SOURCE_DIR}/src/sound/soundinterface.h
    ${CMAKE_SOURCE_DIR}/src/sound/soundnull.h
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/aac_codec.h
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/AudioCodec.h
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/AudioSourceDecoder.h
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/AudioSourceEncoder.h
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/null_codec.h
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/opus_codec.h
    ${CMAKE_SOURCE_DIR}/src/spectrumanalyser.h
    ${CMAKE_SOURCE_DIR}/src/sync/FreqSyncAcq.h
    ${CMAKE_SOURCE_DIR}/src/sync/SyncUsingPil.h
    ${CMAKE_SOURCE_DIR}/src/sync/TimeSyncFilter.h
    ${CMAKE_SOURCE_DIR}/src/sync/TimeSync.h
    ${CMAKE_SOURCE_DIR}/src/sync/TimeSyncTrack.h
    ${CMAKE_SOURCE_DIR}/src/tables/TableAMSS.h
    ${CMAKE_SOURCE_DIR}/src/tables/TableCarMap.h
    ${CMAKE_SOURCE_DIR}/src/tables/TableDRMGlobal.h
    ${CMAKE_SOURCE_DIR}/src/tables/TableFAC.h
    ${CMAKE_SOURCE_DIR}/src/tables/TableMLC.h
    ${CMAKE_SOURCE_DIR}/src/tables/TableQAMMapping.h
    ${CMAKE_SOURCE_DIR}/src/tables/TableStations.h
    ${CMAKE_SOURCE_DIR}/src/TextMessage.h
    ${CMAKE_SOURCE_DIR}/src/UpsampleFilter.h
    ${CMAKE_SOURCE_DIR}/src/util/AudioFile.h
    ${CMAKE_SOURCE_DIR}/src/util/Buffer.h
    ${CMAKE_SOURCE_DIR}/src/util/CRC.h
    ${CMAKE_SOURCE_DIR}/src/util/FileTyper.h
    ${CMAKE_SOURCE_DIR}/src/util/LibraryLoader.h
    ${CMAKE_SOURCE_DIR}/src/util/LogPrint.h
    ${CMAKE_SOURCE_DIR}/src/util/Modul.h
    ${CMAKE_SOURCE_DIR}/src/util/Pacer.h
    ${CMAKE_SOURCE_DIR}/src/util/Reassemble.h
    ${CMAKE_SOURCE_DIR}/src/util/Settings.h
    ${CMAKE_SOURCE_DIR}/src/util/Utilities.h
    ${CMAKE_SOURCE_DIR}/src/util/Vector.h
    ${CMAKE_SOURCE_DIR}/src/Version.h
    ${CMAKE_SOURCE_DIR}/src/MSC/logicalframe.h
    ${CMAKE_SOURCE_DIR}/src/MSC/audiosuperframe.h
    ${CMAKE_SOURCE_DIR}/src/MSC/aacsuperframe.h
    ${CMAKE_SOURCE_DIR}/src/MSC/xheaacsuperframe.h
    ${CMAKE_SOURCE_DIR}/src/MSC/frameborderdescription.h
    ${CMAKE_SOURCE_DIR}/src/resample/speexresampler.h
    ${CMAKE_SOURCE_DIR}/src/resample/cspectrumresample.h
    ${CMAKE_SOURCE_DIR}/src/resample/caudioresample.h
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/reverb.h
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/caudioreverb.h
    ${CMAKE_SOURCE_DIR}/src/tuner.h
    ${CMAKE_SOURCE_DIR}/src/sound/soundinterfacefactory.h
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketSocketHTTP.h
)
# Bugfix
#list(APPEND SOURCE_FILES
#    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/dabdgdec_impl.c
#)

set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/AMDemodulation.cpp
    ${CMAKE_SOURCE_DIR}/src/AMSSDemodulation.cpp
    ${CMAKE_SOURCE_DIR}/src/chanest/ChanEstTime.cpp
    ${CMAKE_SOURCE_DIR}/src/chanest/ChannelEstimation.cpp
    ${CMAKE_SOURCE_DIR}/src/chanest/IdealChannelEstimation.cpp
    ${CMAKE_SOURCE_DIR}/src/chanest/TimeLinear.cpp
    ${CMAKE_SOURCE_DIR}/src/chanest/TimeWiener.cpp
    ${CMAKE_SOURCE_DIR}/src/creceivedata.cpp
    ${CMAKE_SOURCE_DIR}/src/ctransmitdata.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/DABMOT.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/DataDecoder.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/DataEncoder.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/epgutil.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/Experiment.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/Journaline.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/crc_8_16.c
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/dabdgdec_impl.c
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/log.c
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/newsobject.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/newssvcdec_impl.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/NML.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/journaline/Splitter.cpp
    ${CMAKE_SOURCE_DIR}/src/datadecoding/MOTSlideShow.cpp
    ${CMAKE_SOURCE_DIR}/src/DataIO.cpp
    ${CMAKE_SOURCE_DIR}/src/drmchannel/ChannelSimulation.cpp
    ${CMAKE_SOURCE_DIR}/src/DrmReceiver.cpp
    ${CMAKE_SOURCE_DIR}/src/DrmSimulation.cpp
    ${CMAKE_SOURCE_DIR}/src/DrmTransmitter.cpp
    ${CMAKE_SOURCE_DIR}/src/FAC/FAC.cpp
    ${CMAKE_SOURCE_DIR}/src/InputResample.cpp
    ${CMAKE_SOURCE_DIR}/src/interleaver/BlockInterleaver.cpp
    ${CMAKE_SOURCE_DIR}/src/interleaver/SymbolInterleaver.cpp
    ${CMAKE_SOURCE_DIR}/src/IQInputFilter.cpp
    ${CMAKE_SOURCE_DIR}/src/matlib/MatlibSigProToolbox.cpp
    ${CMAKE_SOURCE_DIR}/src/matlib/MatlibStdToolbox.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/AFPacketGenerator.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/MDIDecode.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/MDIInBuffer.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/MDIRSCI.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/MDITagItemDecoders.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/MDITagItems.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketSinkFile.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketSocket.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketSourceFile.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/Pft.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/RCITagItems.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/RSCITagItemDecoders.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/RSISubscriber.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/TagPacketDecoder.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/TagPacketDecoderMDI.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/TagPacketDecoderRSCIControl.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/TagPacketGenerator.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/BitInterleaver.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/ChannelCode.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/ConvEncoder.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/EnergyDispersal.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/Metric.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/MLC.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/QAMMapping.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/TrellisUpdateMMX.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/TrellisUpdateSSE2.cpp
    ${CMAKE_SOURCE_DIR}/src/mlc/ViterbiDecoder.cpp
    ${CMAKE_SOURCE_DIR}/src/MSCMultiplexer.cpp
    ${CMAKE_SOURCE_DIR}/src/ofdmcellmapping/CellMappingTable.cpp
    ${CMAKE_SOURCE_DIR}/src/ofdmcellmapping/OFDMCellMapping.cpp
    ${CMAKE_SOURCE_DIR}/src/OFDM.cpp
    ${CMAKE_SOURCE_DIR}/src/Parameter.cpp
    ${CMAKE_SOURCE_DIR}/src/PlotManager.cpp
    ${CMAKE_SOURCE_DIR}/src/ReceptLog.cpp
    ${CMAKE_SOURCE_DIR}/src/resample/Resample.cpp
    ${CMAKE_SOURCE_DIR}/src/resample/ResampleFilter.cpp
    ${CMAKE_SOURCE_DIR}/src/Scheduler.cpp
    ${CMAKE_SOURCE_DIR}/src/SDC/SDCReceive.cpp
    ${CMAKE_SOURCE_DIR}/src/SDC/SDCTransmit.cpp
    ${CMAKE_SOURCE_DIR}/src/SDC/audioparam.cpp
    ${CMAKE_SOURCE_DIR}/src/ServiceInformation.cpp
    ${CMAKE_SOURCE_DIR}/src/SimulationParameters.cpp
    ${CMAKE_SOURCE_DIR}/src/sound/audiofilein.cpp
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/aac_codec.cpp
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/AudioCodec.cpp
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/AudioSourceDecoder.cpp
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/AudioSourceEncoder.cpp
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/null_codec.cpp
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/opus_codec.cpp
    ${CMAKE_SOURCE_DIR}/src/spectrumanalyser.cpp
    ${CMAKE_SOURCE_DIR}/src/sync/FreqSyncAcq.cpp
    ${CMAKE_SOURCE_DIR}/src/sync/SyncUsingPil.cpp
    ${CMAKE_SOURCE_DIR}/src/sync/TimeSync.cpp
    ${CMAKE_SOURCE_DIR}/src/sync/TimeSyncFilter.cpp
    ${CMAKE_SOURCE_DIR}/src/sync/TimeSyncTrack.cpp
    ${CMAKE_SOURCE_DIR}/src/tables/TableCarMap.cpp
    ${CMAKE_SOURCE_DIR}/src/tables/TableFAC.cpp
    ${CMAKE_SOURCE_DIR}/src/tables/TableStations.cpp
    ${CMAKE_SOURCE_DIR}/src/TextMessage.cpp
    ${CMAKE_SOURCE_DIR}/src/util/CRC.cpp
    ${CMAKE_SOURCE_DIR}/src/util/FileTyper.cpp
    ${CMAKE_SOURCE_DIR}/src/util/LogPrint.cpp
    ${CMAKE_SOURCE_DIR}/src/util/Reassemble.cpp
    ${CMAKE_SOURCE_DIR}/src/util/Settings.cpp
    ${CMAKE_SOURCE_DIR}/src/util/Utilities.cpp
    ${CMAKE_SOURCE_DIR}/src/Version.cpp
    ${CMAKE_SOURCE_DIR}/src/sound/soundnull.cpp
    ${CMAKE_SOURCE_DIR}/src/DrmTransceiver.cpp
    ${CMAKE_SOURCE_DIR}/src/sound/soundinterface.cpp
    ${CMAKE_SOURCE_DIR}/src/sound/selectioninterface.cpp
    ${CMAKE_SOURCE_DIR}/src/MSC/logicalframe.cpp
    ${CMAKE_SOURCE_DIR}/src/MSC/audiosuperframe.cpp
    ${CMAKE_SOURCE_DIR}/src/MSC/aacsuperframe.cpp
    ${CMAKE_SOURCE_DIR}/src/MSC/xheaacsuperframe.cpp
    ${CMAKE_SOURCE_DIR}/src/MSC/frameborderdescription.cpp
    ${CMAKE_SOURCE_DIR}/src/resample/speexresampler.cpp
    ${CMAKE_SOURCE_DIR}/src/resample/cspectrumresample.cpp
    ${CMAKE_SOURCE_DIR}/src/resample/caudioresample.cpp
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/reverb.cpp
    ${CMAKE_SOURCE_DIR}/src/sourcedecoders/caudioreverb.cpp
    ${CMAKE_SOURCE_DIR}/src/tuner.cpp
    ${CMAKE_SOURCE_DIR}/src/sound/soundinterfacefactory.cpp
    ${CMAKE_SOURCE_DIR}/src/MDI/PacketSocketHTTP.cpp
)


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


if(CONSOLE)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/main.cpp)
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
    if(UNIX AND NOT CROSS_COMPILE)
        list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/linux/ConsoleIO.h)
        list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/linux/ConsoleIO.cpp)
        message(STATUS "Building Qt console with terminal user interface")
    endif()
endif()

# If Qt GUI support is enabled, add GUI-specific sources & forms
set(FORMS "")
set(GUI_HEADERS "")
set(GUI_SOURCES "")
set(RESOURCES "")
if(USE_QT)

    list(APPEND RESOURCES src/GUI-QT/res/icons.qrc)
    list(APPEND INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/src/GUI-QT)
    list(APPEND FORMS
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/AboutDlgbase.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/AMMainWindow.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/AMSSDlgbase.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/AACCodecParams.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/OpusCodecParams.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/DRMMainWindow.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/EPGDlgbase.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/FMMainWindow.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/GeneralSettingsDlgbase.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/JLViewer.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/LiveScheduleWindow.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/MultSettingsDlgbase.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/SlideShowViewer.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/StationsDlgbase.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/systemevalDlgbase.ui
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/TransmDlgbase.ui
    )
    list(APPEND GUI_HEADERS
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/AnalogDemDlg.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/CWindow.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/DialogUtil.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/DRMPlot.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/EPGDlg.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/EvaluationDlg.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/fdrmdialog.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/fmdialog.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/GeneralSettingsDlg.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/jlbrowser.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/JLViewer.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/LiveScheduleDlg.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/MultColorLED.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/MultSettingsDlg.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/Schedule.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/SlideShowViewer.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/SoundCardSelMenu.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/StationsDlg.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/OpusCodecParams.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/AACCodecParams.h
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/TransmDlg.h
    )
    list(APPEND GUI_SOURCES
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/AnalogDemDlg.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/CWindow.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/DialogUtil.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/DRMPlot.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/EPGDlg.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/EvaluationDlg.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/fdrmdialog.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/fmdialog.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/GeneralSettingsDlg.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/jlbrowser.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/JLViewer.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/LiveScheduleDlg.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/MultColorLED.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/MultSettingsDlg.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/Schedule.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/SlideShowViewer.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/SoundCardSelMenu.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/StationsDlg.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/OpusCodecParams.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/AACCodecParams.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/TransmDlg.cpp
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/main.cpp
    )
    list(APPEND SOURCE_FILES ${GUI_SOURCES})
    list(APPEND HEADER_FILES ${GUI_HEADERS})
endif()

if(USE_QT)
    list(APPEND HEADER_FILES
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/Logging.h
        ${CMAKE_SOURCE_DIR}/src/util-QT/epgdec.h
        ${CMAKE_SOURCE_DIR}/src/util-QT/EPG.h
        ${CMAKE_SOURCE_DIR}/src/util-QT/Util.h
        ${CMAKE_SOURCE_DIR}/src/main-Qt/ctrx.h
        ${CMAKE_SOURCE_DIR}/src/main-Qt/crx.h
        ${CMAKE_SOURCE_DIR}/src/main-Qt/ctx.h
    )
    list(APPEND SOURCE_FILES
        ${CMAKE_SOURCE_DIR}/src/GUI-QT/Logging.cpp
        ${CMAKE_SOURCE_DIR}/src/util-QT/EPG.cpp
        ${CMAKE_SOURCE_DIR}/src/util-QT/epgdec.cpp
        ${CMAKE_SOURCE_DIR}/src/util-QT/Util.cpp
        ${CMAKE_SOURCE_DIR}/src/main-Qt/ctrx.cpp
        ${CMAKE_SOURCE_DIR}/src/main-Qt/crx.cpp
        ${CMAKE_SOURCE_DIR}/src/main-Qt/ctx.cpp
    )
endif()

#Optional features (fdk-aac, opus, sndfile, speexdsp, gps, hamlib)
if(ENABLE_FDK_AAC)
    add_compile_definitions(HAVE_LIBFDK_AAC HAVE_USAC)
    list(APPEND EXTRA_LIBS "-lfdk-aac" "-L/usr/lib64/fdk-aac -lfdk-aac")
    list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/sourcedecoders/fdk_aac_codec.h)
    list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/sourcedecoders/fdk_aac_codec.cpp)
    message(STATUS "with fdk-aac")
endif()

if(ENABLE_OPUS)
    add_compile_definitions(HAVE_LIBOPUS USE_OPUS_LIBRARY)
    if(UNIX)
        list(APPEND EXTRA_LIBS "-lopus")
    endif()
    message(STATUS "with opus")
endif()

if(ENABLE_SNDFILE)
    add_compile_definitions(HAVE_LIBSNDFILE)
    if(UNIX)
        list(APPEND EXTRA_LIBS "-lsndfile1")
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
    if(LK MATCHES "^-l" OR LK MATCHES "^-L" OR LK MATCHES "^-Wl,")
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

# try to find Qt6/Qt5
if(USE_QT)
    if(QT_MAJOR_VERSION STREQUAL "6")
        find_package(Qt6 COMPONENTS Core Widgets Network Xml Svg WebEngineWidgets Core5Compat Gui REQUIRED QUIET)
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
qt6_wrap_ui(QT_FORMS ${FORMS})
target_sources(${PROJECT_NAME} PRIVATE ${QT_FORMS})
            # Core5Compat is a Qt6 module mapping to Qt5 behaviour if present
            if(TARGET Qt6::Core5Compat)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core5Compat)
            endif()
        endif()
    else()
        # Try Qt5
        find_package(Qt5 COMPONENTS Core Widgets Network Xml WebEngineWidgets Svg REQUIRED QUIET)
        if(Qt5_FOUND)
            message(STATUS "Qt5 found")
            if(TARGET Qt5::Widgets)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)
            endif()
            if(TARGET Qt5::Network)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Network)
            endif()
            if(TARGET Qt5::Xml)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Xml)
            endif()
            if(TARGET Qt5::Svg)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Svg)
            endif()
            if(TARGET Qt5::WebEngineWidgets)
                list(APPEND FORMS ${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.ui)
                list(APPEND HEADER_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.h)
                list(APPEND SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/GUI-QT/BWSViewer.cpp)
                target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::WebEngineWidgets)
                message(STATUS "with BWS (Qt WebEngineWidgets)")
            endif()

            # Process resources and forms for Qt5
            qt5_add_resources(QT_RESOURCES ${RESOURCES})
            qt5_wrap_ui(QT_FORMS_MOC ${FORMS})
            target_sources(${PROJECT_NAME} PRIVATE ${QT_RESOURCES} ${QT_FORMS_MOC})
        endif()
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

if(NOT ENABLE_PULSEAUDIO AND NOT ENABLE_PORTAUDIO AND NOT ENABLE_ALSA)
    message(WARNING "No usable audio interface configured (pulseaudio/portaudio/alsa). Set ENABLE_PULSEAUDIO or ENABLE_PORTAUDIO or ENABLE_ALSA.")
    # In the original .pro an error() would stop qmake
    # might be importart if only soapySDR is used (TODO!)
    #message(FATAL_ERROR "no usable audio interface found - install pulseaudio or portaudio dev package")
endif()

set(DREAM_INCLUDE_DIRS ${INCLUDE_DIRS} CACHE INTERNAL "dream include dirs")
set(DREAM_EXTRA_LIBS ${EXTRA_LIBS} CACHE INTERNAL "dream extra libs")
