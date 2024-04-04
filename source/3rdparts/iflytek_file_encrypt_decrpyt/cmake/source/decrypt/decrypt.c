
#include "stdio.h"
#include "stdint.h"
#include "common/common.h"
#include "decrypt/decrypt.h"



/************************************************************************
* @brief :  ��ȡ�ӽ�������汾��Ϣ
* @param :  none  
* @note:    ��ȡ�ӽ�������汾��Ϣ ��ֱ�ӷ���ifly_int32_t�����ݣ�����汾��Ϣ��XXXXYYZZ, XXXX:�������,YY�����汾��,ZZ����С�汾��
* @author : dwwang3
*************************************************************************/
//ifly_int32_t DECRYPTAPI iDecryptGetVersionV20190001(void)
//{
//	return internalEncryptDecryptGetVersionV20190001();
//}

/************************************************************************
* @brief :  ִ�н��ܲ���
* @param : 
	ifly_int8_t *Key          �û��������Կ�ַ���
	ifly_int32_t KeySize        �û��������Կ�ַ�������
	void *inRes        �ӽ���������Դ���ڴ�ָ��
	ifly_int32_t resLen         �ӽ���������Դ���ڴ�ռ��С
	void *outRes	   �ӽ��������Դ���ڴ�ָ��
* @note:    �û��������Կ����ΪNULL������Կ����������[8,32]��������   
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