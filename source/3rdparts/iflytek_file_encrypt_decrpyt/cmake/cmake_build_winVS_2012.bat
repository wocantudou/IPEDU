@echo off

cd ..

if not exist cmake_build (
mkdir cmake_build
)
cd cmake_build


if exist build_vs_32 ( rd /s /q build_vs_32)
mkdir build_vs_32
cd build_vs_32
cmake ../../cmake -G "Visual Studio 11 2012"
cd ..
devenv.com ./build_vs_32/ENCRYPT.sln /Rebuild "Release|Win32"

if exist build_vs_64 ( rd /s /q build_vs_64)
mkdir build_vs_64
cd build_vs_64
cmake ../../cmake -G "Visual Studio 11 2012 Win64"
cd ..
devenv.com ./build_vs_64/ENCRYPT.sln /Rebuild "Release|x64"

cd ../cmake
pause