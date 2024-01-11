/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2024-01-10 16:57:21
 * @LastEditors: Gao
 * @LastEditTime: 2024-01-10 16:57:22
 */


#include "log.h"
#include <thread>
#include <chrono>
#include <iostream>

int main()
{
    INITLOG("path");

    //单个日志
    auto log1= GETLOG("Test1");
    auto log2= GETLOG("Test1");
    //原始调用方式
    //SPDLOG_LOGGER_INFO(log1, "123");
    LOGGER_INFO(log2, "123");

    auto sw = LOGSW();
    // 延时2秒
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    INFO("Elapsed {0} {1}","时间", sw);
    WARN("Elapsed {0} {1}", "时间", sw);
    //原始调用方式
    //SPDLOG_INFO("TEST");
    INFO("TEST");
}
