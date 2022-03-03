#ifndef __LOG_H__
#define __LOG_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef L_PATH
#define L_PATH "./logs/"
#endif // L_PATH

// typedef struct Log {
//     FILE *fp;
//     struct tm *time;
// } Log;
//

#define CALLBACK_LIM 32

typedef struct {
    va_list ap;
    const char *fmt;
    const char *file;
    struct tm *time;
    void *udata;
    int line;
    int level;
} log_Event;

typedef void (*log_LogFn)(log_Event *ev);
typedef void (*log_LockFn)(bool lock, void *udata);

enum { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_FATAL };

#define log_trace(...) log_log(LOG_TRACE, __FILE__, __LINE__, __VA_ARGS__)
#define log_debug(...) log_log(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define log_info(...) log_log(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define log_warn(...) log_log(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define log_fatal(...) log_log(LOG_FATAL, __FILE__, __LINE__, __VA_ARGS__)

const char *log_level_string(int level);
void log_set_lock(log_LockFn fn, void *udata);
void log_set_level(int level);
void log_set_quiet(bool enable);
int log_add_callback(log_LogFn fn, void *udata, int level);
int log_add_fp(FILE *fp, int level);

void log_log(int level, const char *file, int line, const char *fmt, ...);

// // Log level formated str's.
// #ifndef L_ERR
// #define L_ERR "|ERROR|\t"   // Error reports.
// #define L_WARN "|WARN |\t"  // Warning messages.
// #define L_INFO "|INFO |\t"  // General info reported.
// #define L_CMMND "|CMMND|\t" // Commands executed in runtime.
// #define L_SUCMD "|SUCMD|\t" // As super user.
// #define L_FATAL "|FATAL|\t" // Exiting errors reported.
// #define L_PANIC "|PANIC|\t" // When a FATAL log is not reported, logged
// latter. #define L_DEBUG "|DEBUG|\t" // Used for development, need callbacks
// btw. #define L_TEST "|TEST |\t"  // Production tests. #define L_TRACE
// "|TRACE|\t" // Detailed steps of an operation. #endif                      //
// L_ERR // log to files.
//
// // ANSI terminal color codes.
// #ifndef LC_E
// #define LC_E "\033[91m|ERROR|\t"
// #define LC_F "\033[91m|FATAL|\t"
// #define LC_W "\033[93m|WARN |\t"
// #define LC_WR "\033[91m|WARN |\t"
// #define LC_I "\033[92m|INFO |\t"
// #define LC_R "\033[0m" // Reset color codes.
// #endif                 // LC_E

// void log_to_file(const char *str);
// void log_errno_to_file(const uint8_t err);
//
// #ifndef LOG_ERR
// #define LOG_ERRNO(ERRNO) \
//     fprintf(stderr, LC_E "%d : %s!\n" LC_R, ERRNO, strerror(ERRNO)); \
//     log_errno_to_file(ERRNO);
//
// // Doesn't log to file.
// #define LOG_ERR(STR) fprintf(stderr, LC_E "%s" LC_R "\n", STR)
//
// #define LOGF_ERR(STR) \
//     fprintf(stderr, LC_E "%s" LC_R "\n", STR); \ log_to_file(L_ERR STR);
// #endif // LOG_ERR
//
// #ifndef LOG_INFO
// #define LOG_INFO(STR) \
//     printf(LC_I "%s" LC_R "\n", STR); \ log_to_file(L_INFO STR)
//
// #define LOG_INFO_NW(STR) printf(LC_I "%s" LC_R "\n", STR);
//
// //! TODO
// #endif // LOG_INFO
//
// #ifndef LOG_WARN
// #define LOG_WARN(STR) \
//     printf(LC_W "%s" LC_R "\n", STR); \ log_to_file(L_WARN STR);
//
// #define LOG_WARN_R(STR) \
//     printf(LC_WR "%s" LC_R "\n", STR); \ log_to_file(L_WARN STR);
//
// //! TODO
// #endif // LOG_WARN
//
// #ifndef LOG_FATAL
// #define LOG_ERRNO_EXIT(ERRNO) \
//     log_errno_to_file(ERRNO); \
//     fprintf(stderr, LC_FATAL "exit(%d) : %s!" LC_RESET, ERRNO, \
//             strerror(ERRNO)); \
//     exit(ERRNO);
//
// #define LOG_FATAL(STR, ERRNO) \
//     LOG_ERR(STR); \ LOG_ERRNO_EXIT(ERRNO)
// #endif // LOG_FATAL

#endif // __LOG_H__
