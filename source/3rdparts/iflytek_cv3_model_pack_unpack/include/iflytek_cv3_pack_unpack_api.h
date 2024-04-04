#ifndef __IFLYTEK_CV3_PACK_UNPACK_API_H__
#define __IFLYTEK_CV3_PACK_UNPACK_API_H__

#if defined(_MSC_VER)                 /* Microsoft Visual C++ */
#	if defined(PACKUNPACKAPI)
#		undef PACKUNPACKAPI
#		undef PACKUNPACKAPITYPE
#	endif
#	define PACKUNPACKAPI __stdcall
#	define PACKUNPACKAPITYPE __stdcall
#	pragma pack(push, 8)
#else                                /* Any other including Unix */
#	if defined(PACKUNPACKAPI)
#		undef PACKUNPACKAPI
#		undef PACKUNPACKAPITYPE
#   endif
#	define PACKUNPACKAPI  __attribute__ ((visibility("default")))
#	define PACKUNPACKAPITYPE
#endif

#ifdef __cplusplus
extern "C" {
#endif
#include <cstdio>
#include "iflytek_cv3_pack_unpack_type.h"

/*
const char* file_path			文件路径
char** data_buf					文件内存
int* data_len					文件长度
*/
int PACKUNPACKAPI MallocFileBuff(const char* file_path, char** data_buf, int* data_len);

int PACKUNPACKAPI FreeFileBuff(char** data_buf);

int PACKUNPACKAPI SaveFileBuff(char* data_buf, const int buff_len, const char* file_path);

/*
const int magic_num:            	magic number
const char *conf_path：     		配置文件路径
const char *model_name：   			模型名称
const int model_version：        	模型版本号
const ModelType model_type：		模型类别
const char **input_buf_arr：		实际输入资源buf的头部指针数组
const int* input_buf_len_arr：      实际输入资源各个buf的长度
const int input_buf_arr_len	        实际输入资源的数量(json + params = 2)
char* pack_buffer		        	打包结果分配内存
*/
int PACKUNPACKAPI pack(const int magic_num, const char *conf_path, const char * model_name, const int model_version, const ModelType model_type,\
						const char **input_buf_arr, const int* input_buf_len_arr, const int input_buf_arr_len, char* pack_buffer);

/*
const char** packencrypt_buf:   	打包文件数据内存
int* magnum:                    	magic number
int* input_buffs_num:            	实际输入资源的数量(json + params = 2)
ModelParams* model_params:          模型json数据长度
char **input_bufs:               	实际输入资源buf的头部指针数组
int* input_buf_lens：				实际输入资源各个buf的长度
*/
int PACKUNPACKAPI unpack(char* packencrypt_buf, int* magnum, int* input_buffs_num, ModelParams* model_params, char **input_bufs, int* input_buf_lens);

#ifdef __cplusplus
};
#endif

/* Reset the structure packing alignments for different compilers. */
#if defined(_MSC_VER)                /* Microsoft Visual C++ */
#pragma pack(pop)
#endif

#endif //__IFLYTEK_CV3_PACK_UNPACK_API_H__
