#  Minimum verion cmake required
cmake_minimum_required(VERSION 3.5)
#set(CMAKE_C_COMPILER g++)
#add_compile_options(-std=c++11)

SET(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "" FORCE)
#  Project
project  (IPEDU C CXX)

set(source_dir  "${PROJECT_SOURCE_DIR}/source")
set(output_dir  "./output")

#link_directories(${PROJECT_SOURCE_DIR}/output/lib)

set(ENGINE_NAME ipedu_shared)
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
        "${source_dir}/include/ipedu_config.h.in"
		"${PROJECT_BINARY_DIR}/ipedu_config.h"
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
option(IPEDU_BUILD_TEST      		"Build Test."         											OFF)

include(${PROJECT_SOURCE_DIR}/cmake/platform.cmake)

# find_package(Git QUIET)
# message(STATUS "Submodule update")
# execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
# 				WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
# 				RESULT_VARIABLE GIT_SUBMOD_RESULT)
# if(NOT GIT_SUBMOD_RESULT EQUAL "0")
# 	message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
# endif()

include_directories(
${PROJECT_SOURCE_DIR}/source/3rdparts/iflytek_file_encrypt_decrpyt/cmake/include
${PROJECT_SOURCE_DIR}/source/3rdparts/iflytek_cv3_model_pack_unpack/include
)

add_subdirectory(${PROJECT_SOURCE_DIR}/source/3rdparts/iflytek_file_encrypt_decrpyt/cmake)
add_subdirectory(${PROJECT_SOURCE_DIR}/source/3rdparts/iflytek_cv3_model_pack_unpack)
add_subdirectory(${PROJECT_SOURCE_DIR}/source/iPEDUApi)

if (IPEDU_BUILD_TEST)
	add_subdirectory(${PROJECT_SOURCE_DIR}/source/test)
endif ()
