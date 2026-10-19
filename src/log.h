#pragma once
#include <stdio.h>
#include <stdarg.h>

#define ERROR 2
#define WARNING 1
#define INFO 0
#define LOG_LEVEL INFO

// 0-> Info , 1-> Warning 2-> ERROR
void LOG(const int log_level,const char * str, ...){

    if (log_level < LOG_LEVEL){
        return ;
    }
    switch (log_level)
    {
    case INFO:
        printf("%-12s", "Info:");
        break;
    case WARNING:
        printf("%-12s", "Warning:");
        break;
    case ERROR:
        printf("%-12s", "**ERROR**:");

        break;
    default:
        break;
    }
    va_list args;
    va_start(args,str);
    vprintf(str,args);
    va_end(args);
    printf("\n");
}
