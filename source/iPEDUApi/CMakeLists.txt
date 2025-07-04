#generate library

include_directories(
${PROJECT_BINARY_DIR}
${PROJECT_SOURCE_DIR}/source/include
)

#***************static library************
aux_source_directory(.  IPEDU_STATIC_LIB)


#***************shared library************
aux_source_directory(.  IPEDU_SHARED_LIB)


# add thridyparty library dir
set(thirdparty_lib_dir "")
# add thridyparty library
set(thirdparty_lib "")

list(APPEND thirdparty_lib "decrypt")
list(APPEND thirdparty_lib "ipup_static")

if(MSVC)
	# add thridyparty library
	list(APPEND thirdparty_lib_dir ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
	list(APPEND thirdparty_lib_dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})

else () 
	# add thridyparty library
	list(APPEND thirdparty_lib_dir ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
	list(APPEND thirdparty_lib_dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	if (CMAKE_SYSTEM_NAME STREQUAL "Android")
		list(APPEND thirdparty_lib "log;z")
		
	else ()
		if (CMAKE_SYSTEM_NAME STREQUAL "QNX")
			
		else()
			list(APPEND thirdparty_lib "dl")
		endif()	
	endif ()
endif ()

link_directories(
    ${thirdparty_lib_dir}
)

if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON) #open directory
	#***************static library************
	add_library(ipedu_static STATIC ${IPEDU_STATIC_LIB})
	target_link_libraries (ipedu_static ${thirdparty_lib})
	set_property(TARGET ipedu_static PROPERTY FOLDER "IPEDUApi")
	#***************shared library************
	if(IPEDU_BUILD_SHARED)
		set(API_DEF_FILE "./ipedu_api_debug.def")
		if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
			set(API_DEF_FILE "./ipedu_api_release.def")
		endif()
		add_library(ipedu_shared SHARED ${IPEDU_SHARED_LIB} ${API_DEF_FILE})
		target_link_libraries (ipedu_shared ${thirdparty_lib})
		set_property(TARGET ipedu_shared PROPERTY FOLDER "IPEDUApi")
	endif()
else ()
	#***************static library************
	add_library(ipedu_static STATIC ${IPEDU_STATIC_LIB})
	#set_target_properties (ipedu_static PROPERTIES LINK_FLAGS  -Wl,--no-undefined,--retain-symbols-file,${CMAKE_CURRENT_SOURCE_DIR}/IPEDU.sym)
	#***************shared library************
	if(IPEDU_BUILD_SHARED)
		add_library(${ENGINE_NAME_WITH_VERSION} SHARED ${IPEDU_SHARED_LIB})
		target_link_libraries (${ENGINE_NAME_WITH_VERSION} ${thirdparty_lib})
		if(NOT MSVC AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
			#get_target_property(target_name ${ENGINE_NAME_WITH_VERSION}.so OUTPUT_NAME)
			add_custom_command(TARGET ${ENGINE_NAME_WITH_VERSION} POST_BUILD
							WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
							COMMAND ${CMAKE_STRIP} "-s" "lib${ENGINE_NAME_WITH_VERSION}.so")
			#MESSAGE(STATUS "************ENGINE_NAME_WITH_VERSION = ${ENGINE_NAME_WITH_VERSION}")
			#MESSAGE(STATUS "************target_name = ${target_name}")
			#set_target_properties(${ENGINE_NAME_WITH_VERSION} PROPERTIES LINK_FLAGS  -Wl,--no-undefined,--version-script,${CMAKE_CURRENT_SOURCE_DIR}/IPEDU.map)
		endif()
	endif()
endif()

