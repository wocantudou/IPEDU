
#include "common/common.h"


#define CONFUSION_CODE_LEN						(256)
// strlen should not less than 256Bytes
static const ifly_int8_t *confusion_code = "IFLYTEK CO.,LTD.(iFLYTEK)is a national key software enterprise dedicated to the research of intelligent speech and language technologies, development of software and chip products, provision of speech information services, and integration of E-government systems. The intelligent speech technology of iFLYTEK, the core technology of the company, represents the top level in the world. Established in 1999, iFLYTEK was listed in the Shenzhen Stock Exchange in 2008 (stock code: 002230). With vigorous support from major shareholders including USTC Holdings Co., Ltd., Shanghai Guangxin, and Legend Capital, iFLYTEK boasts the longest fundamental research history, the largest professional research team, the greatest capital investment, the best evaluation results, and the largest market share among all business entities in the speech technology field in China.";

#define MAX_KEY_LEN					(32)


/************************************************************************
* @brief :  对用户输入密钥进行求和计算
* @param : 
	ifly_int8_t *Key          用户输入的密钥字符串
	ifly_int32_t KeySize        用户输入的密钥字符串长度
* @note:   
* @author : dwwang3
*************************************************************************/
static ifly_int8_t calcUserKeySum(const ifly_int8_t *Key, ifly_uint32_t KeySize)
{
	ifly_uint32_t i = 0;
	ifly_uint8_t sum = 0;

	for (i = 0; i < KeySize; i++)
	{
		sum += Key[i];
	}

	return sum;
}

/************************************************************************
* @brief :  对用户输入密钥进行求和计算
* @param : 
	ifly_int8_t *Key          用户输入的密钥字符串
	ifly_int32_t KeySize        用户输入的密钥字符串长度
* @note:   
* @author : dwwang3
*************************************************************************/
static ifly_int8_t calcUserKeyXor(const ifly_int8_t *Key, ifly_uint32_t KeySize)
{
	ifly_uint32_t i = 0;
	ifly_uint8_t xor = 0;

	for (i = 0; i < KeySize; i++)
	{
		xor ^= Key[i];
	}

	return xor;
}


/************************************************************************
* @brief :  获取加解密组件版本信息
* @param :  none  
* @note:    获取加解密组件版本信息 ，直接返回ifly_int32_t型数据，代表版本信息：XXXXYYZZ, XXXX:代表年份,YY代表大版本号,ZZ代表小版本号
* @author : dwwang3
*************************************************************************/
ifly_int32_t internalEncryptDecryptGetVersionV20190001(void)
{
	return 20190001;
}


/************************************************************************
* @brief :  执行加解密操作(内部公用函数)
* @param : 
	ifly_int8_t *Key          用户输入的密钥字符串
	ifly_int32_t KeySize        用户输入的密钥字符串长度
	void *inRes        加解密输入资源的内存指针
	ifly_int32_t resLen         加解密输入资源的内存空间大小
	void *outRes	   加解密输出资源的内存指针
* @note:    加解密内部处理函数使用同一个内部操作函数   
* @author : dwwang3
*************************************************************************/
void internalEncryptDecryptDoProcessV20190001(const ifly_int8_t *Key, ifly_uint32_t KeySize, const void *inRes, ifly_uint64_t resLen, void *outRes)
{
	ifly_uint64_t i = 0;
	ifly_uint32_t start_pos = 0;
	ifly_int8_t tmpKeyBuf[MAX_KEY_LEN] = {0};
	ifly_int8_t *inResTmp = (ifly_int8_t *)inRes, *outResTmp = (ifly_int8_t *)outRes;

	if ( 0 == Key[0]%2 )
	{
		start_pos = calcUserKeySum(Key, KeySize);
		for (i = 0; i < MAX_KEY_LEN; i++)
		{
			tmpKeyBuf[i] = Key[i%KeySize];
			tmpKeyBuf[i] = tmpKeyBuf[i] ^ confusion_code[(start_pos + i)%CONFUSION_CODE_LEN];
		}

		for (i = 0; i < resLen; i++)
		{
			outResTmp[i] = tmpKeyBuf[i % MAX_KEY_LEN] ^ inResTmp[i];
		}
	}
	else
	{
		start_pos = calcUserKeyXor(Key, KeySize);
		for (i = 0; i < MAX_KEY_LEN; i++)
		{
			tmpKeyBuf[i] = Key[i%KeySize];
			tmpKeyBuf[i] = tmpKeyBuf[i] ^ confusion_code[(start_pos + 2*i)%CONFUSION_CODE_LEN];
		}

		for (i = 0; i < resLen; i++)
		{
			outResTmp[i] = tmpKeyBuf[i % MAX_KEY_LEN] ^ inResTmp[i];
		}
	}
}