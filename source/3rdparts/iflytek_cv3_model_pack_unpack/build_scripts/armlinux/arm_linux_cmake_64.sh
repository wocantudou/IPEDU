#/bin/sh
cd ../../

if [ ! -f "cmake_build" ];then
	mkdir cmake_build
fi

CMAKE=cmake
batch_file_path=$(pwd)
echo "${batch_file_path}"

cd cmake_build
Arm_Linux_Path64="./cmake_build_arm_lin64"
if [ ! -f "$Arm_Linux_Path64" ]; then
	mkdir cmake_build_arm_lin64
fi
cd cmake_build_arm_lin64

cmake	-DBUILD_ARMLINUX_64=ON															\
		-DCMAKE_GENERATOR="Unix Makefiles"												\
		-DCMAKE_TOOLCHAIN_FILE=${batch_file_path}/cmake/arm_linux_64.cmake				\
		-DCMAKE_BUILD_TYPE=Release														\
		-DIPUP_BUILD_SHARED=ON															\
		-DIPUP_BUILD_TEST=ON															\
		${batch_file_path}
make -j
cd ../../


echo "################################################## Make Build Target #################"

rm -rf BuildTarget

mkdir -p BuildTarget/bin/armlinux64/output/track_res
touch BuildTarget/bin/armlinux64/output/track_res/.gitkeep
mkdir -p BuildTarget/cfg
mkdir -p BuildTarget/cfu
mkdir -p BuildTarget/data
mkdir -p BuildTarget/doc
mkdir -p BuildTarget/include/
mkdir -p BuildTarget/log
mkdir -p BuildTarget/model
mkdir -p BuildTarget/samples


cp -r output/bin/armlinux64/*.so* BuildTarget/bin/armlinux64

if [ ${use_dlopen} == "OFF" ] ; then
    echo 'use_dlopen = OFF!'
	rm -rf BuildTarget/bin/armlinux64/libmaxengine.*
	#rm -rf BuildTarget/bin/armlinux64/libiflyFaceTrack_shared.so
fi


cp -r output/bin/armlinux64/*.txt BuildTarget/bin/armlinux64

cp -r output/bin/armlinux64/DSMTest BuildTarget/bin/armlinux64
cp -r output/bin/armlinux64/DSMSample BuildTarget/bin/armlinux64
cp -r output/bin/armlinux64/DSMTestUnit BuildTarget/bin/armlinux64
cp -r output/bin/armlinux64/MaxEngineLiteTest BuildTarget/bin/armlinux64
cp -r output/bin/armlinux64/DSMTrackTest BuildTarget/bin/armlinux64
cp -r output/bin/armlinux64/DSMRetrievalTest BuildTarget/bin/armlinux64

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
