#/bin/sh
source /data/wensha2/tool/QNX/sv-g6sh-qnx-system-sdk/qnxsdp-env.sh
cd ../../

if [ ! -f "cmake_build" ];then
	mkdir cmake_build
fi

CMAKE=cmake
batch_file_path=$(pwd)
echo "${batch_file_path}"

cd cmake_build
QNX_BUILD_PATH="./cmake_build_qnx700"
if [ ! -f "$QNX_BUILD_PATH" ]; then
	mkdir cmake_build_qnx700
fi
cd cmake_build_qnx700

cmake	-DBUILD_QNX700=ON 																\
		-DCMAKE_GENERATOR="Unix Makefiles"												\
		-DCMAKE_TOOLCHAIN_FILE=${batch_file_path}/cmake/qnx.toolchain.cmake 			\
		-DCMAKE_BUILD_TYPE=Release														\
		-DIPUP_BUILD_SHARED=ON															\
		-DIPUP_BUILD_TEST=ON															\
		${batch_file_path}
make -j
cd ../../


echo "################################################## Make Build Target #################"