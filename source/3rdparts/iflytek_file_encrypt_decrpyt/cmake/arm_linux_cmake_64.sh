#/bin/sh

cd ../../

if [ ! -f "cmake_build" ];then
	mkdir cmake_build
fi

CMAKE=cmake
batch_file_path=$(pwd)
echo "${batch_file_path}"

cd cmake_build
Arm_Linux_Path64="./cmake_build_arm_lin64"
if [ ! -f "$Arm_Linux_Path64" ]; then
	mkdir cmake_build_arm_lin64
fi
cd cmake_build_arm_lin64
cmake ${batch_file_path} -DBUILD_ARMLINUX_64=ON -DCMAKE_GENERATOR="Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=${batch_file_path}/cmake/arm_linux_64.cmake -DCMAKE_BUILD_TYPE=Release
make -j4
cd ../../


