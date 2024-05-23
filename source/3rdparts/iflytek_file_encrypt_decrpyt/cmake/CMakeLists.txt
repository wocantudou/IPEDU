#  Minimum verion cmake required
cmake_minimum_required(VERSION 3.5)

#  Project
project  (ENCRYPT C CXX)

set(encrypt_include_dir "${PROJECT_SOURCE_DIR}/include")
set(encrypt_source_dir "${PROJECT_SOURCE_DIR}/source")
link_directories(${PROJECT_SOURCE_DIR}/lib)

  if(NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX "d")
  endif()
  if(NOT DEFINED CMAKE_RELEASE_POSTFIX)
    set(CMAKE_RELEASE_POSTFIX "")
  endif()
  
option(BUILD_ENCRYPT_TEST      		  "Build test."         											              OFF)

include(${PROJECT_SOURCE_DIR}/platform.cmake)

include_directories(
./include
)

aux_source_directory(./source/common DECRYPT_LIB)
aux_source_directory(./source/decrypt DECRYPT_LIB)
add_library(decrypt STATIC ${DECRYPT_LIB})

if(BUILD_ENCRYPT_TEST)
	aux_source_directory(./source/common EECRYPT_TEST)
	aux_source_directory(./source/decrypt EECRYPT_TEST)
	aux_source_directory(./source/encrypt EECRYPT_TEST)
	aux_source_directory(./source/encrypt_test EECRYPT_TEST)
	add_executable(encrypt_test ${EECRYPT_TEST})
endif()
