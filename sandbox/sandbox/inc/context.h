#include <climits>

#include <inc/auto_lock.h>
#include <inc/logger.h>

#ifndef INCLUDED_OPTION_HEADER
#define INCLUDED_OPTION_HEADER

class Context
{
public:
    /////////////////////////////////
    // option param
    int uid{}, gid{} ;
    unsigned long long time_limit{}; // 1 time_limit = 0.001 seconds
    unsigned long long memory_limit{}; // milli seconds
    LOG_LEVEL log_level ;

    char cmd_path[PATH_MAX]{};
    char in_path[PATH_MAX]{};
    char out_path[PATH_MAX]{};

    /////////////////////////////////
    // logger
    SmartAutoLock log_lock;
    char log_path[PATH_MAX]{};

    /////////////////////////////////
    // child process
    pid_t child_pid{};
    struct timespec child_start_ts{};
    struct timespec child_end_ts{};

    /////////////////////////////////
    // file descriptors
    int stdout_pipe[2];
    int stderr_pipe[2];
    int stat_pipe[2];

public:
    void initialize();
    bool parse(int argc, char **argv);

    void set_start_child_process();
    void set_end_child_process();
    long long get_child_elapsed_time();

    // pipe
    void set_pipes();
    void set_signals();

} ;

extern Context g_ctx;

#endif
