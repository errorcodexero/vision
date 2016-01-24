
echo "Need root access";
sudo apt-get install cmake-gui;
sudo apt-get remove ffmpeg x264 libx264-dev;
sudo apt-get update;
sudo apt-get install build-essential checkinstall git cmake libfaac-dev libjack-jackd2-dev libmp3lame-dev libopencore-amrnb-dev libopencore-amrwb-dev libsdl1.2-dev libtheora-dev libva-dev libvdpau-dev libvorbis-dev libx11-dev libxfixes-dev libxvidcore-dev texi2html yasm zlib1g-dev;
sudo apt-get install libgstreamer0.10-0 libgstreamer0.10-dev gstreamer0.10-tools gstreamer0.10-plugins-base libgstreamer-plugins-base0.10-dev gstreamer0.10-plugins-good gstreamer0.10-plugins-ugly gstreamer0.10-plugins-bad gstreamer0.10-ffmpeg;
sudo apt-get install libgtk2.0-0 libgtk2.0-dev;
sudo apt-get install libjpeg8 libjpeg8-dev;
cd ~;
mkdir src;
cd ~/src;
sudo wget https://github.com/Itseez/opencv/archive/2.4.11.zip;
sudo unzip ./2.4.11.zip;
cd opencv-2.4.11;
echo "Enter the valid options into CMake Gui, and press generate"
sudo cmake-gui;
make;
sudo make install;
