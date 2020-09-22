#include <stdio.h>
#include "../inc/sum.h"
#include "../inc/opt.h"


int main(int argc, char **argv, char **env)
{
    bool ret ;

    ret = parse_options(argc, argv);
    if (!ret)
        return 0;
    return 0;
}