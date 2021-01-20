#include <stdlib.h>

int main(int argc, char **argv)
{
    int ret = -1;

    do
    {
        if (argc != 2)
            return ret;

        int size = 0;
        for (char *p = argv[1] ; p && *p ; p ++ )
        {
            if ( *p < '0' || *p > '9' )
                return ret ;

            size = size * 10 + ( p[0] - '0' ) ;
        }

        void *mem = malloc(size);

        if (mem)
        {
            for ( int i = 0 ; i < size ; i ++ )
                ((char *)mem)[ i ] = i % 255;
            ret = 0;
            free(mem);
        }

    } while (false);

    return ret ;
}