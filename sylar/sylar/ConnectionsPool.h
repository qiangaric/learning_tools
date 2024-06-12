#pragma once
#include <queue>
#include <condition_variable>
#include <memory>
#include "MysqlConn.h"
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-28 15:31:05
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-28 16:10:25
 */

class ConnectionsPool
{
private:
    ConnectionPool();
    ConnectionPool(const ConnectionPool &obj) = delete;
    ConnectionPool(const ConnectionPool &&obj) = delete;
    ConnectionPool &operator=(const ConnectionPool &obj) = delete;

    bool parseJsonFile();
    void produceConnection();
    void recycleConnection();
    void addConnection();

    // TODO:加上文件路径
    // std::string filePath_;
    string m_ip;
    string m_user;
    string m_passwd;
    string m_dbName;
    unsigned short m_port;
    int m_minSize;
    int m_maxSize;
    int m_timeout;
    int m_maxIdleTime;
    queue<MysqlConn *> m_connectionQueue; // 连接池队列
    mutex m_mutex;
    condition_variable m_cond;

public:
    static ConnectionPool *getConnectionPool();
    std::shared_ptr<MysqlConn> getConnection();
    ~ConnectionPool();
};
