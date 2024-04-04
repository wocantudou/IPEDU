set(CMAKE_SYSTEM_NAME Linux)

#set (PREFIX "/opt/poky/2.4.3/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux/aarch64-poky-linux-")
set (PREFIX "")
set (CMAKE_C_COMPILER ${PREFIX}gcc)
set (CMAKE_CXX_COMPILER ${PREFIX}g++)
set (CMAKE_AR ${PREFIX}ar CACHE FILEPATH "Archiver")
set (CMAKE_RANLIB  ${PREFIX}ranlib)

