#ifndef __TEST_H__
#define __TEST_H__
//! Not used in production, move to src dir, call all_tests(), and compile
//! the project with -g flag, not the best approach to automated testing but
//! they're enough for now.

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _tstart puts("-----Starting tests!-----");

#define _tfail(STR) printf("!!!-TEST-FAILED--->%s\n", STR);
#define _tpass(STR) printf("!!!-TEST-PASSED--->%s\n", STR);

// benchmarks
#define _tbench_start(STR)                                                     \
    printf("!===STARTING BENCHS FOR %s ===!\n", STR);                          \
    float start_t = (float)clock() / CLOCKS_PER_SEC;

#define _tbench_stop                                                           \
    float end_t = (float)clock() / CLOCKS_PER_SEC;                             \
    float bench = end_t - start_t;

#define _tbench_print(STR) printf("!===BENCH FOR %s===>%fseg\n", STR, bench);

#define _assert_cn(TEST, MSG)                                                  \
    if (!TEST) {                                                               \
        LOG_ERR(MSG);                                                          \
        _tfail(MSG);                                                           \
    } else {                                                                   \
        _tpass(MSG);                                                           \
    }

// exits on failure
#define _assert(TEST, MSG)                                                     \
    if (!TEST) {                                                               \
        LOG_ERR(MSG);                                                          \
        _tfail(MSG);                                                           \
        exit(-1);                                                              \
    }                                                                          \
    _tpass(MSG);

#endif // __TEST_H__
