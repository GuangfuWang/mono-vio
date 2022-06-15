#！/bin/bash

function vcpkg_install() {
    sudo git clone https://github.com/Microsoft/vcpkg.git
    sudo sh ./vcpkg/bootstrap-vcpkg.sh

    sudo ./vcpkg/vcpkg install eigen3
    sudo ./vcpkg/vcpkg install sophus
    sudo ./vcpkg/vcpkg install g2o
    sudo ./vcpkg/vcpkg install opencv
    sudo ./vcpkg/vcpkg install qt5
    sudo ./vcpkg/vcpkg install qt5-charts
    sudo ./vcpkg/vcpkg install yaml-cpp
}

echo "-------------Mono-VIO system dependencies installation---------------"
echo "Checking Your OS info..."
current_os=$(uname -a)

echo "Checking end, Start installation..."

if [ test -n $1 ]; then
  $cd $1
  sudo mkdir mono-vio-dependencies
  $cd ./mono-vio-dependencies
  vcpkg_install
else
  check_vcpkg_installation=$(vcpkg --version)
  if [ $? -ne 0 ]; then
      $cd ~
      sudo mkdir mono-vio-dependencies
      $cd ./mono-vio-dependencies
      vcpkg_install
  else
      sudo vcpkg install eigen3
      sudo vcpkg install sophus
      sudo vcpkg install g2o
      sudo vcpkg install opencv
      sudo vcpkg install qt5
      sudo vcpkg install qt5-charts
      sudo vcpkg install yaml-cpp
  fi
fi

sudo apt-get install -y doxygen
sudo apt-get install -y libi2c-dev i2c-tools libi2c0

echo "-------------Dependencies installation end---------------"
