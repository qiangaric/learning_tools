#ifndef __SYLAR_THREAD_H__
#define __SYLAR_THREAD_H__
#include <thread>
#include <functional>

namespace sylar
{
    class Thread
    {
    private:
        Thread(const Thread &) = delete;
        Thread(const Thread &&) = delete;
        Thread &operator=(const Thread &) = delete;
    private:
        tid_t m_id;

    public:
        /// 线程智能指针类型
        typedef std::shared_ptr<Thread> ptr;
    };

} // namespace sylar

#endif