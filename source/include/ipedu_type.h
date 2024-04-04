#ifndef __IPEDU_TYPE_H__
#define __IPEDU_TYPE_H__

#define MAX_MODEL_NAME_SIZE 128

enum IPEDUModelType
{
    IPEDU_ModelTypeNone,
    IPEDU_Int8,	    
    IPEDU_Float32,
    IPEDU_ModelTypeCount,
};

typedef struct _BufferObj
{
    _BufferObj():buff(nullptr),
                buff_len(0){}


    char*             buff;
    int               buff_len;
}IPEDUBufferObj;

typedef struct _Params
{
    _Params()   :conf_path(nullptr),
                packencrypt_path(nullptr),
                real_input_num(1)
    {
        // json_path = nullptr;
        // params_path = nullptr;
        // memset(input_res_paths, 0, MAX_RES_INPUT_NUM * sizeof(char*));
        // memset(input_res_bufs, 0, MAX_RES_INPUT_NUM* sizeof(IPEDUBufferObj));
        int i = 0;
        for (i = 0; i < MAX_RES_INPUT_NUM; ++i)
        {
            input_res_paths[i] = nullptr;
        }
    }
    static const int    MAX_RES_INPUT_NUM = 2;

	char*               conf_path;
    char*               packencrypt_path;
    // char*               json_path;
    // char*               params_path;
    char*               input_res_paths[MAX_RES_INPUT_NUM];

    IPEDUBufferObj      packencrypt_buf;
	// IPEDUBufferObj      json_buf;
	// IPEDUBufferObj      params_buf;
    IPEDUBufferObj      input_res_bufs[MAX_RES_INPUT_NUM];

    int                 real_input_num;
    
}IPEDUParams;

typedef struct _ModelParams
{
    _ModelParams():n(0),
                c(0),
                h(0),
                w(0),
                model_version(0),
                model_type(IPEDU_ModelTypeNone)
                {
                    model_name[0] = '\0';
                    // memset(model_name, 0 , MAX_MODEL_NAME_SIZE);
                }
            
    int                 n;
    int                 c;
    int                 h;
    int                 w;
    int                 model_version;
    char                model_name[MAX_MODEL_NAME_SIZE];
    IPEDUModelType      model_type;
}IPEDUModelParams;

#endif
