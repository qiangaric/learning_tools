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

    //������־
    auto log1= GETLOG("Test1");
    auto log2= GETLOG("Test1");
    //ԭʼ���÷�ʽ
    //SPDLOG_LOGGER_INFO(log1, "123");
    LOGGER_INFO(log2, "123");

    auto sw = LOGSW();
    // ��ʱ2��
    std::this_thread::sleep_for(std::chrono::seconds(2)); 
    INFO("Elapsed {0} {1}","ʱ��", sw);
    WARN("Elapsed {0} {1}", "ʱ��", sw);
    //ԭʼ���÷�ʽ
    //SPDLOG_INFO("TEST");
    INFO("TEST");
}
