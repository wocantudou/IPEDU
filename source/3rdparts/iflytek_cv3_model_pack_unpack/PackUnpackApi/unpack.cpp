#include <memory>
#include <string.h>

#include "iflytek_cv3_pack_unpack_type.h"
#include "iflytek_cv3_pack_unpack_error_module.h"
#include "iflytek_cv3_pack_unpack_api.h"

int PACKUNPACKAPI unpack(char* packencrypt_buf, int* magnum, int* input_buffs_num, ModelParams* model_params, char **input_bufs, int* input_buf_lens)
{
	if(packencrypt_buf == nullptr || model_params == nullptr)
	{
		printf("unpack invalid params.\n");
		return IFLYPU_ERROR_NULL_PTR;
	}

	//获取头信息
	int data_shift_size = 0;
	int curr_data_size = sizeof(*magnum);
	memcpy(magnum, packencrypt_buf + data_shift_size, curr_data_size);

	data_shift_size += curr_data_size;
	curr_data_size = sizeof(*input_buffs_num);
	memcpy(input_buffs_num , packencrypt_buf + data_shift_size, curr_data_size);
	// memcpy(head_len, packencrypt_buf + HEAD_LEN_SHIFT * sizeof(int), sizeof(int));

	data_shift_size += curr_data_size;
	curr_data_size = sizeof(ModelParams);
	memcpy(model_params, packencrypt_buf + data_shift_size, curr_data_size);
	// memcpy(model_params, packencrypt_buf + JSON_PARAMS_SHIFT * sizeof(int), sizeof(ModelParams));

	for(int i = 0; i < *input_buffs_num; ++i)
	{
		data_shift_size += curr_data_size;
		curr_data_size = sizeof(input_buf_lens[i]);
		memcpy(&input_buf_lens[i], packencrypt_buf + data_shift_size, curr_data_size);
		data_shift_size += curr_data_size;
		curr_data_size = input_buf_lens[i];
		input_bufs[i] = packencrypt_buf + data_shift_size;
	}
	return IFLYPU_SUCCESS;
}
