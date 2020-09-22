#define DECLARE_GLOBAL_OPTION

#include <stdlib.h>
#include <string.h>
#include "../inc/opt.h"

template <typename T>
bool parseValue(const char *command, char *parameter, T *ret)
{
    char *p ;
    int len = strlen(command);
    if (parameter == NULL) return false ;
    if ( strncmp(parameter, command, len) != 0 ) return false ;

    *ret = 0;
    for ( p = parameter + len; p && *p ; p ++ )
    {
        if ( *p < '0' || *p > '9' ) return false ;
        *ret = (*ret) * 10 + (*p - '0') ;
    }
    return true;
}
bool is_arg(const char *command, char *parameter)
{
    int len = strlen(command);
    if (parameter == NULL) return false ;
    return strncmp(parameter, command, len) == 0;
}

bool parse_options(int argc, char **argv, OPTION *pOption)
{
    int i ;

    for ( i = 0 ; i < argc ; i ++ )
    {
        if ( parseValue("--uid=", argv[i], &pOption->uid ) ) continue;
        else if ( parseValue("--gid=", argv[i], &pOption->gid ) ) continue;
        else if ( parseValue("--time_limit=", argv[i], &pOption->time_limit ) ) continue;
        else if ( parseValue("--memory_limit=", argv[i], &pOption->memory_limit ) ) continue;
        else if ( is_arg("--verbose", argv[i]) )
        {
            pOption->verbose = true;
            continue;
        }
        else
        {
            // log
        }
    }

    if ( pOption->uid <= 0 ) return false ;
    if ( pOption->gid <= 0 ) return false ;
    if ( pOption->time_limit <= 0ll ) return false ;
    if ( pOption->memory_limit <= 0ll ) return false ;
    
    return true ;
}