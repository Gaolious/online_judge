#include <sys/types.h>
#include <unistd.h>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <climits>

#include <inc/logger.h>
#include <inc/context.h>

const char *GetLogLevel(LOG_LEVEL log_level)
{
    switch (log_level) {
        case LOG_LEVEL::INFO:
            return "INFO";
        case LOG_LEVEL::DEBUG:
            return "DEBUG";
        case LOG_LEVEL::WARN:
            return "WARN";
        case LOG_LEVEL::ERROR:
            return "ERROR";
    }
}

const char *GetShortLogLevel(LOG_LEVEL log_level)
{
    switch (log_level) {
        case LOG_LEVEL::INFO:
            return "I";
        case LOG_LEVEL::DEBUG:
            return "D";
        case LOG_LEVEL::WARN:
            return "W";
        case LOG_LEVEL::ERROR:
            return "E";
    }
}

void log(
        LOG_LEVEL log_level, const char *log_tag, const char *filename, const char *function,
        const int line, const char *fmt, ...
)
{
    va_list ap ;
    pid_t nThreadID ;
    char *pFilename = (char *)filename ;
    int nIdx = 0 ;
    int i ;
    int len ;
    const int BUFFER_SIZE = 10240 ;
    char buff[BUFFER_SIZE]={0, };

    if ( log_tag == 0 || *log_tag == 0 || filename == 0 || *filename == 0 || function == 0 || *function == 0 )
        return ;

    if (log_level < g_ctx.log_level )
        return;


    nThreadID = pthread_self();

    nIdx = 0 ;
    len = strlen( pFilename ) ;

    for ( i = len - 1 ; i > 0 ; i -- )
        if ( pFilename[i] == '/' )
        {
            nIdx = i + 1;
            break;

        }

    if ( sizeof(nThreadID) == 8 )
        snprintf( buff, BUFFER_SIZE, "[%s|%s:%llu|%s|%s():%d] ",GetLogLevel(log_level), log_tag, (long long unsigned int)nThreadID, pFilename + nIdx, function, line );
    else
        snprintf( buff, BUFFER_SIZE, "[%s|%s:%u|%s|%s():%d] ",GetLogLevel(log_level), log_tag, nThreadID, pFilename + nIdx, function, line );

    nIdx = strlen(buff);

    va_start( ap, fmt );
    if ( nIdx < BUFFER_SIZE )
    {
        vsnprintf( buff + nIdx , BUFFER_SIZE - nIdx,  fmt, ap ) ;
        nIdx += strlen(buff + nIdx);
    }
    va_end(ap);

    if ( nIdx < BUFFER_SIZE && buff[nIdx-1] != '\n' ) buff[nIdx++] = '\n';
    if ( nIdx < BUFFER_SIZE ) buff[nIdx] = 0x0;
    buff[ BUFFER_SIZE - 1 ] = 0x00 ;

    if ( g_ctx.log_path[ 0 ] )
    {
        g_ctx.log_lock.lock();
        FILE *fp = fopen(g_ctx.log_path, "at");

        if ( fp )
        {
            fwrite(buff, sizeof(char), nIdx, fp);
            fclose(fp);
        }
        else
        {
            fwrite(buff, sizeof(char), nIdx, stderr);
        }

        g_ctx.log_lock.unlock();
    }
    else
        printf( "%s\n", buff ) ;

}