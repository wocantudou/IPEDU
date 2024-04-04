#-----------------------------------------------------------------
# 172.20.31.106
#-----------------------------------------------------------------
NDK_ROOT=/data/boshao/android-ndk-r16b
#NDK_ROOT=/home/wensha2/tools/android-ndk-r16b
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


#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/${engine_name_with_version}
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/libiflyFaceTrack_shared.so
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/libiflyFaceRetrieval_shared.so
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/libmaxengine.so
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/DSMTest
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/DSMTestUnit
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/DSMSample
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/DSMRetrievalTest
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/DSMTrackTest
#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/MaxEngineLiteTest

if [ ${use_softdog} == "ON" ];then
	echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ use softdog ..."
	#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/licenceTest
	#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/iCloudSdkTest
	#${NDK_ROOT}/toolchains/arm-linux-androideabi-4.9/prebuilt/linux-x86_64/bin/arm-linux-androideabi-strip ./output/bin/armeabi-v7a/restClientTest
else
	echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@not use softdog ..."
fi

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




cmake	-DBUILD_ARM64_V8A=ON                                \
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
		"../../"

#make clean
make -j

cd "../../"
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/${engine_name_with_version}
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/libiflyFaceTrack_shared.so
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/libiflyFaceRetrieval_shared.so
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/libmaxengine.so
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/DSMTest
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/DSMTestUnit
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/DSMSample
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/DSMRetrievalTest
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/DSMTrackTest
#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/MaxEngineLiteTest
if [ ${use_softdog} == "ON" ];then
	echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ use softdog ..."
	#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/licenceTest
	#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/iCloudSdkTest
	#${NDK_ROOT}/toolchains/aarch64-linux-android-4.9/prebuilt/linux-x86_64/bin/aarch64-linux-android-strip ./output/bin/arm64-v8a/restClientTest
else
	echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@not use softdog ..."
fi

echo "################################################## Make Build Target #################"

rm -rf BuildTarget

mkdir -p BuildTarget/bin/armeabi-v7a/output/track_res
touch BuildTarget/bin/armeabi-v7a/output/track_res/.gitkeep
mkdir -p BuildTarget/bin/arm64-v8a/output/track_res
touch BuildTarget/bin/arm64-v8a/output/track_res/.gitkeep
mkdir -p BuildTarget/cfg
mkdir -p BuildTarget/cfu
mkdir -p BuildTarget/data
mkdir -p BuildTarget/doc
mkdir -p BuildTarget/include/
mkdir -p BuildTarget/log
mkdir -p BuildTarget/model
mkdir -p BuildTarget/samples


cp -r output/bin/armeabi-v7a/*.so BuildTarget/bin/armeabi-v7a
if [ ${use_dlopen} == "OFF" ] ; then
    echo 'use_dlopen = OFF!'
	rm -rf BuildTarget/bin/armeabi-v7a/libmaxengine.*
	#rm -rf BuildTarget/bin/armeabi-v7a/libiflyFaceTrack_shared.so
fi
cp -r output/bin/armeabi-v7a/*.txt BuildTarget/bin/armeabi-v7a
cp -r output/bin/armeabi-v7a/DSMTest BuildTarget/bin/armeabi-v7a
cp -r output/bin/armeabi-v7a/DSMTestUnit BuildTarget/bin/armeabi-v7a
cp -r output/bin/armeabi-v7a/DSMSample BuildTarget/bin/armeabi-v7a
cp -r output/bin/armeabi-v7a/MaxEngineLiteTest BuildTarget/bin/armeabi-v7a
cp -r output/bin/armeabi-v7a/DSMTrackTest BuildTarget/bin/armeabi-v7a
cp -r output/bin/armeabi-v7a/DSMRetrievalTest BuildTarget/bin/armeabi-v7a
if [ ${use_softdog} == "ON" ];then
	echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ use softdog ..."
	#cp -r output/bin/armeabi-v7a/licenceTest BuildTarget/bin/armeabi-v7a
	#cp -r output/bin/armeabi-v7a/iCloudSdkTest BuildTarget/bin/armeabi-v7a
	#cp -r output/bin/armeabi-v7a/restClientTest BuildTarget/bin/armeabi-v7a
else
    echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@not use softdog ..."
fi

cp -r output/bin/arm64-v8a/*.so BuildTarget/bin/arm64-v8a
if [ ${use_dlopen} == "OFF" ] ; then
    echo 'use_dlopen = OFF!'
	rm -rf BuildTarget/bin/arm64-v8a/libmaxengine.*
	#rm -rf BuildTarget/bin/arm64-v8a/libiflyFaceTrack_shared.so
fi
cp -r output/bin/arm64-v8a/*.txt BuildTarget/bin/arm64-v8a
cp -r output/bin/arm64-v8a/DSMTest BuildTarget/bin/arm64-v8a
cp -r output/bin/arm64-v8a/DSMTestUnit BuildTarget/bin/arm64-v8a
cp -r output/bin/arm64-v8a/DSMSample BuildTarget/bin/arm64-v8a
cp -r output/bin/arm64-v8a/MaxEngineLiteTest BuildTarget/bin/arm64-v8a
cp -r output/bin/arm64-v8a/DSMTrackTest BuildTarget/bin/arm64-v8a
cp -r output/bin/arm64-v8a/DSMRetrievalTest BuildTarget/bin/arm64-v8a
if [ ${use_softdog} == "ON" ];then
	echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ use softdog ..."
	#cp -r output/bin/arm64-v8a/licenceTest BuildTarget/bin/arm64-v8a
	#cp -r output/bin/arm64-v8a/iCloudSdkTest BuildTarget/bin/arm64-v8a
	#cp -r output/bin/arm64-v8a/restClientTest BuildTarget/bin/arm64-v8a
else
	echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@not use softdog ..."
fi

cp -r output/cfg/iflyDSM.cfg BuildTarget/cfg
cp -r output/cfg/iflyDSM.cfg.int8 BuildTarget/cfg
cp -r output/cfu/iflyDSMLog.cfu BuildTarget/cfu


cp -r output/data/tmp BuildTarget/data
cp -r output/data/64_64_face BuildTarget/data
cp -r output/data/test_gaze BuildTarget/data
cp -r output/data/smoke_call BuildTarget/data
cp -r output/data/test_track BuildTarget/data
cp -r output/data/sbd BuildTarget/data
cp -r output/data/pet BuildTarget/data
cp -r output/data/material BuildTarget/data

cp -r output/doc/*.txt BuildTarget/doc
cp -r output/doc/*.pdf BuildTarget/doc

cp -r source/include/errcode_module.h BuildTarget/include
cp -r source/include/iflyDSM_all_type.h BuildTarget/include
cp -r source/DSMRuntimeApi/iflyDSMRuntime_api.h BuildTarget/include
cp -r source/DSMFaceModule/iflyFaceTrack/iflyFaceTrack_api.h BuildTarget/include
cp -r source/DSMFaceModule/iflyFaceRetrieval/iflyFaceRetrieval_api.h BuildTarget/include


cp -r output/model/max_engine_lite_model_pack_encrypt BuildTarget/model

cp -r ./source/DSMTest/DSMTest/*.cpp ./BuildTarget/samples/

#rm -rf BuildTarget.zip
#zip -r ./BuildTarget.zip ./BuildTarget/
