#define LOGTAG "CHILD"
#include <unistd.h>
#include <inc/context.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <sys/resource.h>

bool is_blank(char c)
{
    switch (c) {
        case '\n':
        case '\r':
        case '\t':
        case ' ':
            return true ;
        default:
            return false;
    }
}
#define DUMP_CONTEXT(pCtx) do { \
    LOGD("addr : %p", pCtx); \
    LOGD("uid : %d", pCtx->uid);\
    LOGD("gid : %d", pCtx->gid);\
    LOGD("time_limit : %llu", pCtx->time_limit);\
    LOGD("memory_limit : %llu", pCtx->memory_limit);\
    LOGD("log_level : %d", pCtx->log_level);\
    LOGD("cmd_path : %s", pCtx->cmd_path);\
    LOGD("in_path : %s", pCtx->in_path);\
    LOGD("out_path : %s", pCtx->out_path);\
    LOGD("log_path : %s", pCtx->log_path);\
    LOGD("child_pid : %d", pCtx->child_pid);\
} while (false )

void dump_rss(struct rusage *usage)
{
    LOGD("ru_utime  = %ld.%06ld; Total amount of user time used", usage->ru_utime.tv_sec, usage->ru_utime.tv_usec);
    LOGD("ru_stime  = %ld.%06ld; Total amount of system time used", usage->ru_stime.tv_sec, usage->ru_stime.tv_usec);
    LOGD("ru_maxrss = %ld; Maximum resident set size (in kilobytes)", usage->ru_maxrss);
    LOGD("ru_ixrss  = %ld; Amount of sharing of text segment memory with other processes (in kilobytes)", usage->ru_ixrss);
    LOGD("ru_idrss  = %ld; Amount of data segment memory used (kilobyte-seconds)", usage->ru_idrss);
    LOGD("ru_isrss  = %ld; Amount of stack memory used (kilobyte-seconds)", usage->ru_isrss);
    LOGD("ru_minflt = %ld; Number of soft page faults (i.e. those serviced by reclaiming a page from the list of pages awaiting reallocation.)", usage->ru_minflt);
    LOGD("ru_majflt = %ld; Number of hard page faults (i.e. those that required I/O).", usage->ru_majflt);
    LOGD("ru_nswap  = %ld; Number of times a process was swapped out of physical memory.", usage->ru_nswap);
    LOGD("ru_inblock= %ld; Number of input operations via the file system.  Note: This and `ru_oublock' do not include operations with the cache.", usage->ru_inblock);
    LOGD("ru_oublock= %ld; Number of output operations via the file system.", usage->ru_oublock);
    LOGD("ru_msgsnd = %ld; Number of IPC messages sent.", usage->ru_msgsnd);
    LOGD("ru_msgrcv = %ld; Number of IPC messages received.", usage->ru_msgrcv);
    LOGD("ru_nsignals = %ld; Number of signals delivered.", usage->ru_nsignals);
    LOGD("ru_nvcsw = %ld; Number of voluntary context switches.", usage->ru_nvcsw);
    LOGD("ru_nivcsw = %ld; Number of involuntary context switches.", usage->ru_nivcsw);
}

void onParent(Context *pCtx)
{
    ENTER_FUNCTION();

    struct rusage usage = {0, };
    int p, stat;

    pCtx->set_start_child_process();

    p = wait4(pCtx->child_pid, &stat, 0, &usage);

    pCtx->set_end_child_process();

    long long s = pCtx->get_child_elapsed_time();
    long long ns = 1000000000ll;
    LOGD("Elapsed time : %lld.%09lld", s / ns , s % ns);
    dump_rss(&usage);

    if (WIFEXITED(stat))
    {
        LOGD("CHILD process exit code = %d", WEXITSTATUS(stat));
    }
    else if ( WIFSIGNALED(stat) )
    {
        LOGD("CHILD process received signal = %d(%s)", WTERMSIG(stat), strsignal(WTERMSIG(stat)));
    }
    else if (WIFSTOPPED(stat))
    {
        LOGD("WSTOPSIG(stat) = %d", WSTOPSIG(stat));
    }

    LEAVE_FUNCTION();
}

//bool setup_file_descriptors() {}
//bool setup_signals(){}
bool fork_child(Context *pCtx)
{
    bool ret = true ;
    char *argv[100] = {NULL, };
    int i, idx ;
    int len = strlen(pCtx->cmd_path);

    ENTER_FUNCTION();

    for ( i = 0, idx=0 ; i < len && idx < 100 ; )
    {
        while ( i < len && is_blank(pCtx->cmd_path[i]) )
            pCtx->cmd_path[i++] = 0x0;

        if ( i >= len || idx >= 100 ) break;

        argv[idx++] = pCtx->cmd_path + i;

        while ( i < len && !is_blank(pCtx->cmd_path[i]) )
            i++;
    }

    do
    {
        pCtx->set_signals();
        pCtx->set_pipes();
        pCtx->child_pid = fork();

        if ( pCtx->child_pid == -1 )
        {
            LOGE("Failed to fork.");
            ret = false ;
            break;
        }

        if ( pCtx->child_pid == 0 )
        {
            int ret_execv = execv(argv[0], argv);
            if ( ret_execv < 0 )
            {
                LOGE("Failed to run execv. command : %s", pCtx->cmd_path);
                kill( getpid(), SIGKILL);
                kill( -getpid(), SIGKILL);
            }
        }
        else
        {
            onParent(pCtx);
        }
    } while (false);

    LEAVE_FUNCTION();

    return ret;
}