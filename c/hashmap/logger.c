#include "log.h"

void log_to_file(const char *str) {
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char filename[40];
  sprintf(filename, L_PATH "%.2d-%.2d-%.2d.log", tm->tm_mday, tm->tm_mon + 1,
          tm->tm_year - 100);
  FILE *fp = fopen(filename, "a");
  if (ferror(fp))
    return;
  fprintf(fp, "%.2d-%.2d-%.2d %.2d:%.2d:%.2d\t%s\n", tm->tm_mday,
          tm->tm_mon + 1, tm->tm_year - 100, tm->tm_hour, tm->tm_min,
          tm->tm_sec, str);
  fclose(fp);
}

void log_errno_to_file(const uint8_t err) {
  time_t t = time(NULL);
  struct tm *tm = localtime(&t);
  char filename[40];
  sprintf(filename, L_PATH "%.2d-%.2d-%.2d.log", tm->tm_mday, tm->tm_mon + 1,
          tm->tm_year - 100);
  FILE *fp = fopen(filename, "a");
  if (ferror(fp))
    return;
  fprintf(fp, "%.2d-%.2d-%.2d %.2d:%.2d:%.2d\t" L_FATAL "%s\n", tm->tm_mday,
          tm->tm_mon + 1, tm->tm_year - 100, tm->tm_hour, tm->tm_min,
          tm->tm_sec, strerror(err));
  fclose(fp);
}
