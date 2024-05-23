#-----------------------------------------------------------------
# 172.20.31.106
#-----------------------------------------------------------------
# NDK_ROOT=/data/boshao/android-ndk-r16b
#NDK_ROOT=/home/wensha2/tools/android-ndk-r16b
#-----------------------------------------------------------------
# WSL2
#-----------------------------------------------------------------
NDK_ROOT=/home/wensha2/workspace/toolchain/android-ndk-r16b
android_ndk=${NDK_ROOT}
toolchain=${NDK_ROOT}/build/cmake/android.toolchain.cmake
build_type=Release
#gernerator="Ninja"
#android_platform=android-19
#android_platform=android-21
android_platform=android-17
android_arm_neon=ON
#android_stl=gnustl_static
android_stl=c++_static
#androidchain=gcc
androidchain=clang


cd "../../"

#################################################armeabi-v7a
PWD=`pwd`
echo "PWD = ${PWD}"
cd "${PWD}"
if [ ! -d "cmake_build" ];then
    mkdir cmake_build
fi

cd "cmake_build"

android_abi=armeabi-v7a
dir_prefix=build_android_libs_
if [ ! -d "${dir_prefix}${android_abi}" ];then
    mkdir "${dir_prefix}${android_abi}"
fi

cd "${dir_prefix}${android_abi}"
PWD=`pwd`
echo "##################################################PWD = ${PWD}"

cmake	-DBUILD_ARMEABI_V7A=ON                              \
		-DANDROID_ABI=${android_abi}                        \
		-DCMAKE_TOOLCHAIN_FILE=${toolchain}                 \
		-DANDROID_NDK=${android_ndk}                        \
		-DANDROID_PLATFORM=${android_platform}              \
		-DCMAKE_BUILD_TYPE=${build_type}                    \
		-DANDROID_ARM_NEON=${android_arm_neon}              \
		-DANDROID_STL=${android_stl}                        \
		-DANDROID_TOOLCHAIN=${androidchain}					\
		-DIPUP_BUILD_SHARED=ON								\
		-DIPUP_BUILD_TEST=ON								\
		../../

#make clean
make -j

cd "../../"

#################################################arm64-v8a
PWD=`pwd`
echo "PWD = ${PWD}"
cd "${PWD}"
if [ ! -d "cmake_build" ];then
    mkdir cmake_build
fi

cd "cmake_build"

android_abi=arm64-v8a
dir_prefix=build_android_libs_
if [ ! -d "${dir_prefix}${android_abi}" ];then
    mkdir "${dir_prefix}${android_abi}"
fi

cd "${dir_prefix}${android_abi}"
PWD=`pwd`
echo "##################################################PWD = ${PWD}"

cmake	-DANDROID_ABI=${android_abi}                        \
		-DCMAKE_TOOLCHAIN_FILE=${toolchain}                 \
		-DANDROID_NDK=${android_ndk}                        \
		-DANDROID_PLATFORM=${android_platform}              \
		-DCMAKE_BUILD_TYPE=${build_type}                    \
		-DANDROID_ARM_NEON=${android_arm_neon}              \
		-DANDROID_STL=${android_stl}                        \
		-DANDROID_TOOLCHAIN=${androidchain}					\
		-DIPUP_BUILD_SHARED=ON								\
		-DIPUP_BUILD_TEST=ON								\
		"../../"

#make clean
make -j

cd "../../"
