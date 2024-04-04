cd ..
if [ ! -f "cmake_build" ];then
mkdir cmake_build
fi
cd cmake_build
Linux_Path64="./cmake_build_lin64"
if [ ! -f "$Path" ]; then
mkdir cmake_build_lin64
fi
cd cmake_build_lin64

cmake ../../cmake -DBUILD_INTEL_64=ON -DCMAKE_GENERATOR="Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=$(pwd)/../../cmake/intel_linux_64.cmake
make -j

