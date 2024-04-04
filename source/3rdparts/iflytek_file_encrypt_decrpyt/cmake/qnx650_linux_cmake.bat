call D:\QNX650\qnx650-env.bat 

cd ..

if not exist cmake_build (
mkdir cmake_build
)
cd cmake_build

if exist cmake_build_qnx650 ( rd /s /q cmake_build_qnx650)
mkdir cmake_build_qnx650
cd cmake_build_qnx650

set toolchain=..\..\cmake\qnx_win.cmake

set gernerator="Unix Makefiles"

cmake ../../cmake -DENCRYPT_BUILD_QNX650=ON -DCMAKE_GENERATOR=%gernerator% -DCMAKE_TOOLCHAIN_FILE=%toolchain%
make clean
make -j