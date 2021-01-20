#include <unistd.h>

int main(int argc, char **argv)
{
    int ret = -1;
    int i = 1 ;

    sleep(1);

    for ( ret = 2 ; ret >= 0 ; ret -- )
        i /= ret ;

    sleep(1);

    return ret ;
}