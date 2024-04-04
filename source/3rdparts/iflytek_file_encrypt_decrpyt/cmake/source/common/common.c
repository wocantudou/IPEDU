
#include "common/common.h"


#define CONFUSION_CODE_LEN						(256)
// strlen should not less than 256Bytes
static const ifly_int8_t *confusion_code = "IFLYTEK CO.,LTD.(iFLYTEK)is a national key software enterprise dedicated to the research of intelligent speech and language technologies, development of software and chip products, provision of speech information services, and integration of E-government systems. The intelligent speech technology of iFLYTEK, the core technology of the company, represents the top level in the world. Established in 1999, iFLYTEK was listed in the Shenzhen Stock Exchange in 2008 (stock code: 002230). With vigorous support from major shareholders including USTC Holdings Co., Ltd., Shanghai Guangxin, and Legend Capital, iFLYTEK boasts the longest fundamental research history, the largest professional research team, the greatest capital investment, the best evaluation results, and the largest market share among all business entities in the speech technology field in China.";

#define MAX_KEY_LEN					(32)


/************************************************************************
* @brief :  ���û�������Կ������ͼ���
* @param : 
	ifly_int8_t *Key          �û��������Կ�ַ���
	ifly_int32_t KeySize        �û��������Կ�ַ�������
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
* @brief :  ���û�������Կ������ͼ���
* @param : 
	ifly_int8_t *Key          �û��������Կ�ַ���
	ifly_int32_t KeySize        �û��������Կ�ַ�������
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
* @brief :  ��ȡ�ӽ�������汾��Ϣ
* @param :  none  
* @note:    ��ȡ�ӽ�������汾��Ϣ ��ֱ�ӷ���ifly_int32_t�����ݣ�����汾��Ϣ��XXXXYYZZ, XXXX:�������,YY�����汾��,ZZ����С�汾��
* @author : dwwang3
*************************************************************************/
ifly_int32_t internalEncryptDecryptGetVersionV20190001(void)
{
	return 20190001;
}


/************************************************************************
* @brief :  ִ�мӽ��ܲ���(�ڲ����ú���)
* @param : 
	ifly_int8_t *Key          �û��������Կ�ַ���
	ifly_int32_t KeySize        �û��������Կ�ַ�������
	void *inRes        �ӽ���������Դ���ڴ�ָ��
	ifly_int32_t resLen         �ӽ���������Դ���ڴ�ռ��С
	void *outRes	   �ӽ��������Դ���ڴ�ָ��
* @note:    �ӽ����ڲ�������ʹ��ͬһ���ڲ���������   
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