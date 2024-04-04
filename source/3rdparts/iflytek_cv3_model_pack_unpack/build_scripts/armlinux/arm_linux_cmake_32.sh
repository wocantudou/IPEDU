#/bin/sh
cd ../../

if [ ! -f "cmake_build" ];then
	mkdir cmake_build
fi

CMAKE=cmake
batch_file_path=$(pwd)
echo "${batch_file_path}"

cd cmake_build
Arm_Linux_Path32="./cmake_build_arm_lin32"
if [ ! -f "$Arm_Linux_Path32" ]; then
	mkdir cmake_build_arm_lin32
fi
cd cmake_build_arm_lin32

cmake	-DBUILD_ARMLINUX_32=ON															\
		-DCMAKE_GENERATOR="Unix Makefiles"												\
		-DCMAKE_TOOLCHAIN_FILE=${batch_file_path}/cmake/arm_linux_32.cmake				\
		-DCMAKE_BUILD_TYPE=Release														\
		-DIPUP_BUILD_SHARED=ON															\
		-DIPUP_BUILD_TEST=ON															\
		${batch_file_path}
make -j
cd ../../


echo "################################################## Make Build Target #################"

rm -rf BuildTarget

mkdir -p BuildTarget/bin/armlinux32/output/track_res
touch BuildTarget/bin/armlinux32/output/track_res/.gitkeep
mkdir -p BuildTarget/cfg
mkdir -p BuildTarget/cfu
mkdir -p BuildTarget/data
mkdir -p BuildTarget/doc
mkdir -p BuildTarget/include/
mkdir -p BuildTarget/log
mkdir -p BuildTarget/model
mkdir -p BuildTarget/samples


cp -r output/bin/armlinux32/*.so* BuildTarget/bin/armlinux32

if [ ${use_dlopen} == "OFF" ] ; then
    echo 'use_dlopen = OFF!'
	rm -rf BuildTarget/bin/armlinux32/libmaxengine.*
	#rm -rf BuildTarget/bin/armlinux32/libiflyFaceTrack_shared.so
fi


cp -r output/bin/armlinux32/*.txt BuildTarget/bin/armlinux32

cp -r output/bin/armlinux32/DSMTest BuildTarget/bin/armlinux32
cp -r output/bin/armlinux32/DSMSample BuildTarget/bin/armlinux32
cp -r output/bin/armlinux32/DSMTestUnit BuildTarget/bin/armlinux32
cp -r output/bin/armlinux32/MaxEngineLiteTest BuildTarget/bin/armlinux32
cp -r output/bin/armlinux32/DSMTrackTest BuildTarget/bin/armlinux32
cp -r output/bin/armlinux32/DSMRetrievalTest BuildTarget/bin/armlinux32

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
cp -r source/DSMPythonApi/dsmpy.h BuildTarget/include

cp -r output/model/max_engine_lite_model_pack_encrypt BuildTarget/model

cp -r ./source/DSMTest/DSMTest/*.cpp ./BuildTarget/samples/

#rm -rf BuildTarget.zip
#zip -r ./BuildTarget.zip ./BuildTarget/
