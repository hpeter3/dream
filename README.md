
# dream-qt6

An experimental Qt6 port of the Dream AM/DRM Receiver program for GNU/Linux. \
Source code of the original project: https://sourceforge.net/p/drm/code/HEAD/tree/branches/dream-ollie-deployed/ \
Currently this program is tested on Fedora 42/43, Debian 13 and Arch Linux.
# Prerequisites (Qt6)
## Debian 13: 
> [!IMPORTANT]
> Enable the experimental repo: https://wiki.debian.org/DebianExperimental \
> Enable the contrib and non-free repos: https://wiki.debian.org/SourcesList#debian.sources 

### Install the following packages:
```sh
sudo apt-get install git build-essential cmake cmake-qt-gui qt6-base-dev qt6-base-dev-tools qt6-networkauth-dev qt6-declarative-dev qt6-declarative-dev-tools libqt6network6 qt6-webengine-dev libgps-dev libsndfile-dev libpcap-dev libfftw3-dev libfaad-dev libfaac-dev libpulse-dev libhamlib-dev libfdk-aac-dev libspeexdsp-dev speex libspeexdsp1 libsoapysdr-dev portaudio19-dev gpsd pipewire-alsa
```
```sh
sudo apt-get install libqt6svg6*
```
```sh
sudo apt -t experimental install libqwt-qt6-dev
```
## Fedora 42/43: 
> [!IMPORTANT]
> Enable RPM Fusion at https://rpmfusion.org/Configuration \
> Configure multimedia packages at https://rpmfusion.org/Howto/Multimedia

### Install the following packages:
```sh
sudo dnf in g++ opus-devel libsndfile-devel portaudio-devel qmake fdk-aac-devel libpcap-devel qt6-qt5compat-devel qt6-qtbase-devel qwt-qt6 qwt-qt6-devel faad2-devel faac-devel hamlib-devel gpsd-devel qt6-qtsvg-devel qt6-qtwebengine-devel fftw-devel speex-devel speexdsp-devel pulseaudio-libs-devel qt6-qttools-devel
```
## Arch Linux: 
### Install the following packages:
```sh
sudo pacman -S libsndfile portaudio fdkaac libpcap qt6-base qwt hamlib gpsd qt6-svg qt6-webengine fftw speex speexdsp qt6-tools cmake alsa-lib glibc libfdk-aac libgcc libstdc++
```
### Install the following AUR package:
```sh
yay -S qwt-qt6
```
> [!TIP]
> If you use PipeWire:
>```sh
>sudo pacman -S pipewire-pulse pipewire-alsa
>```
# Compiling with CMake (this is an example)
```sh
mkdir build
cmake -S . -B build -DUSE_QT=ON -DENABLE_SNDFILE=ON -DENABLE_SPEEXDSP=ON -DENABLE_ALSA=ON -DENABLE_QWT=ON -DENABLE_GPS=ON -DENABLE_FDK_AAC=ON -DENABLE_OPUS=ON -DENABLE_HAMLIB=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build -- -j8
cd build
```
For a complete list of CMake options, please refer to CMakeLists.txt.

# Compiling with qmake
> [!CAUTION]
> Qt6 upstream is deprecating qmake, try using CMake if possible

### qmake6 (alsa OR portaudio OR pulseaudio AND CONFIG+=sound):
```sh
qmake6 CONFIG+=alsa CONFIG+=sound
make -j8
```
# Transmitter AAC fix 
> [!CAUTION]
> This method uses an older release of the FAAD and FAAC libraries, expect incompatibilities and vulnerabilities!

> [!TIP]
> Remove all libfaad,libfaac and related packages (don't remove faad2 itself) 

## Build and install FAAD2 library
```sh
wget http://downloads.sourceforge.net/faac/faad2-2.7.tar.gz
tar zxf faad2-2.7.tar.gz
cd faad2-2.7
. bootstrap
./configure --enable-shared --without-xmms --with-drm --without-mpeg4ip
make $MAKE_ARGS
sudo cp include/faad.h include/neaacdec.h /usr/include
sudo cp libfaad/.libs/libfaad.so.2.0.0 /usr/local/lib/libfaad2_drm.so.2.0.0
sudo ln -s /usr/local/lib/libfaad2_drm.so.2.0.0 /usr/local/lib/libfaad2_drm.so.2
sudo ln -s /usr/local/lib/libfaad2_drm.so.2.0.0 /usr/local/lib/libfaad2_drm.so
cd ..
```
## Build and install FAAC library
```sh
wget http://downloads.sourceforge.net/faac/faac-1.28.tar.gz
tar zxf faac-1.28.tar.gz
cd faac-1.28
. bootstrap
./configure --with-pic --enable-shared --without-mp4v2 --enable-drm
make $MAKE_ARGS
sudo cp include/faaccfg.h  include/faac.h /usr/include
sudo cp libfaac/.libs/libfaac.so.0.0.0 /usr/local/lib/libfaac_drm.so.0.0.0
sudo ln -s /usr/local/lib/libfaac_drm.so.0.0.0 /usr/local/lib/libfaac_drm.so.0
sudo ln -s /usr/local/lib/libfaac_drm.so.0.0.0 /usr/local/lib/libfaac_drm.so
cd ..
```
[ source: https://gist.github.com/1zxLi/42e436e6ee638037d9e3060c808708fa ]
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
- Dream transmitter AAC and Opus codecs are broken (the distro packages are probably broken or have missing features)
- Compile-time errors related to Qwt on Debian 13 (use libqwt version 6.3 or later, it's in the experimental repos)
- If you encounter problems with SoapySDR, please open a new issue with full logs and outputs from the environment you're using (e.g. your terminal)
- Sometimes Dream crashes when changing the signal source or sink. If this happens, try pavucontrol.
