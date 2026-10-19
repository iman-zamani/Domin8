#pragma once
#include <stdio.h>
#include <stdarg.h>

#define ERROR 2
#define WARNING 1
#define INFO 0
#define LOG_LEVEL INFO

// 0-> Info , 1-> Warning 2-> ERROR
void LOG(const int log_level,const char * str, ...);
