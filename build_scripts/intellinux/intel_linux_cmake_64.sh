#/bin/sh

cd ../../

if [ ! -f "cmake_build" ];then
	mkdir cmake_build
fi

CMAKE=cmake
batch_file_path=$(pwd)
echo "${batch_file_path}"

cd cmake_build
Linux_Path64="./cmake_build_lin64"
if [ ! -f "$Linux_Path64" ]; then
	mkdir cmake_build_lin64
fi
cd cmake_build_lin64
#make clean
rm -rf *

cmake	-DBUILD_INTEL_64=ON																\
		-DCMAKE_GENERATOR="Unix Makefiles"												\
		-DCMAKE_TOOLCHAIN_FILE=${batch_file_path}/cmake/intel_linux_64.cmake			\
		-DCMAKE_BUILD_TYPE=Release														\
		-DIPEDU_BUILD_SHARED=ON															\
		-DIPEDU_BUILD_TEST=ON															\
		${batch_file_path}
make -j
cd ../../

