#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <map>
#include <functional>

#include "iflytek_cv3_pack_unpack_type.h"
#include "iflytek_cv3_pack_unpack_error_module.h"
#include "iflytek_cv3_pack_unpack_api.h"

std::vector<std::string> str_split(std::string& str, const std::string& pattern)
{
	std::string::size_type pos = str.rfind(pattern);
	if (pos + pattern.size() != str.size())
	{
		str += pattern;
	}
	std::vector<std::string> result;
	std::string::size_type size = str.size();
	for (std::string::size_type i = 0; i < size; ++i)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			result.push_back(str.substr(i, pos - i));
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

int pack_file(std::string& params_str)
{
	int ret = IFLYPU_SUCCESS;

	std::vector<std::string> params_vec = str_split(params_str, ":");
	if(params_vec.size() != 8)
	{
		std::cout << "pack_encrypt params is invalid." << std::endl;
		return IFLYPU_ERROR_GENERAL;
	}

	const char* conf_path = params_vec[0].c_str();
	const char* json_path = params_vec[1].c_str();
	const char* params_path = params_vec[2].c_str();
	const char* model_name = params_vec[3].c_str();
	const long model_version = std::atol(params_vec[4].c_str());
	const ModelType model_type = static_cast<ModelType>(std::atoi(params_vec[5].c_str()));
	const int magic_num = std::atoi(params_vec[6].c_str());
	const char* output_path = params_vec[7].c_str();

	char* json_buf = nullptr;
	char* params_buf = nullptr;
	int json_len = 0;
	int params_len = 0;

	ret = MallocFileBuff(json_path, &json_buf, &json_len);
	if (ret)
	{
		printf("MallocFileBuff %s failed ...\n", json_path);
		return ret;
	}

    if(!strcmp(params_path, "NULL"))
    {
        params_buf = nullptr;
        params_len = 0;
    }
    else
    {
        ret = MallocFileBuff(params_path, &params_buf, &params_len);
        if (ret)
        {
            printf("MallocFileBuff %s failed ...\n", params_path);
            return ret;
        }
    }

	const int pack_buffer_size = 4 * sizeof(int) + sizeof(ModelParams) + json_len + params_len;
	char* pack_buffer = new (std::nothrow)char[pack_buffer_size];
	if (NULL == pack_buffer)
	{
		printf("Alloc Memory pack_buffer failed, size: %d ...\n", pack_buffer_size);
		return IFLYPU_ERROR_MEM_ALLOC;
	}

	const int input_bufs_num = 2;
	const char *input_bufs[input_bufs_num];
	int input_buf_lens[input_bufs_num];
	input_bufs[0] = json_buf;
	input_buf_lens[0] = json_len;
	input_bufs[1] = params_buf;
	input_buf_lens[1] = params_len;
	

	ret = pack(magic_num, conf_path, model_name, model_version, model_type, input_bufs, input_buf_lens, input_bufs_num, pack_buffer);//packing
	if(ret)
	{
		printf("pack [%s] [%s] failed.", json_path, params_path);
		return ret;
	}

	//FREE MEM
	ret = FreeFileBuff(&json_buf);
	if (ret)
	{
		printf("FreeFileBuff json_buf failed ...\n");
		return ret;
	}

    if(strcmp(params_path, "NULL"))
    {
        ret = FreeFileBuff(&params_buf);
        if (ret)
        {
            printf("FreeFileBuff params_buf failed ...\n");
            return ret;
        }
    }

	ret = SaveFileBuff(pack_buffer, pack_buffer_size, output_path);
	if (ret)
	{
		printf("SaveFileBuff %s failed ...\n", output_path);
		return ret;
	}

	return ret;
}

int unpack_file(std::string& params_str)
{
	int ret = IFLYPU_SUCCESS;

	std::vector<std::string> params_vec = str_split(params_str, ":");
	if(params_vec.size() != 3)
	{
		std::cout << "decrypt_unpack params is invalid." << std::endl;
		return -1;
	}

	const char* file_path = params_vec[0].c_str();
	const char* output_json_path = params_vec[1].c_str();
	const char* output_params_path = params_vec[2].c_str();

	
	int json_len = 0;
	int params_len = 0;
    int input_bufs_real_len = 0;

	int magic_num = 0;
	int packed_size = 0;
	char* packed_buff = nullptr;
	ModelParams model_params;

	ret = MallocFileBuff(file_path, &packed_buff, &packed_size);
	if (ret)
	{
		printf("MallocFileBuff %s failed ...\n", file_path);
		return ret;
	}

	const int max_input_buffs = 2;
	char *input_bufs[max_input_buffs];
	int input_buf_lens[max_input_buffs];
	const char* output_file_paths[max_input_buffs];
	output_file_paths[0] = output_json_path;
	output_file_paths[1] = output_params_path;
	
	ret = unpack(packed_buff, &magic_num, &input_bufs_real_len, &model_params, input_bufs, input_buf_lens);
	if (ret)
	{
		printf("unpack [%s] failed.", file_path);
		return ret;
	}


	for(int i = 0; i < input_bufs_real_len; ++i)
	{
		ret = SaveFileBuff(input_bufs[i], input_buf_lens[i], output_file_paths[i]);
		if (ret)
		{
			printf("SaveFileBuff %s failed ...\n", output_file_paths[i]);
			return ret;
		}
	}

	//printf("MODEL_VERSION=%ld\n", model_params.version);
	std::cout << "MODEL_VERSION=" << model_params.model_version <<std::endl;
	printf("MAX_NCHW=%d,%d,%d,%d\n", model_params.n, model_params.c, model_params.h, model_params.w);

	return ret;
}

int main(int argc, char **argv)
{
	int ret = 0;
	std::map<std::string, std::function<int (std::string&)> > function_map;
	function_map["PACK"] = pack_file;
	function_map["UNPACK"] = unpack_file;

	if (3 != argc)
	{
		printf("Usage %s [TOOL_TYPE] [xxx:yyy:zzz] failed ...\n", argv[0]);
		printf("[TOOL_TYPE = PACK] \"conf_path:json_path:params_path(optional, realpath or NULL):model_name:model_version:magic_num:output_path\"; \n");
		printf("[TOOL_TYPE = UNPACK] \"packed_path:output_json_path:output_params_path(optional, realpath or NULL)\"; \n");
		return IFLYPU_ERROR_GENERAL;
	}

	std::string mode = argv[1];
	std::string params_str = argv[2];
	if (function_map.find(mode) == function_map.end())
	{
		std::cout << "Can not find " << mode << " in the tool_type_map" << std::endl;
		return IFLYPU_ERROR_GENERAL;
	}

	ret = function_map[mode](params_str);
	if(ret)
	{
		std::cout << mode << " failed." << std::endl;
	}

	return ret;
}
