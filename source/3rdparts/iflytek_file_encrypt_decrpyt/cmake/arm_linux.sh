#/bin/sh
set -e
cd ..
build_dir="cmake_build/build_arm_linux/"
if [ ! -d ${build_dir} ];then
	mkdir -p ${build_dir}
fi

project_root_path=$(pwd)
echo "${project_root_path}"

cd ${build_dir}
rm -rf *

cmake -DCMAKE_GENERATOR="Unix Makefiles"                                              \
    -DCMAKE_TOOLCHAIN_FILE=${project_root_path}/cmake/arm_linux.toolchain.cmake  \
    ${project_root_path}/cmake
make -j2
cd ../





