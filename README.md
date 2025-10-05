
# dream-qt6

An experimental Qt6 port of the Dream AM/DRM Receiver program for GNU/Linux.
Source code of the original project: https://sourceforge.net/p/drm/code/HEAD/tree/
Currently this program is only tested on Debian 13. At the time of writing (October 5th 2025) this software is still in its original Qt5 state with only minor compile time fixes (these fixes are marked as "DEBUG2025" in the codebase).
# Prerequisites 
Before doing any of these, please enable the `contrib` and `non-free` repositories in your Debian 13 install. (Usually at /etc/apt/sources.list)
```sh
sudo apt-get install build-essential
```

```sh
sudo apt-get install libgps-dev libsndfile-dev libpcap-dev libqwt-qt5-dev libfftw3-dev libfaad-dev libfaac-dev libpulse-dev libhamlib-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools qtwebengine5-dev libqt5svg5-dev qt5-default libfdk-aac-dev libspeexdsp-dev speex libspeexdsp1 libsoapysdr-dev
```

# Compiling

```sh
qmake
make
```
# Running the program

```sh
./dream
```
