#generate library

include_directories(
./
../include
)
#*************executable target*********
aux_source_directory(.  TEST_IPEDU)
# add thridyparty library
set(thirdparty_lib_dir "")
set(thirdparty_lib "")

if(MSVC)
	list(APPEND thirdparty_lib_dir ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
	list(APPEND thirdparty_lib_dir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})
	list(APPEND thirdparty_lib ${ENGINE_NAME})	
else () 
	# add thridyparty library
	list(APPEND thirdparty_lib_dir ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
	list(APPEND thirdparty_lib_dir ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
	list(APPEND thirdparty_lib ${ENGINE_NAME_WITH_VERSION})
endif ()

link_directories(
    ${thirdparty_lib_dir}
    #${user_lib_dir}
)

#link_libraries(
#    ${thirdparty_lib}
#)

set(EXE_TARGET_NAME test_ipedu)
if(MSVC)
	set_property(GLOBAL PROPERTY USE_FOLDERS ON) #open directory
	#*************executable target*********
	add_executable(${EXE_TARGET_NAME}  ${TEST_IPEDU})
	target_link_libraries (${EXE_TARGET_NAME} ${thirdparty_lib})
	set_property(TARGET ${EXE_TARGET_NAME} PROPERTY FOLDER "test_ipedu")
	#new add 
	SET_TARGET_PROPERTIES(${EXE_TARGET_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}")
else()
	#*************executable target*********
	add_executable(${EXE_TARGET_NAME}  ${TEST_IPEDU})
	target_link_libraries (${EXE_TARGET_NAME} ${thirdparty_lib})
	if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
		add_custom_command(TARGET ${EXE_TARGET_NAME} POST_BUILD
						   WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
						   COMMAND ${CMAKE_STRIP} "-s" "${EXE_TARGET_NAME}")
	endif()
endif()


