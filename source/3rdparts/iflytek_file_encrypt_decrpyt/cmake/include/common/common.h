#ifndef __MODEL_COMMON_H__
#define __MODEL_COMMON_H__

#include "iflyTypeDef.h"
#include "isymdef.h"

#ifdef __cplusplus 
extern "C"{
#endif

ifly_int32_t internalEncryptDecryptGetVersionV20190001(void);
void internalEncryptDecryptDoProcessV20190001(const ifly_int8_t *Key, ifly_uint32_t KeySize, const void *inRes, ifly_uint64_t resLen, void *outRes);

#ifdef __cplusplus
}
#endif

#endif //__MODEL_COMMON_H__