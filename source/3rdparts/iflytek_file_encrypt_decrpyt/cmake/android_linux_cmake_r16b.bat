set android_ndk=E:\softwares\android_ndk\from_dfmlp\android-ndk-r16b-windows-x86_64\android-ndk-r16b
set toolchain=%android_ndk%\build\cmake\android.toolchain.cmake
set build_type=Release
set gernerator="Ninja"
set android_platform=android-17
set android_arm_neon=TRUE
set android_stl=c++_static
set androidchain=gcc

cd ..
if not exist cmake_build (
mkdir cmake_build
)
cd cmake_build

set android_abi=armeabi
set dir_prefix=build_android_libs_
if exist %dir_prefix%%android_abi% ( rd /s /q %dir_prefix%%android_abi%)
mkdir %dir_prefix%%android_abi%
cd %dir_prefix%%android_abi%
cmake ../../cmake -DBUILD_ARMEABI=ON -DANDROID_ABI=%android_abi% -DCMAKE_TOOLCHAIN_FILE=%toolchain% -DANDROID_NDK=%android_ndk% -DANDROID_PLATFORM=%android_platform% -DCMAKE_BUILD_TYPE=%build_type% -DCMAKE_GENERATOR=%gernerator% -DANDROID_ARM_NEON=%android_arm_neon% -DANDROID_STL=%android_stl% -DANDROID_TOOLCHAIN=%androidchain%
ninja clean
ninja
cd ..


set android_abi=armeabi-v7a
set dir_prefix=build_android_libs_
if exist %dir_prefix%%android_abi% ( rd /s /q %dir_prefix%%android_abi%)
mkdir %dir_prefix%%android_abi%
cd %dir_prefix%%android_abi%
cmake ../../cmake -DBUILD_ARMEABI_V7A=ON -DANDROID_ABI=%android_abi% -DCMAKE_TOOLCHAIN_FILE=%toolchain% -DANDROID_NDK=%android_ndk% -DANDROID_PLATFORM=%android_platform% -DCMAKE_BUILD_TYPE=%build_type% -DCMAKE_GENERATOR=%gernerator% -DANDROID_ARM_NEON=%android_arm_neon% -DANDROID_STL=%android_stl% -DANDROID_TOOLCHAIN=%androidchain%
ninja clean
ninja
cd ..

set android_abi=arm64-v8a
set dir_prefix=build_android_libs_
if exist %dir_prefix%%android_abi% ( rd /s /q %dir_prefix%%android_abi%)
mkdir %dir_prefix%%android_abi%
cd %dir_prefix%%android_abi%
cmake ../../cmake -DBUILD_ARM64_V8A=ON -DANDROID_ABI=%android_abi% -DCMAKE_TOOLCHAIN_FILE=%toolchain% -DANDROID_NDK=%android_ndk% -DANDROID_PLATFORM=%android_platform% -DCMAKE_BUILD_TYPE=%build_type% -DCMAKE_GENERATOR=%gernerator% -DANDROID_ARM_NEON=%android_arm_neon% -DANDROID_STL=%android_stl% -DANDROID_TOOLCHAIN=%androidchain%
ninja clean
ninja
cd ..

set android_abi=x86
set dir_prefix=build_android_libs_
if exist %dir_prefix%%android_abi% ( rd /s /q %dir_prefix%%android_abi%)
mkdir %dir_prefix%%android_abi%
cd %dir_prefix%%android_abi%
cmake ../../cmake -DBUILD_X86=ON -DANDROID_ABI=%android_abi% -DCMAKE_TOOLCHAIN_FILE=%toolchain% -DANDROID_NDK=%android_ndk% -DANDROID_PLATFORM=%android_platform% -DCMAKE_BUILD_TYPE=%build_type% -DCMAKE_GENERATOR=%gernerator% -DANDROID_ARM_NEON=%android_arm_neon% -DANDROID_STL=%android_stl% -DANDROID_TOOLCHAIN=%androidchain%
ninja clean
ninja
cd ..

set android_abi=x86_64
set dir_prefix=build_android_libs_
if exist %dir_prefix%%android_abi% ( rd /s /q %dir_prefix%%android_abi%)
mkdir %dir_prefix%%android_abi%
cd %dir_prefix%%android_abi%
cmake ../../cmake -DBUILD_X86_64=ON -DANDROID_ABI=%android_abi% -DCMAKE_TOOLCHAIN_FILE=%toolchain% -DANDROID_NDK=%android_ndk% -DANDROID_PLATFORM=%android_platform% -DCMAKE_BUILD_TYPE=%build_type% -DCMAKE_GENERATOR=%gernerator% -DANDROID_ARM_NEON=%android_arm_neon% -DANDROID_STL=%android_stl% -DANDROID_TOOLCHAIN=%androidchain%
ninja clean
ninja
cd ..

set android_abi=mips
set dir_prefix=build_android_libs_
if exist %dir_prefix%%android_abi% ( rd /s /q %dir_prefix%%android_abi%)
mkdir %dir_prefix%%android_abi%
cd %dir_prefix%%android_abi%
cmake ../../cmake -DBUILD_MIPS=ON -DANDROID_ABI=%android_abi% -DCMAKE_TOOLCHAIN_FILE=%toolchain% -DANDROID_NDK=%android_ndk% -DANDROID_PLATFORM=%android_platform% -DCMAKE_BUILD_TYPE=%build_type% -DCMAKE_GENERATOR=%gernerator% -DANDROID_ARM_NEON=%android_arm_neon% -DANDROID_STL=%android_stl% -DANDROID_TOOLCHAIN=%androidchain%
ninja clean
ninja
cd ..

set android_abi=mips64
set dir_prefix=build_android_libs_
if exist %dir_prefix%%android_abi% ( rd /s /q %dir_prefix%%android_abi%)
mkdir %dir_prefix%%android_abi%
cd %dir_prefix%%android_abi%
cmake ../../cmake -DBUILD_MIPS64=ON -DANDROID_ABI=%android_abi% -DCMAKE_TOOLCHAIN_FILE=%toolchain% -DANDROID_NDK=%android_ndk% -DANDROID_PLATFORM=%android_platform% -DCMAKE_BUILD_TYPE=%build_type% -DCMAKE_GENERATOR=%gernerator% -DANDROID_ARM_NEON=%android_arm_neon% -DANDROID_STL=%android_stl% -DANDROID_TOOLCHAIN=%androidchain%
ninja clean
ninja
cd ..

pause
