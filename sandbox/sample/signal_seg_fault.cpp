#include <unistd.h>

int main(int argc, char **argv)
{
    int *p = 0x00 ;
    *p = 1;
    sleep(1);
    return 0;
}