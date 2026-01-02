
# dream-qt6

An experimental Qt6 port of the Dream AM/DRM Receiver program for GNU/Linux. \
Source code of the original project: https://sourceforge.net/p/drm/code/HEAD/tree/branches/dream-ollie-deployed/ \
Currently this program is only tested on Fedora 42. \
Status as of January 2nd 2026: There's no need for the Qt5 compatibility APIs anymore, however lots of deprecated Qt4 and Qt5 code remains, TODO! \
# Prerequisites (Qt6)
Debian 13: \
Enable the experimental repo:
```sh
https://wiki.debian.org/DebianExperimental
```
Enable the contrib and non-free repos:
```sh
https://wiki.debian.org/SourcesList#debian.sources
```
Install the following packages:
```sh
sudo apt-get install git build-essential cmake cmake-qt-gui qt6-base-dev qt6-base-dev-tools qt6-networkauth-dev qt6-declarative-dev qt6-declarative-dev-tools libqt6network6 qt6-webengine-dev libgps-dev libsndfile-dev libpcap-dev libfftw3-dev libfaad-dev libfaac-dev libpulse-dev libhamlib-dev libfdk-aac-dev libspeexdsp-dev speex libspeexdsp1 libsoapysdr-dev portaudio19-dev gpsd pipewire-alsa
```
```sh
sudo apt-get install libqt6svg6*
```
```sh
sudo apt -t experimental install libqwt-qt6-dev
```
Fedora 42: \
Enable RPM Fusion at https://rpmfusion.org/Configuration \
Configure multimedia packages at https://rpmfusion.org/Howto/Multimedia

Install the following packages:
```sh
sudo dnf in g++ opus-devel libsndfile-devel portaudio-devel qmake fdk-aac-devel libpcap-devel qt6-qt5compat-devel qt6-qtbase-devel qwt-qt6 qwt-qt6-devel faad2-devel faac-devel hamlib-devel gpsd-devel qt6-qtsvg-devel qt6-qtwebengine-devel fftw-devel speex-devel speexdsp-devel pulseaudio-libs-devel qt6-qttools-devel
```
# Compiling with CMake (newer, expect bugs, this is an example)
```sh
mkdir build
cmake -S . -B build -DUSE_QT=ON -DENABLE_SNDFILE=ON -DENABLE_SPEEXDSP=ON -DENABLE_ALSA=ON -DENABLE_QWT=ON -DENABLE_GPS=ON -DENABLE_FDK_AAC=ON -DENABLE_OPUS=ON -DENABLE_HAMLIB=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build -- -j8
cd build
```

# Compiling with qmake (older)
qmake6 (alsa OR portaudio OR pulseaudio AND CONFIG+=sound):
```sh
qmake6 CONFIG+=alsa CONFIG+=sound
make -j8
```
# Running the program

Receiver:
```sh
./dream
```

Transmitter:
```sh
./dream -t
```
# Known bugs
- Dream transmitter AAC and Opus codecs are broken (the distro packages are probably broken or have missing features, TODO!)
- Compile-time errors related to Qwt on Debian 13 (use libqwt version 6.3 or later, it's in the experimental repos)
