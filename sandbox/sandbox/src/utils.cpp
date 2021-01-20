#include <cstring>

char *rstrip(char *str, const char *chars)
{
    char map[256] = {0, };
    int i, len ;
    char *p = str;

    if ( !p ) return p;

    len = strlen(chars);
    for ( i = 0 ; i < len ; i ++ )
        map[ chars[i] ] = 1;

    len = strlen(p);
    for ( i = len-1 ; i >= 0 && map[ p[i] ]; i -- )
        p[i] = 0x0;

    return str;
}

char *lstrip(char *str, const char *chars)
{
    char map[256] = {0, };
    int i, len ;
    char *p = str;
    if ( !p ) return p;

    len = strlen(chars);
    for ( i = 0 ; i < len ; i ++ )
        map[ chars[i] ] = 1;

    len = strlen(p);
    for ( i = 0 ; i < len && map[ *p ] ; i++ )
        p++;

    return p;
}
