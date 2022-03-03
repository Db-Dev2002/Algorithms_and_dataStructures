#include "log.h"

// void log_to_file(const char *str) {
//     time_t t = time(NULL);
//     struct tm *tm = localtime(&t);
//     char filename[40];
//
//     sprintf(filename, L_PATH "%.2d-%.2d-%.2d.log", tm->tm_mday, tm->tm_mon +
//     1,
//             tm->tm_year - 100);
//
//     FILE *fp = fopen(filename, "a");
//     if (ferror(fp)) {
//         return;
//     }
//     fprintf(fp, "%.2d-%.2d-%.2d %.2d:%.2d:%.2d\t%s\n", tm->tm_mday,
//             tm->tm_mon + 1, tm->tm_year - 100, tm->tm_hour, tm->tm_min,
//             tm->tm_sec, str);
//     fclose(fp);
// }
//
// void log_errno_to_file(const uint8_t err) {
//     time_t t = time(NULL);
//     struct tm *tm = localtime(&t);
//     char filename[40];
//
//     sprintf(filename, L_PATH "%.2d-%.2d-%.2d.log", tm->tm_mday, tm->tm_mon +
//     1,
//             tm->tm_year - 100);
//
//     FILE *fp = fopen(filename, "a");
//     if (ferror(fp)) {
//         return;
//     }
//     fprintf(fp, "%.2d-%.2d-%.2d %.2d:%.2d:%.2d\t" L_FATAL "%s\n",
//     tm->tm_mday,
//             tm->tm_mon + 1, tm->tm_year - 100, tm->tm_hour, tm->tm_min,
//             tm->tm_sec, strerror(err));
//     fclose(fp);
// }

void print_trace() {
    //
}

static int file_exist(const char *filename) {
    FILE *fp;

    if ((fp = fopen(filename, "r")) == NULL) {
        return 0;
    } else {
        fclose(fp);
        return 1;
    }
}

typedef struct {
    log_LogFn fn;
    void *udata;
    int level;
} Callback;

static struct {
    void *data;
    log_LockFn lock;
    uint8_t level;
    uint8_t silenced;
    Callback callbacks[CALLBACK_LIM];
} Log;

static const char *level_strings[] = {"TRACE", "DEBUG", "INFO",
                                      "WARN",  "ERROR", "FATAL"};

#ifdef TERMINAL_COLORS
static const char *level_colors[] = {"\x1b[94m", "\x1b[36m", "\x1b[32m",
                                     "\x1b[33m", "\x1b[31m", "\x1b[35m"};
#endif
