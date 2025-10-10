cmake_minimum_required(VERSION 3.16)
project(DreamTests VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Gui Test)

qt_standard_project_setup()

qt_add_executable(DreamTests WIN32 MACOSX_BUNDLE
    ../src/AMDemodulation.cpp
    ../src/AMSSDemodulation.cpp
    ../src/DRMSignalIO.cpp
    ../src/DataIO.cpp
    ../src/DrmReceiver.cpp
    ../src/DrmSimulation.cpp
    ../src/DrmTransceiver.cpp
    ../src/DrmTransmitter.cpp
    ../src/FAC/FAC.cpp
    ../src/IQInputFilter.cpp
    ../src/InputResample.cpp
    ../src/MDI/AFPacketGenerator.cpp
    ../src/MDI/MDIDecode.cpp
    ../src/MDI/MDIInBuffer.cpp
    ../src/MDI/MDIRSCI.cpp
    ../src/MDI/MDITagItemDecoders.cpp
    ../src/MDI/MDITagItems.cpp
    ../src/MDI/PacketSinkFile.cpp
    ../src/MDI/PacketSocket.cpp
    ../src/MDI/PacketSourceFile.cpp
    ../src/MDI/Pft.cpp
    ../src/MDI/RCITagItems.cpp
    ../src/MDI/RSCITagItemDecoders.cpp
    ../src/MDI/RSISubscriber.cpp
    ../src/MDI/TagPacketDecoder.cpp
    ../src/MDI/TagPacketDecoderMDI.cpp
    ../src/MDI/TagPacketDecoderRSCIControl.cpp
    ../src/MDI/TagPacketGenerator.cpp
    ../src/MSC/aacsuperframe.cpp
    ../src/MSC/audiosuperframe.cpp
    ../src/MSC/frameborderdescription.cpp
    ../src/MSC/logicalframe.cpp
    ../src/MSC/xheaacsuperframe.cpp
    ../src/MSCMultiplexer.cpp
    ../src/OFDM.cpp
    ../src/Parameter.cpp
    ../src/PlotManager.cpp
    ../src/ReceptLog.cpp
    ../src/SDC/SDCReceive.cpp
    ../src/SDC/SDCTransmit.cpp
    ../src/SDC/audioparam.cpp
    ../src/Scheduler.cpp
    ../src/ServiceInformation.cpp
    ../src/SimulationParameters.cpp
    ../src/TextMessage.cpp
    ../src/Version.cpp
    ../src/chanest/ChanEstTime.cpp
    ../src/chanest/ChannelEstimation.cpp
    ../src/chanest/IdealChannelEstimation.cpp
    ../src/chanest/TimeLinear.cpp
    ../src/chanest/TimeWiener.cpp
    ../src/datadecoding/DABMOT.cpp
    ../src/datadecoding/DataDecoder.cpp
    ../src/datadecoding/DataEncoder.cpp
    ../src/datadecoding/Experiment.cpp
    ../src/datadecoding/Journaline.cpp
    ../src/datadecoding/MOTSlideShow.cpp
    ../src/datadecoding/epgutil.cpp
    ../src/datadecoding/journaline/NML.cpp
    ../src/datadecoding/journaline/Splitter.cpp
    ../src/datadecoding/journaline/crc_8_16.c
    ../src/datadecoding/journaline/dabdgdec_impl.c
    ../src/datadecoding/journaline/log.c
    ../src/datadecoding/journaline/newsobject.cpp
    ../src/datadecoding/journaline/newssvcdec_impl.cpp
    ../src/drmchannel/ChannelSimulation.cpp
    ../src/interleaver/BlockInterleaver.cpp
    ../src/interleaver/SymbolInterleaver.cpp
    ../src/matlib/MatlibSigProToolbox.cpp
    ../src/matlib/MatlibStdToolbox.cpp
    ../src/mlc/BitInterleaver.cpp
    ../src/mlc/ChannelCode.cpp
    ../src/mlc/ConvEncoder.cpp
    ../src/mlc/EnergyDispersal.cpp
    ../src/mlc/MLC.cpp
    ../src/mlc/Metric.cpp
    ../src/mlc/QAMMapping.cpp
    ../src/mlc/TrellisUpdateMMX.cpp
    ../src/mlc/TrellisUpdateSSE2.cpp
    ../src/mlc/ViterbiDecoder.cpp
    ../src/ofdmcellmapping/CellMappingTable.cpp
    ../src/ofdmcellmapping/OFDMCellMapping.cpp
    ../src/resample/Resample.cpp
    ../src/resample/ResampleFilter.cpp
    ../src/resample/caudioresample.cpp
    ../src/resample/cspectrumresample.cpp
    ../src/resample/speexresampler.cpp
    ../src/sound/audiofilein.cpp
    ../src/sound/selectioninterface.cpp
    ../src/sound/soundinterface.cpp
    ../src/sound/soundnull.cpp
    ../src/sourcedecoders/AudioCodec.cpp
    ../src/sourcedecoders/AudioSourceDecoder.cpp
    ../src/sourcedecoders/AudioSourceEncoder.cpp
    ../src/sourcedecoders/aac_codec.cpp
    ../src/sourcedecoders/caudioreverb.cpp
    ../src/sourcedecoders/null_codec.cpp
    ../src/sourcedecoders/opus_codec.cpp
    ../src/sourcedecoders/reverb.cpp
    ../src/sync/FreqSyncAcq.cpp
    ../src/sync/SyncUsingPil.cpp
    ../src/sync/TimeSync.cpp
    ../src/sync/TimeSyncFilter.cpp
    ../src/sync/TimeSyncTrack.cpp
    ../src/tables/TableCarMap.cpp
    ../src/tables/TableFAC.cpp
    ../src/tables/TableStations.cpp
    ../src/util/CRC.cpp
    ../src/util/FileTyper.cpp
    ../src/util/LogPrint.cpp
    ../src/util/Reassemble.cpp
    ../src/util/Settings.cpp
    ../src/util/Utilities.cpp
    tst_receiverinputchangetest.cpp
)
target_include_directories(DreamTests PRIVATE
    /usr/local/include
)

target_link_directories(DreamTests PRIVATE
    /usr/local/lib
)

target_link_libraries(DreamTests PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Test
    fftw3
    speexdsp
    z
)

if(UNIX)
    target_sources(DreamTests PUBLIC
        ../src/linux/Pacer.cpp
    )
endif()

if(WIN32)
    target_sources(DreamTests PUBLIC
        ../src/windows/Pacer.cpp
    )
endif()

install(TARGETS DreamTests
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET DreamTests
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
