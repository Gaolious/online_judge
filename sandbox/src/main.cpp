#include <stdio.h>
#include <inc/context.h>

int main(int argc, char **argv, char **envp)
{
    g_ctx.initialize();
    g_ctx.parse(argc, argv);

    return 0;
}