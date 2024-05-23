#/bin/sh
set -e
# source /data/wensha2/tool/QNX/sv-g6sh-qnx-system-sdk/qnxsdp-env.sh
source /home/wensha2/workspace/toolchain/sv-g6sh-qnx-system-sdk/qnxsdp-env.sh
cd ..
build_dir="cmake_build/build_aarch64_qnx700/"
if [ ! -d ${build_dir} ];then
	mkdir -p ${build_dir}
fi

project_root_path=$(pwd)
echo "${project_root_path}"

cd ${build_dir}
rm -rf *

cmake -DCMAKE_GENERATOR="Unix Makefiles"                                              \
    -DCMAKE_TOOLCHAIN_FILE=${project_root_path}/cmake/aarch64_qnx700.toolchain.cmake  \
    ${project_root_path}/cmake
make -j2
cd ../





