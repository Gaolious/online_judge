#define DECLARE_GLOBAL_OPTION

#include <cstdlib>
#include <cstring>
#include <cstdio>

#include <inc/context.h>
#include <inc/utils.h>
#include <csignal>

Context g_ctx;

enum SIGNAL_ACTION { SIGNAL_IGNORE, SIGNAL_INTERRUPT, SIGNAL_FATAL };

struct signal_rule {
    int signum;
    SIGNAL_ACTION action;
};


template <typename T>
bool parseInteger(const char *command, char *parameter, T *ret)
{
    char *p ;
    int len = strlen(command);
    if (parameter == NULL) return false ;
    if ( strncmp(parameter, command, len) != 0 ) return false ;

    *ret = 0;
    for ( p = parameter + len; p && *p ; p ++ )
    {
        if ( *p < '0' || *p > '9' ) return false ;
        *ret = (*ret) * 10 + (*p - '0') ;
    }
    return true;
}
bool parseString(const char *command, char *parameter, char *ret)
{
    int i;
    char *p ;
    int len = strlen(command);
    if (parameter == NULL) return false ;
    if ( strncmp(parameter, command, len) != 0 ) return false ;

    p = parameter + len ;
    len = strlen(p);
    if (len >= 2 && p[0] == p[len-1] && ( *p == '\'' || *p == '"' ) )
    {
        p++;
        len -=2;
    }
    memcpy( (void *)ret, (void *)p, sizeof(char) * len);
    ret[len] = 0x00;

    return true ;
}

bool is_arg(const char *command, char *parameter)
{
    int len = strlen(command);
    if (parameter == NULL) return false ;
    return strncmp(parameter, command, len) == 0;
}

bool Context::parse(int argc, char **argv)
{
    int i ;
    this->log_level = LOG_LEVEL::DEBUG;

    for ( i = 0 ; i < argc ; i ++ )
    {
        if (parseInteger("--uid=", argv[i], &this->uid) ) continue;
        else if (parseInteger("--gid=", argv[i], &this->gid) ) continue;
        else if (parseInteger("--time=", argv[i], &this->time_limit) ) continue;
        else if (parseInteger("--memory=", argv[i], &this->memory_limit) ) continue;
        else if (parseString("--in=", argv[i], this->in_path) ) continue;
        else if (parseString("--out=", argv[i], this->out_path) ) continue;
        else if (parseString("--cmd=", argv[i], this->cmd_path) ) continue;
        else if ( is_arg("--verbose", argv[i]) )
        {
            this->log_level = LOG_LEVEL::INFO;
            continue;
        }
        else
        {
            // log
        }
    }

    if ( this->uid <= 0 ) return false ;
    if ( this->gid <= 0 ) return false ;
    if ( this->time_limit <= 0ll ) return false ;
    if ( this->memory_limit <= 0ll ) return false ;
    
    return true ;
}


void Context::initialize()
{

#ifdef _WIN32
    char *sep = "\\";
#else
    char *sep = (char *)"/";
#endif

    char buff[PATH_MAX];
    char *ret = rstrip(realpath(".", buff), sep);

    if (!ret)
    {
        perror("realpath");
        exit(EXIT_FAILURE);
    }

    sprintf(this->log_path, "%s%s%s", ret, sep, "sandbox.log");
    remove(this->log_path);
}

void Context::set_start_child_process() {
    clock_gettime(CLOCK_REALTIME, &this->child_start_ts);
}

void Context::set_end_child_process() {
    clock_gettime(CLOCK_REALTIME, &this->child_end_ts);
}

long long Context::get_child_elapsed_time()
{
    long long ret = 0 ;
    long long s = 1000000000ll;
    ret += (this->child_end_ts.tv_sec - this->child_start_ts.tv_sec) * s;
    ret += (this->child_end_ts.tv_nsec - this->child_start_ts.tv_nsec);
    return ret ;
}
void Context::set_pipes()
{}

static void signal_int(int signum)
{
    LOGD("signal : %d\n", signum);
}

static void signal_fatal(int signum)
{
    LOGD("signal : %d\n", signum);
}

void Context::set_signals()
{
    static const struct signal_rule signal_rules[] = {
        { SIGHUP,	SIGNAL_INTERRUPT },
        { SIGINT,	SIGNAL_INTERRUPT },
        { SIGQUIT,	SIGNAL_INTERRUPT },
        { SIGILL,	SIGNAL_FATAL },
        { SIGABRT,	SIGNAL_FATAL },
        { SIGFPE,	SIGNAL_FATAL },
        { SIGSEGV,	SIGNAL_FATAL },
        { SIGPIPE,	SIGNAL_FATAL },
//        { SIGPIPE,	SIGNAL_IGNORE },
        { SIGTERM,	SIGNAL_INTERRUPT },
//        { SIGUSR1,	SIGNAL_IGNORE },
//        { SIGUSR2,	SIGNAL_IGNORE },
        { SIGUSR1,	SIGNAL_FATAL },
        { SIGUSR2,	SIGNAL_FATAL },
        { SIGBUS,	SIGNAL_FATAL },
//        { SIGTTOU,	SIGNAL_IGNORE },
        { SIGTTOU,	SIGNAL_FATAL },
    };
    int i ;
    int len = sizeof(signal_rules) / sizeof(signal_rules[0]);

    struct sigaction sa_int{}, sa_fatal{};
    memset( &sa_int, 0x0, sizeof(sa_int));
    memset( &sa_fatal, 0x0, sizeof(sa_fatal));

    sa_int.sa_handler = signal_int;
    sa_fatal.sa_handler = signal_fatal;

    for (i=0 ; i<len ; i++)
    {
        switch (signal_rules[i].action) {
            case SIGNAL_IGNORE:
                signal(signal_rules[i].signum, SIG_IGN);
                break;
            case SIGNAL_INTERRUPT:
                sigaction(signal_rules[i].signum, &sa_int, NULL);
                break;
            case SIGNAL_FATAL:
                sigaction(signal_rules[i].signum, &sa_fatal, NULL);
                break;
            default:
                signal(signal_rules[i].signum, SIG_DFL);
                break;
        }
    }
}
