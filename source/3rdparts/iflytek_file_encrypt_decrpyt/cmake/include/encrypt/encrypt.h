#ifndef __MODEL_ENCRYPT_H__
#define __MODEL_ENCRYPT_H__

#include "common/iflyTypeDef.h"

#if defined(_MSC_VER)                 /* Microsoft Visual C++ */
#	if !defined(ENCRYPTAPI)
#		define ENCRYPTAPI __stdcall
#		define ENCRYPTAPITYPE __stdcall
#	endif
#	pragma pack(push, 8)
#else                                /* Any other including Unix */
#	if !defined(ENCRYPTAPI)
#		define ENCRYPTAPI  __attribute__ ((visibility("default")))
#		define ENCRYPTAPITYPE
#	endif
#endif

#define RDeclareApi(func)		extern Proc_##func  func##_;
#define DeclareApi(func)		Proc_##func  func##_;

#define GetProcApi(func)\
	{\
	func##_ = (Proc_##func)GetProcAddress(hand, #func);\
	}
#define GetProcApiVar(func)\
	{\
	func##_ = (Proc_##func)( func);\
	}

#define API_LIST_VAD(func)\
	func(iEncryptGetVersion)\
	func(iEncryptDoProcess)

#ifdef __cplusplus 
extern "C"{
#endif

	//获取加密组件的版本信息
	ifly_int32_t ENCRYPTAPI iEncryptGetVersionV20190001(void);
	typedef ifly_int32_t (ENCRYPTAPITYPE* Proc_iEncryptGetVersionV20190001)(void);

	//执行加密操作
	ifly_int32_t ENCRYPTAPI iEncryptDoProcessV20190001(const ifly_int8_t *Key, ifly_uint32_t KeySize, const void *inRes, ifly_uint64_t resLen, void *outRes);
	typedef ifly_int32_t (ENCRYPTAPITYPE* Proc_iEncryptDoProcessV20190001)(const ifly_int8_t *Key, ifly_uint32_t KeySize, const void *inRes, ifly_uint64_t resLen, void *outRes);

#ifdef __cplusplus
}
#endif

/* Reset the structure packing alignments for different compilers. */
#if defined(_MSC_VER)                /* Microsoft Visual C++ */
#pragma pack(pop)
#endif

#endif //__MODEL_ENCRYPT_H__