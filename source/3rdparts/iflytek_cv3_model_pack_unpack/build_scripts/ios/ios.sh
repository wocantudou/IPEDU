#-----------------------------------------------------------------
# Cmake build for iOS while -DMAXENGINE_PLATFORM="ios", with
# -IOS_PLATFOEM=OS, for armv7 armv7s arm64 arm64e (if applicable);
# -IOS_PLATFORM=SIMULATOR, for i386 x86_64;
#-----------------------------------------------------------------

cd ../../
if [ ! -f "cmake_build" ];then
	mkdir cmake_build
fi

CMAKE=cmake
batch_file_path=$(pwd)
echo "${batch_file_path}"

cd cmake_build
IOS_Path64="./cmake_build_ios64"
if [ ! -f "$IOS_Path64" ]; then
	mkdir cmake_build_ios64
fi
cd cmake_build_ios64

cmake ${batch_file_path} -DBUILD_IOS64=ON -DCMAKE_TOOLCHAIN_FILE=${batch_file_path}/cmake/ios.toolchain.cmake -DIOS_PLATFORM=OS

make clean
make -j

