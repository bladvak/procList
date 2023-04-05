#include "proclist.h"

const char *afterSubstr(const char *str, const char *sub)
{
    const char* occurence;
    if( !(occurence = strstr(str, sub)))
        return NULL;

    return str + (occurence - str) + strlen(sub);
}