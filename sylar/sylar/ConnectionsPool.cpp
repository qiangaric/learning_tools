#include <fstream>
#include <thread>
#include <assert.h>
#include "ConnectionsPool.h"
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-28 16:11:27
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-29 13:16:18
 */

ConnectionPool *ConnectionPool::getConnectionPool()
{
    static ConnectionPool pool;
    return &pool;
}

ConnectionPool::ConnectionPool()
{
    // assert();
    // parseJsonFile();

    for (int i = 0; i < minSize_; ++i)
    {
        addConnection();
    }
    // �������߳�ִ������
    std::thread producer(&ConnectionPool::produceConnection, this);
    std::thread recycler(&ConnectionPool::recycleConnection, this);
    // �����̷߳��룬�������ڴ˴�
    producer.detach();
    recycler.detach();
}

ConnectionPool::~ConnectionPool()
{
    // �ͷŶ���������MySQL������Դ
    while (!connectionQueue_.empty())
    {
        MysqlConn *conn = connectionQueue_.front();
        connectionQueue_.pop();
        delete conn;
    }
}

// ����JSON�����ļ�
bool ConnectionPool::parseJsonFile()
{
    std::ifstream file("conf.json");
    json conf = json::parse(file);

    ip_ = conf["ip"];
    user_ = conf["userName"];
    passwd_ = conf["password"];
    dbName_ = conf["dbName"];
    port_ = conf["port"];
    minSize_ = conf["minSize"];
    maxSize_ = conf["maxSize"];
    timeout_ = conf["timeout"];
    maxIdleTime_ = conf["maxIdleTime"];
    return true;
}

void ConnectionPool::produceConnection()
{
    while (true)
    {
        // RALL�ַ���װ�Ļ���������ʼ��������������������
        std::unique_lock<std::mutex> locker(mutex_);
        while (connectionQueue_.size() >= minSize_)
        {
            cond_.wait(locker);
        }
        // �������������������ά�ֵ���С�����������Ǿ���Ҫ�����µ�����
        addConnection();
        // ���ѱ��������߳�
        cond_.notify_all();
    }
}

// ���ٶ�������ݿ�����
void ConnectionPool::recycleConnection()
{
    while (true)
    {
        // �����Ե�����⹤����ÿ500���루0.5s��ִ��һ��
        std::this_thread::sleep_for(std::chrono::microseconds(500));
        std::lock_guard<std::mutex> locker(mutex_);
        while (connectionQueue_.size() > minSize_)
        {
            MysqlConn *conn = connectionQueue_.front();
            if (conn->getAliveTime() >= maxIdleTime_)
            {
                // ����ʱ�䳬���趨ֵ������
                connectionQueue_.pop();
                delete conn;
            }
            else
            {
                // �����Ƚ��ȳ�˳��ǰ���û�г�������Ŀ϶�Ҳû��
                break;
            }
        }
    }
}

void ConnectionPool::addConnection()
{
    MysqlConn *conn = new MysqlConn;
    conn->connect(user_, passwd_, dbName_, ip_, port_);
    conn->refreshAliveTime();    // ˢ����ʼ�Ŀ���ʱ���
    connectionQueue_.push(conn); // ��¼������
}

// ��ȡ����
std::shared_ptr<MysqlConn> ConnectionPool::getConnection()
{
    std::unique_lock<std::mutex> locker(mutex_);
    while (connectionQueue_.empty())
    {
        // ���Ϊ�գ���Ҫ����һ��ʱ�䣬�ȴ��µĿ�������
        if (std::cv_status::timeout == cond_.wait_for(locker, std::chrono::milliseconds(timeout_)))
        {
            // std::cv_status::timeout ��ʾ��ʱ
            if (connectionQueue_.empty())
            {
                continue;
            }
        }
    }
    // �п��õ�����
    // ��λ������ݿ����ӣ�
    // ʹ�ù�������ָ�벢�涨��ɾ����
    // �涨���ٺ����ɾ�������ڻ��������¸��¿���ʱ�䲢�������ݿ����ӳ�
    std::shared_ptr<MysqlConn> connptr(connectionQueue_.front(),
                                       [this](MysqlConn *conn)
                                       {
                                           std::lock_guard<std::mutex> locker(mutex_);
                                           conn->refreshAliveTime();
                                           connectionQueue_.push(conn);
                                       });
    connectionQueue_.pop();
    cond_.notify_all();
    return connptr;
}