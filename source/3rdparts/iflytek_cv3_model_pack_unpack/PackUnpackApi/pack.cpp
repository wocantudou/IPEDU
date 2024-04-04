#include <memory>
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include "iflytek_cv3_pack_unpack_type.h"
#include "iflytek_cv3_pack_unpack_error_module.h"
#include "iflytek_cv3_pack_unpack_api.h"
//static const int magic_num = 45678;//magic num

#define HEAD_LEN_SHIFT					(1)
#define JSON_PARAMS_SHIFT				(2)

int read_file(const std::string& file_path, std::vector<std::string>& file_list_vec)
{
	file_list_vec.clear();
	std::ifstream			fin;
	fin.open( file_path, std::ios::in);
	if (!fin.is_open())
	{
		printf("open file : %s failed !!!\n",  file_path.c_str());
		return IFLYPU_ERROR_OPEN_FILE_FAILED;
	}

	std::string line;
	while (std::getline(fin, line))
	{
		file_list_vec.push_back(line);
	}
	fin.close();
	return IFLYPU_SUCCESS;
}

std::vector<std::string> str_split(std::string str, const std::string & pattern)
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

int parse_model_params(std::string& model_params_str, std::string& model_name, ModelParams& model_params)
{
	int ret = IFLYPU_SUCCESS;
	std::vector<std::string> type_params = str_split(model_params_str, " ");
	if(type_params.size() != 2)
	{
		printf("conf format error.");
		return IFLYPU_ERROR_CONF_FORMAT_UNSUPPORTED;
	}
	model_name = type_params.front();

	std::vector<std::string> params = str_split(type_params.back(), "=");
	if(params.size() != 2)
	{
		printf("conf format error.");
		return IFLYPU_ERROR_CONF_FORMAT_UNSUPPORTED;
	}
	std::vector<std::string> params_value = str_split(params.back(), ",");
	if(params_value.size() != 4)
	{
		printf("conf format error.");
		return IFLYPU_ERROR_CONF_FORMAT_UNSUPPORTED;
	}

	model_params.n = std::atoi(params_value.at(0).c_str());
	model_params.c = std::atoi(params_value.at(1).c_str());
	model_params.h = std::atoi(params_value.at(2).c_str());
	model_params.w = std::atoi(params_value.at(3).c_str());

	return ret;
}

int parse_conf(const std::string& conf_path, std::map<std::string, ModelParams>& model_params_map)
{
	int ret = IFLYPU_SUCCESS;
	std::vector<std::string> conf_line_vec;
	ret = read_file(conf_path, conf_line_vec);
	if(ret)
	{
		printf("open conf [%s] failed.", conf_path.c_str());
		return ret;
	}

	for(auto& conf_line : conf_line_vec)
	{
		std::string model_name;
		ModelParams model_params;
		ret = parse_model_params(conf_line, model_name, model_params);
		if(ret)
		{
			printf("parse conf [%s] failed.", conf_line.c_str());
			return ret;
		}
		model_params_map[model_name] = model_params;
	}

	return ret;
}

int PACKUNPACKAPI pack(const int magic_num, const char *conf_path, const char * model_name, const int model_version, const ModelType model_type,\
						const char **input_buf_arr, const int* input_buf_len_arr, const int input_buf_arr_len, char* pack_buffer)
{
	int ret = IFLYPU_SUCCESS;

	if(conf_path == nullptr || model_name == nullptr || pack_buffer == nullptr)
	{
		printf("pack invalid params.\n");
		return IFLYPU_ERROR_NULL_PTR;
	}

	if(model_type <= ModelTypeNone || model_type >= ModelTypeCount)
	{
		printf("pack invalid params.\n");
		return IFLYPU_ERROR_INVAILD_PARAMS;
	}

	for(int i = 0; i < input_buf_arr_len; ++i)
	{
		if(nullptr == input_buf_arr[i])
		{
			printf("pack invalid params.\n");
			return IFLYPU_ERROR_NULL_PTR;
		}
	}

	int model_name_len = strlen(model_name);
	
	if(model_name_len >= MAX_MODEL_NAME_SIZE)
	{
		printf("pack invalid params.\n");
		return IFLYPU_ERROR_INVAILD_PARAMS;
	}

	std::map<std::string, ModelParams> model_params_map;
	ret = parse_conf(conf_path, model_params_map);
	if(ret)
	{
		printf("parse conf [%s] failed.", conf_path);
		return ret;
	}

	if (model_params_map.find(model_name) == model_params_map.end())
	{
		printf("Can not find [%s] in conf [%s]", model_name, conf_path);
		return IFLYPU_ERROR_MODEL_TYPE_UNSUPPORTED;
	}

	ModelParams& model_params = model_params_map[model_name];
	memcpy(model_params.model_name, model_name, model_name_len);
	model_params.model_name[model_name_len] = '\0';
	model_params.model_version = model_version;
	model_params.model_type = model_type;
	model_params.input_res_num = input_buf_arr_len;

	//int head_len = JSON_PARAMS_SHIFT * sizeof(int) + sizeof(ModelParams);	//head_len
	

	int data_shift_size = 0;
	int curr_data_size = sizeof(magic_num);
	memcpy(pack_buffer + data_shift_size, (void*)(&magic_num), curr_data_size);

	data_shift_size += curr_data_size;
	curr_data_size = sizeof(input_buf_arr_len);
	memcpy(pack_buffer + data_shift_size, (void*)(&input_buf_arr_len), curr_data_size);

	data_shift_size += curr_data_size;
	curr_data_size = sizeof(ModelParams);
	memcpy(pack_buffer + data_shift_size, (void*)(&model_params), curr_data_size);

	for(int i = 0; i < input_buf_arr_len; ++i)
	{
		data_shift_size += curr_data_size;
		curr_data_size = sizeof(input_buf_len_arr[i]);
		memcpy(pack_buffer + data_shift_size, (void*)(&input_buf_len_arr[i]), curr_data_size);
		data_shift_size += curr_data_size;
		curr_data_size = input_buf_len_arr[i];
		memcpy(pack_buffer + data_shift_size, (void*)(input_buf_arr[i]), curr_data_size);
	}
	return ret;
}