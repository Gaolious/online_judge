#ifndef INCLUDED_OPTION_HEADER
#define INCLUDED_OPTION_HEADER

typedef struct _options_
{
    int uid, gid ;
    unsigned long long time_limit; // 1 time_limit = 0.001 seconds
    unsigned long long memory_limit; // milli seconds
    bool verbose ;
} OPTION;

bool parse_options(int argc, char **argv, OPTION *pOption);
#endif