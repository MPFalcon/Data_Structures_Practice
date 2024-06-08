#include "security_functions.h"

uint32_t hash_value(const char * p_str)
{
    uint32_t hash = 5381;
    int32_t  c    = 0;

    while ((c = *(p_str++)))
    {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

/*** EOF ***/
