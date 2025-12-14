#include <stdio.h>
#include <stdlib.h>

#include "log.h"

void logMsg(char *msg) {

    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    FILE *fp = fopen("log.txt", "a");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "%d-%02d-%02d %02d:%02d:%02d - %s\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, msg);

    fclose(fp);
}