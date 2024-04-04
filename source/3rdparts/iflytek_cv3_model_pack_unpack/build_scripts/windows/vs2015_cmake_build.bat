@echo off
set VS_BIN_PATH= "C://Program Files (x86)/Microsoft Visual Studio 14.0/Common7/IDE/devenv"
set build_type=Debug

cd ..\..
set batch_file_path=%cd%

if not exist cmake_build (
mkdir cmake_build
)


cd cmake_build
if exist build_vs2015_64 ( rd /s /q build_vs2015_64)
mkdir build_vs2015_64
cd build_vs2015_64
cmake %batch_file_path% -G "Visual Studio 14 2015 Win64" 	^
						-DCMAKE_BUILD_TYPE=%build_type%		^
						-DIPUP_BUILD_SHARED=ON				^
						-DIPUP_BUILD_TEST=ON

::%VS_BIN_PATH% maxengine.sln /ReBuild "Release|x64" /Project ALL_BUILD /out ./Build.log
::%VS_BIN_PATH% maxengine.sln /Build "Debug|x64" /Project ALL_BUILD /out ./Build.log

cd %batch_file_path% 
pause