#include <unistd.h>

int main(int argc, char **argv)
{
    int ret = -1;

    do
    {
        if (argc != 2)
            return ret;

        int ms = 0;
        for (char *p = argv[1] ; p && *p ; p ++ )
        {
            if ( *p < '0' || *p > '9' )
                return ret ;

            ms = ms * 10 + (p[0] - '0' ) ;
        }

        sleep(ms);

    } while (false);

    return ret ;
}