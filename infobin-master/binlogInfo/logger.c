#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "logger.h"

#ifndef LOGLEVEL
#define LOGLEVEL DEBUG
#endif

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2024-01-11 17:39:00
 * @LastEditors: Gao
 * @LastEditTime: 2024-01-11 17:39:01
 */
/**
��־��ӡʾ����
ʹ�ã�
Log(DEBUG, "This is debug info\n");
�����
[2018-07-22 23:37:27:172] [DEBUG] [main.cpp:5] This is debug info
Ĭ�ϴ�ӡ��ǰʱ�䣨��ȷ�����룩���ļ����ơ��кš�
*/

// ʹ����GNU C��չ�﷨��ֻ��gcc��C���ԣ���Ч��
// g++��c++�汾���벻ͨ��
static const char *s_loginfo[] = {
    [ERROR] = "ERROR",
    [WARN] = "WARN",
    [INFO] = "INFO",
    [DEBUG] = "DEBUG",
};

static void get_timestamp(char *buffer)
{
    time_t t;
    struct tm *p;
    struct timeval tv;
    int len;
    int millsec;

    t = time(NULL);
    p = localtime(&t);

    gettimeofday(&tv, NULL);
    millsec = (int)(tv.tv_usec / 1000);

    /* ʱ���ʽ��[2011-11-15 12:47:34:888] */
    len = snprintf(buffer, 32, "[%04d-%02d-%02d %02d:%02d:%02d:%03d] ",
                   p->tm_year + 1900, p->tm_mon + 1,
                   p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, millsec);

    buffer[len] = '\0';
}

void mylog1(const char *filename, int line, enum LogLevel level, const char *fmt, ...)
{
    if (level > LOGLEVEL)
        return;

    va_list arg_list;
    char buf[1024];
    memset(buf, 0, 1024);
    va_start(arg_list, fmt);
    vsnprintf(buf, 1024, fmt, arg_list);
    char time[32] = {0};

    // ȥ��*����*���ڵ�Ŀ¼·����ֻ�����ļ���
    const char *tmp = strrchr(filename, '/');
    if (!tmp)
        tmp = filename;
    else
        tmp++;
    get_timestamp(time);

    switch (level)
    {
    case DEBUG:
        // ��ɫ
        printf("\033[1;32m%s[%s] [%s:%d] %s\n\033[0m", time, s_loginfo[level], tmp, line, buf);
        break;
    case INFO:
        // ��ɫ
        printf("\033[1;34m%s[%s] [%s:%d] %s\n\033[0m", time, s_loginfo[level], tmp, line, buf);
        break;
    case ERROR:
        // ��ɫ
        printf("\033[1;31m%s[%s] [%s:%d] %s\n\033[0m", time, s_loginfo[level], tmp, line, buf);
        break;
    case WARN:
        // ��ɫ
        printf("\033[1;33m%s[%s] [%s:%d] %s\n\033[0m", time, s_loginfo[level], tmp, line, buf);
        break;
    }
    va_end(arg_list);
}