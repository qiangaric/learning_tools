#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/daily_file_sink.h"
#include "spdlog/stopwatch.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/callback_sink.h"
#include <iostream>

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2024-01-10 16:55:18
 * @LastEditors: Gao
 * @LastEditTime: 2024-01-10 16:55:19
 */

void init_spdlog()
{
    // �첽��־������8k����Ŀ��1����̨�̵߳Ķ���
    spdlog::init_thread_pool(8192, 1);
    // ��׼����̨���
    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    stdout_sink->set_level(spdlog::level::debug);
    // ��־�ļ������0��0�ִ�������־
    auto file_sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>("logs/log.txt", 0, 0);
    file_sink->set_level(spdlog::level::info);
    // ��־�ص�
    auto callback_sink = std::make_shared<spdlog::sinks::callback_sink_mt>([](const spdlog::details::log_msg &msg)
                                                                           {
                                                                               // ��־��¼������
                                                                               std::string name(msg.logger_name.data(), 0, msg.logger_name.size());
                                                                               // ��־��Ϣ
                                                                               std::string str(msg.payload.data(), 0, msg.payload.size());
                                                                               // ��־ʱ��
                                                                               std::time_t now_c = std::chrono::system_clock::to_time_t(msg.time);

                                                                               // �ص��Ĵ����߼��Լ�������Ŀ������壬����ʵʱ��ʾ��UI�����浽���ݿ�ȵ�

                                                                               //.... �ص������߼���ʾ��
                                                                               // std::tm localTime;
                                                                               // localtime_s(&localTime, &now_c);
                                                                               // char timeStr[50];
                                                                               // std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", &localTime);
                                                                               //// ��ȡ������
                                                                               // auto duration = msg.time.time_since_epoch();
                                                                               // auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count() % 1000;
                                                                               // std::cout << timeStr << "." << std::setfill('0') << std::setw(3) << milliseconds << " " ;
                                                                               // std::cout << to_string_view(msg.level).data() << " " << str << std::endl << std::endl << std::flush;
                                                                           });
    callback_sink->set_level(spdlog::level::info);

    std::vector<spdlog::sink_ptr> sinks{stdout_sink, file_sink, callback_sink};
    auto log = std::make_shared<spdlog::async_logger>("logger", sinks.begin(), sinks.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);

    // ������־��¼��������Ҫ�� %^ �� %$  ������Ҫ��ɫ�Ĳ���
    log->set_level(spdlog::level::trace);
    // ���ø�ʽ
    // �ο� https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
    //[%Y-%m-%d %H:%M:%S.%e] ʱ��
    //[%l] ��־����
    //[%t] �߳�
    //[%s] �ļ�
    //[%#] �к�
    //[%!] ����
    //[%v] ʵ���ı�
    log->set_pattern("[%Y-%m-%d %H:%M:%S.%e] %^[%l]%$ [%t] [%s %!:%#] %v");
    // ���õ����� err ������صĴ���ʱ����ˢ����־��  disk
    log->flush_on(spdlog::level::err);
    // 3��ˢ��һ�ζ���
    spdlog::flush_every(std::chrono::seconds(3));
    spdlog::set_default_logger(log);
}

// ������־��¼��
std::shared_ptr<spdlog::logger> get_async_file_logger(std::string name)
{
    auto log = spdlog::get(name);
    if (!log)
    {
        // ָ��Ϊ�գ��򴴽���־��¼����
        log = spdlog::daily_logger_mt<spdlog::async_factory>(name, "logs/" + name + "/log.txt");
        log->set_level(spdlog::level::trace);
        log->flush_on(spdlog::level::err);
        log->set_pattern("[%Y-%m-%d %H:%M:%S.%e] %^[%l]%$ [%t] [%s %!:%#] %v");
        // ��¼�����Զ�ע��ģ�����Ҫ�ֶ�ע��  spdlog::register_logger(name);
    }
    return log;
}

#define INITLOG() init_spdlog()

#define TRACE(...) SPDLOG_TRACE(__VA_ARGS__)
#define DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__)
#define INFO(...) SPDLOG_INFO(__VA_ARGS__)
#define WARN(...) SPDLOG_WARN(__VA_ARGS__)
#define ERROR(...) SPDLOG_ERROR(__VA_ARGS__)
#define CRITICAL(...) SPDLOG_CRITICAL(__VA_ARGS__)

// ������־�ļ�
#define GETLOG(LOG_NAME) get_async_file_logger(LOG_NAME)

#define LOGGER_TRACE(logger, ...) SPDLOG_LOGGER_TRACE(logger, __VA_ARGS__)
#define LOGGER_DEBUG(logger, ...) SPDLOG_LOGGER_DEBUG(logger, __VA_ARGS__)
#define LOGGER_INFO(logger, ...) SPDLOG_LOGGER_INFO(logger, __VA_ARGS__)
#define LOGGER_WARN(logger, ...) SPDLOG_LOGGER_WARN(logger, __VA_ARGS__)
#define LOGGER_ERROR(logger, ...) SPDLOG_LOGGER_ERROR(logger, __VA_ARGS__)
#define LOGGER_CRITICAL(logger, ...) SPDLOG_LOGGER_CRITICAL(logger, __VA_ARGS__)

// ʱ��ͳ�ƺ�
#define LOGSW() spdlog::stopwatch()
