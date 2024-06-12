#ifndef LOGGER_H_
#define LOGGER_H_

#ifdef __cplusplus
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2024-01-11 17:39:20
 * @LastEditors: Gao
 * @LastEditTime: 2024-01-11 17:40:57
 */

extern "C"
{
#endif

    enum LogLevel
    {
        ERROR = 1,
        WARN = 2,
        INFO = 3,
        DEBUG = 4,
    };

    void mylog1(const char *filename, int line, enum LogLevel level, const char *fmt, ...) __attribute__((format(printf, 4, 5)));

#define Log(level, format, ...) mylog1(__FILE__, __LINE__, level, format, ##__VA_ARGS__)

#ifdef __cplusplus
};
#endif

#endif