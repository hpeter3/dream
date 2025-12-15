
# dream-qt6

An experimental Qt6 port of the Dream AM/DRM Receiver program for GNU/Linux.
Source code of the original project: https://sourceforge.net/p/drm/code/HEAD/tree/
Currently this program is only tested on Fedora 42. At the time of writing (December 15th 2025) this software is in the Qt5 to Qt6 transition phase, plus additional compile time fixes (including the "DEBUG2025" fixes)

# Prerequisites (Qt6)
Debian 13:
```sh
Qwt on Debian 13 is broken, dream won't compile.
```
Fedora 42:
Enable RPM Fusion at https://rpmfusion.org/Configuration
Configure multimedia packages at https://rpmfusion.org/Howto/Multimedia

Install the following packages:
```sh
sudo dnf in g++ portaudio-devel qmake fdk-aac-devel libpcap-devel qt6-qt5compat-devel qt6-qtbase-devel qwt-qt6 qwt-qt6-devel faad2-devel faac-devel hamlib-devel gpsd-devel qt6-qtsvg-devel qt6-qtwebengine-devel fftw-devel speex-devel speexdsp-devel pulseaudio-libs-devel
```
# Compiling
qmake6 (alsa OR portaudio OR pulseaudio AND CONFIG+=sound):
```sh
qmake6 CONFIG +=alsa CONFIG+=sound
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
