#ifndef __LOG_H__
#define __LOG_H__
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef L_PATH
#define L_PATH "./logs/"
#endif // L_PATH

typedef struct Log { // never constructed, no time! \:
    FILE *fp;        // we wanted the file opened while the program is running.
    struct tm *time;
} Log;

#ifndef L_ERR
#define L_ERR "|ERROR|\t"   // error reports
#define L_WARN "|WARN |\t"  // warning messages
#define L_INFO "|INFO |\t"  // general info reported
#define L_CMMND "|CMMND|\t" // commands executed in runtime
#define L_SUCMD "|SUCMD|\t" // as super user
#define L_FATAL "|FATAL|\t" // exiting errors reported
#define L_PANIC "|PANIC|\t" // when a FATAL log is not reported, logged latter
#define L_DEBUG "|DEBUG|\t" // used for development, need callback functions btw
#define L_TEST "|TEST |\t"  // production tests
#define L_TRACE "|TRACE|\t" // detailed steps of an operation
#endif                      // L_ERR // log to files

#ifndef LC_ERR
#define LC_ERR "\033[91m|ERROR|\t"
#define LC_FATAL "\033[91m|FATAL|\t"
#define LC_WARN "\033[93m|WARN |\t"
#define LC_WARN_R "\033[91m|WARN |\t"
#define LC_INFO "\033[92m|INFO |\t"
#define LC_RESET "\033[0m"
#endif // LC_ERR // log to terminal

void log_to_file(const char *str);
void log_errno_to_file(const uint8_t err);

#ifndef LOG_ERR
#define LOG_ERRNO(ERRNO)                                                       \
    fprintf(stderr, LC_ERR "%d : %s!\n" LC_RESET, ERRNO, strerror(ERRNO));     \
    log_errno_to_file(ERRNO);

// doesn't log to file
#define LOG_ERR(STR) fprintf(stderr, LC_ERR "%s" LC_RESET "\n", STR)

#define LOGF_ERR(STR)                                                          \
    fprintf(stderr, LC_ERR "%s" LC_RESET "\n", STR);                           \
    log_to_file(L_ERR STR);
#endif // LOR_ERR

#ifndef LOG_INFO
#define LOG_INFO(STR)                                                          \
    printf(LC_INFO "%s" LC_RESET "\n", STR);                                   \
    log_to_file(L_INFO STR)
#define LOG_INFO_NW(STR)                                                       \
    printf(LC_INFO "%s" LC_RESET "\n", STR);                                   \
//! TODO
#endif // LOG_INFO

#ifndef LOG_WARN
#define LOG_WARN(STR)                                                          \
    printf(LC_WARN "%s" LC_RESET "\n", STR);                                   \
    log_to_file(L_WARN STR);

#define LOG_WARN_R(STR)                                                        \
    printf(LC_WARN_R "%s" LC_RESET "\n", STR);                                 \
    log_to_file(L_WARN STR);
//! TODO
#endif // LOG_WARN

#ifndef LOG_FATAL
#define LOG_ERRNO_EXIT(ERRNO)                                                  \
    log_errno_to_file(ERRNO);                                                  \
    fprintf(stderr, LC_FATAL "exit(%d) : %s!" LC_RESET, ERRNO,                 \
            strerror(ERRNO));                                                  \
    exit(ERRNO);

#define LOG_FATAL(STR, ERRNO)                                                  \
    LOG_ERR(STR);                                                              \
    LOG_ERRNO_EXIT(ERRNO)
#endif // LOG_FATAL

#endif // __LOG_H__
