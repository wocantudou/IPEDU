source /usr/local/oecore-x86_64/environment-setup-aarch64-poky-linux

cd ..
if [ ! -f "cmake_build" ];then
mkdir cmake_build
fi
cd cmake_build
Linux_Path64="./cmake_build_cortex"
if [ ! -f "$Path" ]; then
mkdir cmake_build_cortex
fi
cd cmake_build_cortex

cmake ../../cmake -DENCRYPT_BUILD_CORTEX=ON -DCMAKE_GENERATOR="Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$(pwd)/../../cmake/cortex_intel.cmake
make -j
