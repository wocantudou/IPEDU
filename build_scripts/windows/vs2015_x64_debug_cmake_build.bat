@echo off
set VS_BIN_PATH= "C://Program Files (x86)/Microsoft Visual Studio 14.0/Common7/IDE/devenv"
set build_type=Debug

cd ..\..
set batch_file_path=%cd%

if not exist cmake_build (
mkdir cmake_build
)


cd cmake_build
set build_dir=build_vs2015_x64_debug
if exist %build_dir% ( rd /s /q %build_dir%)
mkdir %build_dir%
cd %build_dir%
cmake %batch_file_path% -G "Visual Studio 14 2015 Win64" 			^
						-DCMAKE_BUILD_TYPE=%build_type%				^
						-DIPEDU_BUILD_SHARED=ON						^
						-DIPEDU_BUILD_TEST=ON

::%VS_BIN_PATH% ICCVP1.1.sln /Build "Debug|x64" /Project ALL_BUILD /out ./Build.log
cd %batch_file_path% 

pause