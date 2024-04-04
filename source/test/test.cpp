#include <vector>
#include <string>
#include <map>
#include <string>
#include <iostream>
#include <functional>
#include <string.h>

#include "ipedu_type.h"
#include "ipedu_error_module.h"
#include "ipedu_api.h"

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

int pack_encrypt(std::string& params_str)
{
	int ret = IFLYPEDU_SUCCESS;

	std::vector<std::string> params_vec = str_split(params_str, ":");
	if(params_vec.size() < 9)
	{
		std::cout << "pack_encrypt params is invalid." << std::endl;
		return IFLYPEDU_ERROR_GENERAL;
	}
	
	int file_num = std::atoi(params_vec[1].c_str());
	if((params_vec.size() != (8 + file_num)) || (file_num > IPEDUParams::MAX_RES_INPUT_NUM))
	{
		std::cout << "pack_encrypt params is invalid." << std::endl;
		return IFLYPEDU_ERROR_GENERAL;
	}

	IPEDUParams function_params;
	IPEDUModelParams model_params;

	function_params.conf_path = (char*)params_vec[0].c_str();
	function_params.real_input_num = file_num;
	for(int index = 0; index < file_num; index++)
	{
		function_params.input_res_paths[index] = (char*)params_vec[2 + index].c_str();
	}
	memcpy(model_params.model_name, params_vec[2 + file_num].c_str(), strlen(params_vec[2 + file_num].c_str()) + 1);
	model_params.model_version = std::atoi(params_vec[3 + file_num].c_str());
	model_params.model_type = static_cast<IPEDUModelType>(std::atoi(params_vec[4 + file_num].c_str()));
	const int magic_num = std::atoi(params_vec[5 + file_num].c_str());
	const char* key = params_vec[6 + file_num].c_str();
	function_params.packencrypt_path = (char*)params_vec[7 + file_num].c_str();


	ret = packencrypt(key, magic_num, &model_params, &function_params);
	if(ret)
	{
		std::cout << "pack_encrypt process failed." << std::endl;
	}

	return ret;
}

int decrypt_unpack(std::string& params_str)
{
	int ret = 0;

	IPEDUParams function_params;
	IPEDUModelParams model_params;

	std::vector<std::string> params_vec = str_split(params_str, ":");
	if((params_vec.size() < 3) || (params_vec.size() > 2 + IPEDUParams::MAX_RES_INPUT_NUM))
	{
		std::cout << "decrypt_unpack params is invalid." << std::endl;
		return IFLYPEDU_ERROR_GENERAL;
	}

	function_params.packencrypt_path = (char*)params_vec[0].c_str();
	const char* key = params_vec[1].c_str();
	for(int index = 0; index < params_vec.size() - 2; index++)
	{
		function_params.input_res_paths[index] = (char*)params_vec[2 + index].c_str();
	}

	int magic_num = 0;

	ret = decryptunpack(key, &magic_num, &model_params, &function_params);
	if(ret)
	{
		std::cout << "decrypt_unpack process failed." << std::endl;
		return ret;
	}

	printf("OUTPUT FILE NUM : %d\n", function_params.real_input_num);
	printf("MAGIC_NUMBER : %d\n", magic_num);
	printf("MODEL_NAME : %s\n", model_params.model_name);
	printf("MODEL_TYPE : %d\n", model_params.model_type);
	printf("MODEL_VERSION : %ld\n", model_params.model_version);
	printf("MAX_IPUTY_SIZE : [N:%d, C:%d, H:%d, W:%d]\n", model_params.n, model_params.c, model_params.h, model_params.w);
	
	return ret;
}

struct{
    int x;
    char y;
}s;

int main(int argc, char **argv)
{

	int ret = 0;
	std::map<std::string, std::function<int (std::string&)> > function_map;
	function_map["PACK_ENCRYPT"] = pack_encrypt;
	function_map["DECRYPT_UNPACK"] = decrypt_unpack;

	if (3 != argc)
	{
		printf("Usage %s [TOOL_TYPE] [xxx:yyy:zzz] failed ...\n", argv[0]);
		printf("[TOOL_TYPE = PACK_ENCRYPT] \"conf_path:file_num:file1_path:fiel2_path:...:model_name:model_version:model_type:magic_num:key:output_path\"; \n");
		printf("[TOOL_TYPE = DECRYPT_UNPACK] \"packed_path:key:output1_path:output2_path:...\"; \n");
		return -1;
	}

	std::string mode = argv[1];
	std::string params_str = argv[2];
	if (function_map.find(mode) == function_map.end())
	{
		std::cout << "Can not find " << mode << " in the tool_type_map" << std::endl;
		return -1;
	}

	ret = function_map[mode](params_str);
	if(ret)
	{
		std::cout << mode << " failed." << std::endl;
	}

	return ret;

}