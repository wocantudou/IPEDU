#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <string.h>

//pack_unpack API
#include "iflytek_cv3_pack_unpack_type.h"
#include "iflytek_cv3_pack_unpack_error_module.h"
#include "iflytek_cv3_pack_unpack_api.h"

//�encrypt_decryp API
#include "common/isymdef.h"
#include "common/common.h"
#include "encrypt/encrypt.h"
#include "decrypt/decrypt.h"
#include "common/iflyTypeDef.h"

#include "ipedu_error_module.h"
#include "ipedu_api.h"

inline void safe_delete_pointer(char** data_buf)
{
	if(*data_buf)
	{
		delete[] *data_buf; 
		*data_buf = nullptr;
		//printf("delete success\n");
	}
}

int IPEDUAPI malloc_buff_from_file(const char* file_path, char** data_buf, int* data_len)
{
	int ret = IFLYPEDU_SUCCESS;
	ret = MallocFileBuff(file_path, data_buf, data_len);
	return ret;
}

int IPEDUAPI free_buff(char** data_buf)
{
	int ret = IFLYPEDU_SUCCESS;
	ret = FreeFileBuff(data_buf);
	return ret;
}

int IPEDUAPI packencrypt(const char* key, const int magic_num, IPEDUModelParams* model_params, IPEDUParams* function_params)
{
	int ret = IFLYPEDU_SUCCESS;
	function_params->packencrypt_buf.buff_len = 4 * sizeof(int) + sizeof(ModelParams);
	for(int i = 0; i < function_params->real_input_num; ++i)
	{
		ret = MallocFileBuff(function_params->input_res_paths[i], &function_params->input_res_bufs[i].buff, &function_params->input_res_bufs[i].buff_len);
		if (ret)
		{
			printf("MallocFileBuff %s failed ...\n", function_params->input_res_paths[i]);
			return ret + IFLYPEDU_ERROR_BASE;
		}
		function_params->packencrypt_buf.buff_len += function_params->input_res_bufs[i].buff_len;
	}
	
	//function_params->packencrypt_buf.buff_len = 4 * sizeof(int) + sizeof(ModelParams) + function_params->json_buf.buff_len + function_params->params_buf.buff_len;

	function_params->packencrypt_buf.buff = new (std::nothrow)char[function_params->packencrypt_buf.buff_len];
	if (NULL == function_params->packencrypt_buf.buff)
	{
		printf("Alloc Memory pack_buffer failed, size: %d ...\n", function_params->packencrypt_buf.buff_len);
		for(int i = 0; i < function_params->real_input_num; ++i)
		{
			ret = FreeFileBuff(&function_params->input_res_bufs[i].buff);
			if (ret)
			{
				printf("FreeFileBuff json_buf failed ...\n");
				return ret + IFLYPEDU_ERROR_BASE;
			}
		}
		return IFLYPEDU_ERROR_MEM_ALLOC;
	}

	
	ret = packencrypt_from_mem(key, magic_num, model_params, function_params);
	if (ret)
	{
		for(int i = 0; i < function_params->real_input_num; ++i)
		{
			printf("packencrypt_from_mem [%s] failed ...\n", function_params->input_res_paths[i]);
			ret = FreeFileBuff(&function_params->input_res_bufs[i].buff);
			if (ret)
			{
				printf("FreeFileBuff json_buf failed ...\n");
				return ret + IFLYPEDU_ERROR_BASE;
			}

		}
		safe_delete_pointer(&(function_params->packencrypt_buf.buff));
		return ret + IFLYPEDU_ERROR_BASE;
	}
	
	//FREE MEM
	for(int i = 0; i < function_params->real_input_num; ++i)
	{
		ret = FreeFileBuff(&function_params->input_res_bufs[i].buff);
		if (ret)
		{
			printf("FreeFileBuff json_buf failed ...\n");
			return ret + IFLYPEDU_ERROR_BASE;
		}
	}

	ret = SaveFileBuff(function_params->packencrypt_buf.buff, function_params->packencrypt_buf.buff_len, function_params->packencrypt_path);
	if (ret)
	{
		printf("SaveFileBuff %s failed ...\n", function_params->packencrypt_path);
		safe_delete_pointer(&(function_params->packencrypt_buf.buff));
		return ret + IFLYPEDU_ERROR_BASE;
	}
	safe_delete_pointer(&(function_params->packencrypt_buf.buff));
	return ret;
}

int IPEDUAPI packencrypt_from_mem(const char* key, const int magic_num, IPEDUModelParams* model_params, IPEDUParams* function_params)
{
	int ret = IFLYPEDU_SUCCESS;
	for (int  i = 0; i < function_params->real_input_num; ++i)
	{
		if(function_params->input_res_bufs[i].buff_len <= 0)
		{
			printf("the json_len:[%d] is invaild\n", function_params->input_res_bufs[i].buff_len);
			return IFLYPEDU_ERROR_INVAILD_PARAMS;
		}
	}
	
	const int pack_buffer_size = function_params->packencrypt_buf.buff_len;

	const int input_bufs_num = function_params->real_input_num;
	/*const char *input_bufs[input_bufs_num];
	int input_buf_lens[input_bufs_num];*/

	const char *input_bufs[IPEDUParams::MAX_RES_INPUT_NUM];
	int input_buf_lens[IPEDUParams::MAX_RES_INPUT_NUM];

	for(int i = 0; i < input_bufs_num; ++i)
	{
		input_bufs[i] = function_params->input_res_bufs[i].buff;
		input_buf_lens[i] = function_params->input_res_bufs[i].buff_len;
	}
	

	ret = pack(magic_num, function_params->conf_path, model_params->model_name, model_params->model_version, static_cast<ModelType>(model_params->model_type), \
	input_bufs, input_buf_lens, input_bufs_num, function_params->packencrypt_buf.buff);//packing
	if(ret)
	{
		printf("pack failed.");
		return ret + IFLYPEDU_ERROR_BASE;
	}

	internalEncryptDecryptDoProcessV20190001((signed char*)key, strlen((char* )key), function_params->packencrypt_buf.buff, pack_buffer_size, function_params->packencrypt_buf.buff); //encrypting

	return ret;
}

int IPEDUAPI decryptunpack(const char* key, int *magic_num, IPEDUModelParams* model_params, IPEDUParams* function_params)
{
	int ret = IFLYPEDU_SUCCESS;
	ModelParams in_model_params;

	ret = MallocFileBuff(function_params->packencrypt_path, &function_params->packencrypt_buf.buff, &function_params->packencrypt_buf.buff_len);
	if (ret)
	{
		printf("MallocFileBuff %s failed ...\n", function_params->packencrypt_path);
		return ret + IFLYPEDU_ERROR_BASE;
	}


	ret = decryptunpack_from_mem(key, magic_num, model_params, function_params);
	if (ret)
	{
		printf("decryptunpack [%s] failed ...\n", function_params->packencrypt_path);
		ret = FreeFileBuff(&function_params->packencrypt_buf.buff);
		if (ret)
		{
			printf("FreeFileBuff packencrypt_buf failed ...\n");
			return ret + IFLYPEDU_ERROR_BASE;
		}
		return ret + IFLYPEDU_ERROR_BASE;
	}
	
	for(int i = 0; i < function_params->real_input_num; ++i)
	{
		ret = SaveFileBuff(function_params->input_res_bufs[i].buff, function_params->input_res_bufs[i].buff_len, function_params->input_res_paths[i]);
		if (ret)
		{
			printf("SaveFileBuff %s failed ...\n", function_params->input_res_paths[i]);
			ret = FreeFileBuff(&function_params->packencrypt_buf.buff);
			if (ret)
			{
				printf("FreeFileBuff packencrypt_buf failed ...\n");
				return ret + IFLYPEDU_ERROR_BASE;
			}
			return ret + IFLYPEDU_ERROR_BASE;
		}
	}

	ret = FreeFileBuff(&function_params->packencrypt_buf.buff);
	if (ret)
	{
		printf("FreeFileBuff packencrypt_buf failed ...\n");
		return ret + IFLYPEDU_ERROR_BASE;
	}

	return ret;

}

int IPEDUAPI decryptunpack_from_mem(const char* key, int *magic_num, IPEDUModelParams* model_params, IPEDUParams* function_params)
{
	int ret = IFLYPEDU_SUCCESS;
	if(function_params->packencrypt_buf.buff_len <= 0)
	{
		printf("the packencrypt_len:[%d] is invaild\n", function_params->packencrypt_buf.buff_len);
		return IFLYPEDU_ERROR_INVAILD_PARAMS;
	}

	ModelParams in_model_params;

	internalEncryptDecryptDoProcessV20190001((signed char*)key, strlen((char* )key), function_params->packencrypt_buf.buff, function_params->packencrypt_buf.buff_len, function_params->packencrypt_buf.buff); 

	char* input_bufs[IPEDUParams::MAX_RES_INPUT_NUM];
	int input_buf_len[IPEDUParams::MAX_RES_INPUT_NUM];
	ret = unpack(function_params->packencrypt_buf.buff, magic_num, &function_params->real_input_num, &in_model_params, input_bufs, input_buf_len);
	if(ret)
	{
		printf("unpack failed.");
		return ret + IFLYPEDU_ERROR_BASE;
	}

	const int  input_bufs_num = function_params->real_input_num;
	for(int  i = 0; i < input_bufs_num; ++i)
	{
		function_params->input_res_bufs[i].buff = input_bufs[i];
		function_params->input_res_bufs[i].buff_len = input_buf_len[i];
	}

#if 0
	memcpy(model_params, &in_model_params, sizeof(ModelParams));
#else
	model_params->n = in_model_params.n;
	model_params->c = in_model_params.c;
	model_params->h = in_model_params.h;
	model_params->w = in_model_params.w;
	memcpy(model_params->model_name, in_model_params.model_name, strlen(in_model_params.model_name));
	model_params->model_name[strlen(in_model_params.model_name)] = '\0';
	model_params->model_version = in_model_params.model_version;
	model_params->model_type = static_cast<IPEDUModelType>(in_model_params.model_type);
#endif
	return ret;

}



