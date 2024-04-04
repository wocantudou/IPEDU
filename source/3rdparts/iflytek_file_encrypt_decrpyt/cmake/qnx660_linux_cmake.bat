call D:\qnx660\qnx660-env.bat 

cd ..

if not exist cmake_build (
mkdir cmake_build
)
cd cmake_build

if exist cmake_build_qnx660 ( rd /s /q cmake_build_qnx660)
mkdir cmake_build_qnx660
cd cmake_build_qnx660

set toolchain=..\..\cmake\qnx_win.cmake

set gernerator="Unix Makefiles"

cmake ../../cmake -DENCRYPT_BUILD_QNX660=ON -DCMAKE_GENERATOR=%gernerator% -DCMAKE_TOOLCHAIN_FILE=%toolchain%
make clean
make -j