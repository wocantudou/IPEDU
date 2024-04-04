#ifndef __IFLYTEK_CV3_PACK_UNPACK_TYPE_H__
#define __IFLYTEK_CV3_PACK_UNPACK_TYPE_H__

#define MAX_MODEL_NAME_SIZE 128

enum ModelType
{
    ModelTypeNone,
    Float16,
    Float32,
    Float64,
    Int8, 
    Int16,  
    Int32,  
    Int64, 
    Uint8,  
    Uint16, 
    Uint32, 
    Uint64,
    ModelTypeCount,
};

typedef struct _PUModelParams
{
    _PUModelParams():n(0),
                c(0),
                h(0),
                w(0),
                model_version(0),
                model_type(ModelTypeNone),
                input_res_num(0)
                {
                    model_name[0] = '\0';
                    // memset(model_name, 0 , MAX_MODEL_NAME_SIZE);
                }

    int         n;
    int         c;
    int         h;
    int         w;
    int         input_res_num;
    int         model_version;
    char        model_name[MAX_MODEL_NAME_SIZE];
    ModelType   model_type;
}ModelParams;


#endif