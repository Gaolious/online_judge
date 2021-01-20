#ifndef LOGTAG
#define LOGTAG "logger"
#endif

#ifndef SB_LAUNCHER_LOGGER_H
#define SB_LAUNCHER_LOGGER_H

enum LOG_LEVEL {
    INFO, DEBUG, WARN, ERROR
};

void log(
    LOG_LEVEL log_level, const char *log_tag, const char *filename, const char *function,
    const int line, const char *fmt, ...
);

#define LOGI(fmt, args...) log(LOG_LEVEL::INFO, LOGTAG, __FILE__, __FUNCTION__, __LINE__, fmt, ##args)
#define LOGD(fmt, args...) log(LOG_LEVEL::DEBUG, LOGTAG, __FILE__, __FUNCTION__, __LINE__, fmt, ##args)
#define LOGW(fmt, args...) log(LOG_LEVEL::WARN, LOGTAG, __FILE__, __FUNCTION__, __LINE__, fmt, ##args)
#define LOGE(fmt, args...) log(LOG_LEVEL::ERROR, LOGTAG, __FILE__, __FUNCTION__, __LINE__, fmt, ##args)

#define ENTER_FUNCTION() LOGI(">>> Enter Function")
#define LEAVE_FUNCTION() LOGI("<<< Leave Function")

#endif //SB_LAUNCHER_LOGGER_H
