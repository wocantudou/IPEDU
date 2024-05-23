#  Minimum verion cmake required
cmake_minimum_required(VERSION 3.5)
#  Project
#iflytek_cv3_pack_unpack
project  (IPUP C CXX)

set(source_dir  "${PROJECT_SOURCE_DIR}")
set(output_dir  "./output")

#link_directories(${PROJECT_SOURCE_DIR}/output/lib)

set(ENGINE_NAME ipup_shared)
set(ENGINE_VERSION_MAJOR 1.0)
set(ENGINE_VERSION_MINOR 1000)
set(ENGINE_VERSION_PATCH 0)

FILE(STRINGS "${PROJECT_SOURCE_DIR}/version.txt" contents)
foreach(line ${contents})
    string(FIND "${line}" "#define ENGINE_VERSION_MAJOR" test)
	#MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~test = ${test}")
	#MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~line = ${line}")
    if (NOT(${test} STREQUAL "-1"))
		string(REPLACE "#define ENGINE_VERSION_MAJOR " "" ENGINE_VERSION_MAJOR ${line})
		continue() 
    endif()

    string(FIND "${line}" "#define ENGINE_VERSION_MINOR" test)
    if (NOT(${test} STREQUAL "-1"))
		string(REPLACE "#define ENGINE_VERSION_MINOR " "" ENGINE_VERSION_MINOR ${line})
		continue() 
    endif()

    string(FIND "${line}" "#define ENGINE_VERSION_PATCH" test)
    if (NOT(${test} STREQUAL "-1"))
		string(REPLACE "#define ENGINE_VERSION_PATCH " "" ENGINE_VERSION_PATCH ${line})
		continue() 
    endif()

	string(FIND "${line}" "#define ENGINE_NAME" test)
    if (NOT(${test} STREQUAL "-1"))
		#MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~test = ${test}")
		#MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~line = ${line}")
		string(REPLACE "#define ENGINE_NAME " "" ENGINE_NAME ${line})
		continue() 
    endif()
endforeach()

MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~ENGINE_NAME = ${ENGINE_NAME}")
MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~ENGINE_VERSION_MAJOR = ${ENGINE_VERSION_MAJOR}")
MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~ENGINE_VERSION_MINOR = ${ENGINE_VERSION_MINOR}")
MESSAGE(STATUS "~~~~~~~~~~~~~~~~~~ENGINE_VERSION_PATCH = ${ENGINE_VERSION_PATCH}")

configure_file(
        "${source_dir}/include/iflytek_cv3_pack_unpack_config.h.in"
		"${PROJECT_BINARY_DIR}/iflytek_cv3_pack_unpack_config.h"
)

#set (ENGINE_NAME_WITH_VERSION "${ENGINE_NAME}${ENGINE_VERSION_MAJOR}_${ENGINE_VERSION_MINOR}")
string(CONCAT ENGINE_NAME_WITH_VERSION ${ENGINE_NAME} ${ENGINE_VERSION_MAJOR} "." ${ENGINE_VERSION_MINOR} "." ${ENGINE_VERSION_PATCH})
MESSAGE(STATUS "~~~~~~~~~~ENGINE_NAME_WITH_VERSION = ${ENGINE_NAME_WITH_VERSION}")

if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
	set(CMAKE_DEBUG_POSTFIX "d")
endif()

if(NOT DEFINED CMAKE_RELEASE_POSTFIX)
	set(CMAKE_RELEASE_POSTFIX "")
endif()

set(CPP11  "-std=c++11")


option(INTEL_OPENMP      			"Use OpenMP when compiles for intel cpu(x86_64)."      			OFF)
option(ARM_OPENMP      				"Use OpenMP when compiles for arm(Android)."    		 		OFF)
option(IPUP_BUILD_TEST      		"Build Test."         											OFF)
option(IPUP_BUILD_SHARED     		"Build Shared Libs."         									OFF)

include(${PROJECT_SOURCE_DIR}/cmake/platform.cmake)

add_subdirectory(${source_dir}/PackUnpackApi)
if (IPUP_BUILD_TEST)
	add_subdirectory(${source_dir}/test)	
endif ()
