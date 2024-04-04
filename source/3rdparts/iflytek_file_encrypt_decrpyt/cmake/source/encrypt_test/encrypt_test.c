#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "encrypt/encrypt.h"
#include <sys/stat.h>  

#define INPUT_FILE_BUFFR_SIZE 1024

enum MODEL_PARAM
{
	ENCRYPT_SUCCESS = 0,
	ENCRYPT_NULL_HANDLE_KEY,
	ENCRYPT_INCORRECT_KEY_SIZE,
	ENCRYPT_NULL_HANDLE_MODEL,
	ENCRYPT_ZERO_SIZE_MODEL,
	ENCRYPT_NULL_HANDLE_OUTPUT,
};

const char* output_info_table[] = 
{
	"run successfully" ,
	"input key is null handle" ,
	"key size is out of range" ,
	"input model is null handle" ,
	"input model size is zero" ,
	"output buffer is null handle" 
};


ifly_int32_t main(ifly_int32_t argc, ifly_int8_t *argv[])
{
	FILE *fp_org_input = NULL;
	FILE *fp_encrypt = NULL;

	clock_t start, pause;
	ifly_int8_t		ret = 0;
	ifly_float_t	fTaskProg	= 0.0f;
	ifly_uint64_t nFileSize		= 0;
	ifly_uint64_t nReadIdx		= 0;
	ifly_uint64_t nReadLen	= 0;
	ifly_uint32_t nTimeIdx		= 0;
	
	ifly_int8_t *ori_model_name = argv[1];
	ifly_int8_t *encrypt_model_key = argv[2];
	ifly_int8_t *encrypt_model_name = argv[3];

	ifly_int8_t *buffer_org_input = (ifly_int8_t *)malloc(INPUT_FILE_BUFFR_SIZE);

	printf("{\"code\":\"start\",\"result\":\"true\",\"describer\":\"\"}\n");
	if (4 != argc)
	{
		printf("{\"code\":\"process\",\"result\":\"true\",\"describer\":\"100.00\"}\n");
		printf("{\"code\":\"end\",\"result\":\"false\",\"describer\":\"please input right number of params: encrypt_test [ori_model_name] [encrypt_key] [new_model_name]\"}\n");
		exit(EOF);
	}

	fp_org_input = fopen(ori_model_name, "rb");
	if (NULL == fp_org_input)
	{
		printf("{\"code\":\"process\",\"result\":\"true\",\"describer\":\"100.00\"}\n");
		printf("{\"code\":\"end\",\"result\":\"false\",\"describer\":\"model to be encrypted don't exist\"}\n");
		exit(EOF);
	}
	fp_encrypt = fopen(encrypt_model_name, "wb");
	if (NULL == fp_encrypt)
	{
		printf("{\"code\":\"process\",\"result\":\"true\",\"describer\":\"100.00\"}\n");
		printf("{\"code\":\"end\",\"result\":\"false\",\"describer\":\"model to be generated can't open\"}\n");
		exit(EOF);
	}

	fseek(fp_org_input, 0, SEEK_END);
	nFileSize = ftell(fp_org_input);
	fseek(fp_org_input, 0, SEEK_SET);

	start = clock();
	while (nReadLen = fread(buffer_org_input, sizeof(ifly_int8_t), INPUT_FILE_BUFFR_SIZE, fp_org_input))
	{
		ret = iEncryptDoProcessV20190001(encrypt_model_key, strlen(encrypt_model_key), buffer_org_input, INPUT_FILE_BUFFR_SIZE, buffer_org_input);
		if ( ENCRYPT_SUCCESS != ret)
		{
			printf("{\"code\":\"process\",\"result\":\"true\",\"describer\":\"100.00\"}\n");
			printf("{\"code\":\"end\",\"result\":\"false\",\"describer\":\"%s\"}\n", output_info_table[ret]);
			return -1;
		}
		fwrite(buffer_org_input, sizeof(ifly_int8_t), nReadLen, fp_encrypt);
		nReadIdx += nReadLen;
		pause = clock();
		if (nTimeIdx <= (pause - start) / CLOCKS_PER_SEC)
		{
			fTaskProg = 100.0f *nReadIdx / nFileSize;
			nTimeIdx++;
			printf("{\"code\":\"process\",\"result\":\"true\",\"describer\":\"%.2f\"}\n", fTaskProg);
		}
	}
	if (ENCRYPT_SUCCESS == ret)
	{
		printf("{\"code\":\"process\",\"result\":\"true\",\"describer\":\"100.00\"}\n");
		printf("{\"code\":\"end\",\"result\":\"true\",\"describer\":\"Completed successfully\"}\n");
	}

	fclose(fp_encrypt);
	fclose(fp_org_input);

	free(buffer_org_input);
	return 0;
}

