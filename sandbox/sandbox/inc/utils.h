#ifndef SB_LAUNCHER_UTILS_H
#define SB_LAUNCHER_UTILS_H

char *rstrip(char *str, const char *chars = "\r\n\t ");
char *lstrip(char *str, const char *chars = "\r\n\t ");

////////////////////////////////////////////
#define BZERO_ARR(var) do { memset((var), 0x00, sizeof(var) / sizeof( (var)[0] ) ) ; } while (0)

#endif //SB_LAUNCHER_UTILS_H
