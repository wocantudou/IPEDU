#include <iostream>
#include <fstream>
#include <string> 
#include <memory>

#include "iflytek_cv3_pack_unpack_error_module.h"
#include "iflytek_cv3_pack_unpack_api.h"

int PACKUNPACKAPI MallocFileBuff(const char* file_path, char** data_buf, int* data_len)
{
	std::ifstream file_fin(file_path, std::ios::in | std::ios::binary);
	if (file_fin.fail())
	{
		printf("Open Data File From %s Failed \n", file_path);
		return IFLYPU_ERROR_OPEN_FILE_FAILED;
	}

	file_fin.seekg(0, std::ios::end);    // go to the end
	*data_len = file_fin.tellg();           // report location (this is the length)
	file_fin.seekg(0, std::ios::beg);    // go back to the beginning
	*data_buf = new (std::nothrow)char[*data_len];    // allocate memory for a buffer of appropriate dimension
	if (NULL == data_buf)
	{
		printf("Alloc Memory data_buffer failed ...\n");
		file_fin.close();
		return IFLYPU_ERROR_MEM_ALLOC;
	}
	file_fin.read(*data_buf, *data_len);       // read the whole file into the buffer
	file_fin.close();                    // close file handle
	return IFLYPU_SUCCESS;
}

int PACKUNPACKAPI FreeFileBuff(char** data_buf)
{
	if (*data_buf)
	{
		delete[] *data_buf;
		*data_buf = NULL;
	}
	else
	{
		printf("Buffer is NULL ...\n");
		return IFLYPU_ERROR_NULL_PTR;
	}

	return IFLYPU_SUCCESS;
}

int PACKUNPACKAPI SaveFileBuff(char* data_buf, const int buff_len, const char* file_path)
{
	std::ofstream file_out;
	file_out.open(file_path, std::ios::out | std::ios::binary);
	if (!file_out.is_open())
	{
		printf("Open File From %s Failed \n", file_path);
		return IFLYPU_ERROR_OPEN_FILE_FAILED;
	}

	file_out.write(data_buf, buff_len);
	file_out.close();

	return IFLYPU_SUCCESS;
}
