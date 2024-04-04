#/bin/sh

cd ../../

if [ ! -f "cmake_build" ];then
	mkdir cmake_build
fi

CMAKE=cmake
batch_file_path=$(pwd)
echo "${batch_file_path}"

cd cmake_build
Arm_Linux_Path32="./cmake_build_arm_lin32"
if [ ! -f "$Arm_Linux_Path32" ]; then
	mkdir cmake_build_arm_lin32
fi
cd cmake_build_arm_lin32
cmake ${batch_file_path} -DBUILD_ARMLINUX_32=ON -DCMAKE_GENERATOR="Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=${batch_file_path}/cmake/arm_linux_32.cmake -DCMAKE_BUILD_TYPE=Release
make -j4
cd ../../


