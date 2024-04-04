
#include "stdio.h"
#include "stdint.h"
#include "common/common.h"
#include "decrypt/decrypt.h"



/************************************************************************
* @brief :  获取加解密组件版本信息
* @param :  none  
* @note:    获取加解密组件版本信息 ，直接返回ifly_int32_t型数据，代表版本信息：XXXXYYZZ, XXXX:代表年份,YY代表大版本号,ZZ代表小版本号
* @author : dwwang3
*************************************************************************/
//ifly_int32_t DECRYPTAPI iDecryptGetVersionV20190001(void)
//{
//	return internalEncryptDecryptGetVersionV20190001();
//}

/************************************************************************
* @brief :  执行解密操作
* @param : 
	ifly_int8_t *Key          用户输入的密钥字符串
	ifly_int32_t KeySize        用户输入的密钥字符串长度
	void *inRes        加解密输入资源的内存指针
	ifly_int32_t resLen         加解密输入资源的内存空间大小
	void *outRes	   加解密输出资源的内存指针
* @note:    用户传入的秘钥不得为NULL，且秘钥长度限制在[8,32]长度区间   
* @author : dwwang3
*************************************************************************/
ifly_int32_t DECRYPTAPI iDecryptDoProcessV20190001(const ifly_int8_t *Key, ifly_uint32_t KeySize, const void *inRes, ifly_uint64_t resBytes, void *outRes )
{
	if ((NULL == Key))
	{
		return 1;
	}
	if ((KeySize < 8) || (KeySize > 32))
	{
		return 2;
	}
	if ((NULL == inRes))
	{
		return 3;
	}
	if (0 == resBytes)
	{
		return 4;
	}
	if (NULL == outRes)
	{
		return 5;
	}

	internalEncryptDecryptDoProcessV20190001(Key, KeySize, inRes, resBytes, outRes);

	return 0;
}