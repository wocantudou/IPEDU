#ifndef __IPEDU_API_H__
#define __IPEDU_API_H__


#if defined(_MSC_VER)                 /* Microsoft Visual C++ */
#	if defined(IPEDUAPI)
#		undef IPEDUAPI
#		undef IPEDUAPITYPE
#	endif
#	define IPEDUAPI __stdcall
#	define IPEDUAPITYPE __stdcall
#	pragma pack(push, 8)
#else                                /* Any other including Unix */
#	if defined(IPEDUAPI)
#		undef IPEDUAPI
#		undef IPEDUAPITYPE
#   endif
#	define IPEDUAPI  __attribute__ ((visibility("default")))
#	define IPEDUAPITYPE
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "ipedu_type.h"

#define                                         _IN
#define                                         _OUT
#define                                         _IN_OUT


/*
const char* file_path                           file path													[in]
char** data_buf									memory data buf												[out]
int* data_len									memory data buf len											[out]
*/
int IPEDUAPI malloc_buff_from_file(_IN const char* file_path, _OUT char** data_buf, _OUT int* data_len);

/*
char** data_buf									memory data buf												[in]
*/
int IPEDUAPI free_buff(_IN char** data_buf);


/*
const char* key                                 Secret key                                                  [in]
const int magic_num                             Pack/UnPack check value                                     [in]
IPEDUModelParams* model_params                  Model parameters info                                       [in]
IPEDUParams* function_params                    Resource mem info                                           [in/out]
*/
int IPEDUAPI packencrypt(_IN const char* key, _IN const int magic_num, _IN IPEDUModelParams* model_params, _IN_OUT IPEDUParams* function_params);

/*
const char* key                                 Secret key                                                  [in]
const int magic_num                             Pack/UnPack check value                                     [in]
IPEDUModelParams* model_params                  Model parameters info                                       [in]
IPEDUParams* function_params                    Resource mem info                                           [in/out]
*/
int IPEDUAPI packencrypt_from_mem(_IN const char* key, const int magic_num, IPEDUModelParams* model_params, _IN_OUT IPEDUParams* function_params);

/*
const char* key                                 Secret key                                                  [in]
int* magic_num                                  Pack/UnPack check value                                     [out]
IPEDUModelParams* model_params                  Model parameters info                                       [out]
IPEDUParams* function_params                    Resource mem info                                           [in/out]
*/
int IPEDUAPI decryptunpack(_IN const char* key, _OUT int *magic_num, _OUT IPEDUModelParams* model_params, _IN_OUT IPEDUParams* function_params);

/*
const char* key                                 Secret key                                                  [in]
int* magic_num                                  Pack/UnPack check value                                     [out]
IPEDUModelParams* model_params                  Model parameters info                                       [out]
IPEDUParams* function_params                    Resource mem info                                           [in/out]
*/
int IPEDUAPI decryptunpack_from_mem(_IN const char* key, _OUT int *magic_num, _OUT IPEDUModelParams* model_params, _IN_OUT IPEDUParams* function_params);

#ifdef __cplusplus
};
#endif

/* Reset the structure packing alignments for different compilers. */
#if defined(_MSC_VER)                /* Microsoft Visual C++ */
#pragma pack(pop)
#endif

#endif //__IPEDU_API_H__