cmake_minimum_required(VERSION 3.16)
project(dream VERSION 1.0 LANGUAGES C CXX)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Gui)
find_package(Qt6 OPTIONAL_COMPONENTS Core5Compat Network Svg Widgets Xml)
find_package(Qt5Network REQUIRED)

qt_standard_project_setup()

qt_add_executable(dream WIN32 MACOSX_BUNDLE
    src/AMDemodulation.cpp src/AMDemodulation.h
    src/AMSSDemodulation.cpp src/AMSSDemodulation.h
    src/DataIO.cpp src/DataIO.h
    src/DrmReceiver.cpp src/DrmReceiver.h
    src/DrmSimulation.cpp src/DrmSimulation.h
    src/DrmTransceiver.cpp src/DrmTransceiver.h
    src/DrmTransmitter.cpp src/DrmTransmitter.h
    src/FAC/FAC.cpp src/FAC/FAC.h
    src/GlobalDefinitions.h
    src/IQInputFilter.cpp src/IQInputFilter.h
    src/InputResample.cpp src/InputResample.h
    src/MDI/AFPacketGenerator.cpp src/MDI/AFPacketGenerator.h
    src/MDI/MDIDecode.cpp src/MDI/MDIDecode.h
    src/MDI/MDIDefinitions.h
    src/MDI/MDIInBuffer.cpp src/MDI/MDIInBuffer.h
    src/MDI/MDIRSCI.cpp src/MDI/MDIRSCI.h
    src/MDI/MDITagItemDecoders.cpp src/MDI/MDITagItemDecoders.h
    src/MDI/MDITagItems.cpp src/MDI/MDITagItems.h
    src/MDI/PacketInOut.h
    src/MDI/PacketSinkFile.cpp src/MDI/PacketSinkFile.h
    src/MDI/PacketSocket.cpp src/MDI/PacketSocket.h
    src/MDI/PacketSocketHTTP.cpp src/MDI/PacketSocketHTTP.h
    src/MDI/PacketSourceFile.cpp src/MDI/PacketSourceFile.h
    src/MDI/Pft.cpp src/MDI/Pft.h
    src/MDI/RCITagItems.cpp src/MDI/RCITagItems.h
    src/MDI/RSCITagItemDecoders.cpp src/MDI/RSCITagItemDecoders.h
    src/MDI/RSISubscriber.cpp src/MDI/RSISubscriber.h
    src/MDI/TagItemDecoder.h
    src/MDI/TagPacketDecoder.cpp src/MDI/TagPacketDecoder.h
    src/MDI/TagPacketDecoderMDI.cpp src/MDI/TagPacketDecoderMDI.h
    src/MDI/TagPacketDecoderRSCIControl.cpp src/MDI/TagPacketDecoderRSCIControl.h
    src/MDI/TagPacketGenerator.cpp src/MDI/TagPacketGenerator.h
    src/MSC/aacsuperframe.cpp src/MSC/aacsuperframe.h
    src/MSC/audiosuperframe.cpp src/MSC/audiosuperframe.h
    src/MSC/frameborderdescription.cpp src/MSC/frameborderdescription.h
    src/MSC/logicalframe.cpp src/MSC/logicalframe.h
    src/MSC/xheaacsuperframe.cpp src/MSC/xheaacsuperframe.h
    src/MSCMultiplexer.cpp src/MSCMultiplexer.h
    src/OFDM.cpp src/OFDM.h
    src/Parameter.cpp src/Parameter.h
    src/PlotManager.cpp src/PlotManager.h
    src/ReceptLog.cpp src/ReceptLog.h
    src/SDC/SDC.h
    src/SDC/SDCReceive.cpp
    src/SDC/SDCTransmit.cpp
    src/SDC/audioparam.cpp src/SDC/audioparam.h
    src/Scheduler.cpp src/Scheduler.h
    src/ServiceInformation.cpp src/ServiceInformation.h
    src/SimulationParameters.cpp
    src/TextMessage.cpp src/TextMessage.h
    src/UpsampleFilter.h
    src/Version.cpp src/Version.h
    src/chanest/ChanEstTime.cpp src/chanest/ChanEstTime.h
    src/chanest/ChannelEstimation.cpp src/chanest/ChannelEstimation.h
    src/chanest/IdealChannelEstimation.cpp src/chanest/IdealChannelEstimation.h
    src/chanest/TimeLinear.cpp src/chanest/TimeLinear.h
    src/chanest/TimeWiener.cpp src/chanest/TimeWiener.h
    src/creceivedata.cpp src/creceivedata.h
    src/ctransmitdata.cpp src/ctransmitdata.h
    src/datadecoding/DABMOT.cpp src/datadecoding/DABMOT.h
    src/datadecoding/DataDecoder.cpp src/datadecoding/DataDecoder.h
    src/datadecoding/DataEncoder.cpp src/datadecoding/DataEncoder.h
    src/datadecoding/Experiment.cpp src/datadecoding/Experiment.h
    src/datadecoding/Journaline.cpp src/datadecoding/Journaline.h
    src/datadecoding/MOTSlideShow.cpp src/datadecoding/MOTSlideShow.h
    src/datadecoding/epgutil.cpp src/datadecoding/epgutil.h
    src/datadecoding/journaline/NML.cpp src/datadecoding/journaline/NML.h
    src/datadecoding/journaline/Splitter.cpp src/datadecoding/journaline/Splitter.h
    src/datadecoding/journaline/cpplog.h
    src/datadecoding/journaline/crc_8_16.c src/datadecoding/journaline/crc_8_16.h
    src/datadecoding/journaline/dabdatagroupdecoder.h
    src/datadecoding/journaline/dabdgdec_impl.c src/datadecoding/journaline/dabdgdec_impl.h
    src/datadecoding/journaline/log.c src/datadecoding/journaline/log.h
    src/datadecoding/journaline/newsobject.cpp src/datadecoding/journaline/newsobject.h
    src/datadecoding/journaline/newssvcdec.h
    src/datadecoding/journaline/newssvcdec_impl.cpp src/datadecoding/journaline/newssvcdec_impl.h
    src/drmchannel/ChannelSimulation.cpp src/drmchannel/ChannelSimulation.h
    src/interleaver/BlockInterleaver.cpp src/interleaver/BlockInterleaver.h
    src/interleaver/SymbolInterleaver.cpp src/interleaver/SymbolInterleaver.h
    src/matlib/Matlib.h
    src/matlib/MatlibSigProToolbox.cpp src/matlib/MatlibSigProToolbox.h
    src/matlib/MatlibStdToolbox.cpp src/matlib/MatlibStdToolbox.h
    src/mlc/BitInterleaver.cpp src/mlc/BitInterleaver.h
    src/mlc/ChannelCode.cpp src/mlc/ChannelCode.h
    src/mlc/ConvEncoder.cpp src/mlc/ConvEncoder.h
    src/mlc/EnergyDispersal.cpp src/mlc/EnergyDispersal.h
    src/mlc/MLC.cpp src/mlc/MLC.h
    src/mlc/Metric.cpp src/mlc/Metric.h
    src/mlc/QAMMapping.cpp src/mlc/QAMMapping.h
    src/mlc/TrellisUpdateMMX.cpp
    src/mlc/TrellisUpdateSSE2.cpp
    src/mlc/ViterbiDecoder.cpp src/mlc/ViterbiDecoder.h
    src/ofdmcellmapping/CellMappingTable.cpp src/ofdmcellmapping/CellMappingTable.h
    src/ofdmcellmapping/OFDMCellMapping.cpp src/ofdmcellmapping/OFDMCellMapping.h
    src/resample/Resample.cpp src/resample/Resample.h
    src/resample/ResampleFilter.cpp src/resample/ResampleFilter.h
    src/resample/caudioresample.cpp src/resample/caudioresample.h
    src/resample/cspectrumresample.cpp src/resample/cspectrumresample.h
    src/resample/speexresampler.cpp src/resample/speexresampler.h
    src/sound/audiofilein.cpp src/sound/audiofilein.h
    src/sound/drm_soapySDR.cpp src/sound/drm_soapySDR.h
    src/sound/selectioninterface.cpp src/sound/selectioninterface.h
    src/sound/soundinterface.cpp src/sound/soundinterface.h
    src/sound/soundinterfacefactory.cpp src/sound/soundinterfacefactory.h
    src/sound/soundnull.cpp src/sound/soundnull.h
    src/sourcedecoders/AudioCodec.cpp src/sourcedecoders/AudioCodec.h
    src/sourcedecoders/AudioSourceDecoder.cpp src/sourcedecoders/AudioSourceDecoder.h
    src/sourcedecoders/AudioSourceEncoder.cpp src/sourcedecoders/AudioSourceEncoder.h
    src/sourcedecoders/aac_codec.cpp src/sourcedecoders/aac_codec.h
    src/sourcedecoders/caudioreverb.cpp src/sourcedecoders/caudioreverb.h
    src/sourcedecoders/null_codec.cpp src/sourcedecoders/null_codec.h
    src/sourcedecoders/opus_codec.cpp src/sourcedecoders/opus_codec.h
    src/sourcedecoders/reverb.cpp src/sourcedecoders/reverb.h
    src/spectrumanalyser.cpp src/spectrumanalyser.h
    src/sync/FreqSyncAcq.cpp src/sync/FreqSyncAcq.h
    src/sync/SyncUsingPil.cpp src/sync/SyncUsingPil.h
    src/sync/TimeSync.cpp src/sync/TimeSync.h
    src/sync/TimeSyncFilter.cpp src/sync/TimeSyncFilter.h
    src/sync/TimeSyncTrack.cpp src/sync/TimeSyncTrack.h
    src/tables/TableAMSS.h
    src/tables/TableCarMap.cpp src/tables/TableCarMap.h
    src/tables/TableDRMGlobal.h
    src/tables/TableFAC.cpp src/tables/TableFAC.h
    src/tables/TableMLC.h
    src/tables/TableQAMMapping.h
    src/tables/TableStations.cpp src/tables/TableStations.h
    src/tuner.cpp src/tuner.h
    src/util/AudioFile.h
    src/util/Buffer.h
    src/util/CRC.cpp src/util/CRC.h
    src/util/FileTyper.cpp src/util/FileTyper.h
    src/util/LibraryLoader.h
    src/util/LogPrint.cpp src/util/LogPrint.h
    src/util/Modul.h
    src/util/Pacer.h
    src/util/Reassemble.cpp src/util/Reassemble.h
    src/util/Settings.cpp src/util/Settings.h
    src/util/Utilities.cpp src/util/Utilities.h
    src/util/Vector.h
)
target_include_directories(dream PRIVATE
    include
)

target_compile_definitions(dream PRIVATE
    EXECUTABLE_NAME=dream
    QT_DISABLE_DEPRECATED_UP_TO=0x060700
)

target_link_directories(dream PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_link_libraries(dream PRIVATE
    Qt::Core
    Qt::Gui
)

if(console)
    target_sources(dream PUBLIC
        src/main.cpp
    )

    target_link_libraries(dream PRIVATE
        # Remove flag: -core
        # Remove flag: -gui
    )
endif()

if(UNIX AND console AND NOT CMAKE_CROSSCOMPILING)
    target_sources(dream PUBLIC
        src/linux/ConsoleIO.cpp src/linux/ConsoleIO.h
    )

    target_link_libraries(dream PRIVATE
        pthread
    )
endif()

if(qtconsole)
    target_sources(dream PUBLIC
        src/main-Qt/main.cpp
    )

    target_link_libraries(dream PRIVATE
        # Remove flag: -gui
        Qt::Core5Compat
        Qt::Network
        Qt::Xml
    )
endif()

if(UNIX AND qtconsole AND NOT CMAKE_CROSSCOMPILING)
    target_sources(dream PUBLIC
        src/linux/ConsoleIO.cpp src/linux/ConsoleIO.h
    )
endif()

if(QT___contains___gui)
    target_sources(dream PUBLIC
        src/GUI-QT/AACCodecParams.cpp src/GUI-QT/AACCodecParams.h src/GUI-QT/AACCodecParams.ui
        src/GUI-QT/AMMainWindow.ui
        src/GUI-QT/AMSSDlgbase.ui
        src/GUI-QT/AboutDlgbase.ui
        src/GUI-QT/AnalogDemDlg.cpp src/GUI-QT/AnalogDemDlg.h
        src/GUI-QT/CWindow.cpp src/GUI-QT/CWindow.h
        src/GUI-QT/DRMMainWindow.ui
        src/GUI-QT/DRMPlot.cpp src/GUI-QT/DRMPlot.h
        src/GUI-QT/DialogUtil.cpp src/GUI-QT/DialogUtil.h
        src/GUI-QT/EPGDlg.cpp src/GUI-QT/EPGDlg.h
        src/GUI-QT/EPGDlgbase.ui
        src/GUI-QT/EvaluationDlg.cpp src/GUI-QT/EvaluationDlg.h
        src/GUI-QT/FMMainWindow.ui
        src/GUI-QT/GeneralSettingsDlg.cpp src/GUI-QT/GeneralSettingsDlg.h
        src/GUI-QT/GeneralSettingsDlgbase.ui
        src/GUI-QT/JLViewer.cpp src/GUI-QT/JLViewer.h src/GUI-QT/JLViewer.ui
        src/GUI-QT/LiveScheduleDlg.cpp src/GUI-QT/LiveScheduleDlg.h
        src/GUI-QT/LiveScheduleWindow.ui
        src/GUI-QT/MultColorLED.cpp src/GUI-QT/MultColorLED.h
        src/GUI-QT/MultSettingsDlg.cpp src/GUI-QT/MultSettingsDlg.h
        src/GUI-QT/MultSettingsDlgbase.ui
        src/GUI-QT/OpusCodecParams.cpp src/GUI-QT/OpusCodecParams.h src/GUI-QT/OpusCodecParams.ui
        src/GUI-QT/Schedule.cpp src/GUI-QT/Schedule.h
        src/GUI-QT/SlideShowViewer.cpp src/GUI-QT/SlideShowViewer.h src/GUI-QT/SlideShowViewer.ui
        src/GUI-QT/SoundCardSelMenu.cpp src/GUI-QT/SoundCardSelMenu.h
        src/GUI-QT/StationsDlg.cpp src/GUI-QT/StationsDlg.h
        src/GUI-QT/StationsDlgbase.ui
        src/GUI-QT/TransmDlg.cpp src/GUI-QT/TransmDlg.h
        src/GUI-QT/TransmDlgbase.ui
        src/GUI-QT/fdrmdialog.cpp src/GUI-QT/fdrmdialog.h
        src/GUI-QT/fmdialog.cpp src/GUI-QT/fmdialog.h
        src/GUI-QT/jlbrowser.cpp src/GUI-QT/jlbrowser.h
        src/GUI-QT/main.cpp
        src/GUI-QT/systemevalDlgbase.ui
    )

    target_include_directories(dream PRIVATE
        src/GUI-QT
    )

    target_link_libraries(dream PRIVATE
        Qt::Core5Compat
        Qt::Network
        Qt::Widgets
        Qt::Xml
    )


    # Resources:
    set(icons_resource_files
        "src/GUI-QT/res/CSAudSNRHist.png"
        "src/GUI-QT/res/CSChannel.png"
        "src/GUI-QT/res/CSConstellation.png"
        "src/GUI-QT/res/CSFAC.png"
        "src/GUI-QT/res/CSHistory.png"
        "src/GUI-QT/res/CSHistoryDelDopp.png"
        "src/GUI-QT/res/CSHistoryFreqSam.png"
        "src/GUI-QT/res/CSIR.png"
        "src/GUI-QT/res/CSMSC.png"
        "src/GUI-QT/res/CSSDC.png"
        "src/GUI-QT/res/CSSpectrum.png"
        "src/GUI-QT/res/CSSpectrumAudio.png"
        "src/GUI-QT/res/CSSpectrumInpPSD.png"
        "src/GUI-QT/res/CSSpectrumInpSpectr.png"
        "src/GUI-QT/res/CSSpectrumSNR.png"
        "src/GUI-QT/res/CSSpectrumShiftedPSD.png"
        "src/GUI-QT/res/CSSpectrumWaterf.png"
        "src/GUI-QT/res/CSTF.png"
        "src/GUI-QT/res/Home.png"
        "src/GUI-QT/res/JumpBegin.png"
        "src/GUI-QT/res/JumpEnd.png"
        "src/GUI-QT/res/LogoFhGIIS.png"
        "src/GUI-QT/res/LogoJournaline.png"
        "src/GUI-QT/res/LogoOpus.png"
        "src/GUI-QT/res/LogoSmall.png"
        "src/GUI-QT/res/MainIcon.svg"
        "src/GUI-QT/res/MainIconTx.svg"
        "src/GUI-QT/res/Refresh.png"
        "src/GUI-QT/res/StepBack.png"
        "src/GUI-QT/res/StepForw.png"
        "src/GUI-QT/res/Stop.png"
        "src/GUI-QT/res/aac.png"
        "src/GUI-QT/res/greenCube.png"
        "src/GUI-QT/res/orangeCube.png"
        "src/GUI-QT/res/pinkCube.png"
        "src/GUI-QT/res/redCube.png"
        "src/GUI-QT/res/smallGreenCube.png"
    )

    qt_add_resources(dream "icons"
        PREFIX
            "/icons"
        BASE
            "src/GUI-QT/res"
        FILES
            ${icons_resource_files}
    )
endif()

if(QT___contains___gui AND QT___contains___webenginewidgets)
    target_sources(dream PUBLIC
        src/GUI-QT/BWSViewer.cpp src/GUI-QT/BWSViewer.h src/GUI-QT/BWSViewer.ui
    )
endif()

if(UNIX)
    target_sources(dream PUBLIC
        src/linux/Pacer.cpp
    )

    target_compile_definitions(dream PRIVATE
        HAVE_DLFCN_H
        HAVE_INTTYPES_H
        HAVE_LIBZ
        HAVE_MEMORY_H
        HAVE_STDINT_H HAVE_STDINT_H
        HAVE_STDLIB_H
        HAVE_STRINGS_H
        HAVE_STRING_H
        HAVE_SYS_STAT_H
        HAVE_SYS_TYPES_H
        HAVE_UNISTD_H
        STDC_HEADERS
    )

    target_link_libraries(dream PRIVATE
        fftw3
        z
    )
endif()

if(UNIX AND NOT CMAKE_CROSSCOMPILING)
    target_compile_definitions(dream PRIVATE
        HAVE_LIBPCAP
    )

    target_link_libraries(dream PRIVATE
        pcap
    )
endif()

if(linux-_x_)
    target_link_libraries(dream PRIVATE
        dl
        rt
    )
endif()

if(fdk-aac)
    target_sources(dream PUBLIC
        src/sourcedecoders/fdk_aac_codec.cpp src/sourcedecoders/fdk_aac_codec.h
    )

    target_compile_definitions(dream PRIVATE
        HAVE_LIBFDK_AAC
        HAVE_USAC
    )

    target_link_libraries(dream PRIVATE
        fdk-aac
    )
endif()

if(opus)
    target_compile_definitions(dream PRIVATE
        HAVE_LIBOPUS
        USE_OPUS_LIBRARY
    )
endif()

if(UNIX AND opus)
    target_link_libraries(dream PRIVATE
        opus
    )
endif()

if(sndfile)
    target_compile_definitions(dream PRIVATE
        HAVE_LIBSNDFILE
    )
endif()

if(UNIX AND sndfile)
    target_link_libraries(dream PRIVATE
        sndfile1
    )
endif()

if(speexdsp)
    target_compile_definitions(dream PRIVATE
        HAVE_SPEEX
    )

    target_link_libraries(dream PRIVATE
        speexdsp
    )
endif()

if(gps)
    target_compile_definitions(dream PRIVATE
        HAVE_LIBGPS
    )
endif()

if(UNIX AND gps)
    target_link_libraries(dream PRIVATE
        gps
    )
endif()

if(hamlib)
    target_sources(dream PUBLIC
        src/util/Hamlib.cpp src/util/Hamlib.h
    )

    target_compile_definitions(dream PRIVATE
        HAVE_LIBHAMLIB
    )
endif()

if(UNIX AND hamlib)
    target_link_libraries(dream PRIVATE
        hamlib
    )
endif()

if(QT___contains___core AND hamlib)
    target_sources(dream PUBLIC
        src/util-QT/Rig.cpp src/util-QT/Rig.h
    )
endif()

if(QT___contains___gui AND hamlib)
    target_sources(dream PUBLIC
        RigDlg.ui
        src/GUI-QT/RigDlg.cpp src/GUI-QT/RigDlg.h
    )
endif()

if(qwt)
    target_link_libraries(dream PRIVATE
        Qt::Svg
    )
endif()

if((qwt) AND (unix))
    target_link_libraries(dream PRIVATE
        qwt-qt5
    )
endif()

if(((qwt) AND (NOT crosscompile)) AND (EXISTS /usr/include/qwt/qwt.h))
    target_include_directories(dream PRIVATE
        /usr/include/qwt
    )
endif()

if(((qwt) AND (NOT crosscompile)) AND (EXISTS /usr/local/include/qwt/qwt.h))
    target_include_directories(dream PRIVATE
        /usr/local/include/qwt
    )
endif()

if(alsa)
    target_sources(dream PUBLIC
        src/linux/alsacommon.cpp src/linux/alsacommon.h
        src/linux/alsain.cpp src/linux/alsain.h
        src/linux/alsaout.cpp src/linux/alsaout.h
    )

    target_compile_definitions(dream PRIVATE
        USE_ALSA
    )

    target_link_libraries(dream PRIVATE
        asound
    )
endif()

if(portaudio)
    target_sources(dream PUBLIC
        src/sound/drm_portaudio.cpp src/sound/drm_portaudio.h
        src/sound/pa_ringbuffer.c src/sound/pa_ringbuffer.h
    )

    target_compile_definitions(dream PRIVATE
        USE_PORTAUDIO
    )

    target_link_libraries(dream PRIVATE
        portaudio
    )
endif()

if(pulseaudio)
    target_sources(dream PUBLIC
        src/sound/drm_pulseaudio.cpp src/sound/drm_pulseaudio.h
    )

    target_compile_definitions(dream PRIVATE
        USE_PULSEAUDIO
    )
endif()

if(WIN32 AND pulseaudio)
    target_link_libraries(dream PRIVATE
        pulse
    )
endif()

if(soapysdr)
    target_compile_definitions(dream PRIVATE
        USE_SOAPYSDR
    )

    target_link_libraries(dream PRIVATE
        SoapySDR
    )
endif()

if(QT___contains___core)
    target_sources(dream PUBLIC
        src/GUI-QT/Logging.cpp src/GUI-QT/Logging.h
        src/main-Qt/crx.cpp src/main-Qt/crx.h
        src/main-Qt/ctrx.cpp src/main-Qt/ctrx.h
        src/main-Qt/ctx.cpp src/main-Qt/ctx.h
        src/util-QT/EPG.cpp src/util-QT/EPG.h
        src/util-QT/Util.cpp src/util-QT/Util.h
        src/util-QT/epgdec.cpp src/util-QT/epgdec.h
    )
endif()

install(TARGETS dream
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET dream
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
