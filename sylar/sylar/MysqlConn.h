#pragma once
#include <iostream>
#include
using namespace std;
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-28 10:30:10
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-28 10:34:53
 */

class MysqlConn
{
private:
    MYSQL *m_conn = nullptr;

public:
    // 初始化数据库连接
    MysqlConn();
    // 释放数据库函数
    ~MysqlConn();
    // 连接数据库
    bool connect(string user, string passwd, string dbName, string ip, unsigned short port = 3306);
    // 更新数据库
    bool update(string sql);
    // 查询数据库
    bool query(string sql);

    // 遍历查询得到的结果集
    bool next(string sql);
    // 得到结果集中的字段值
    string value(int index);

    // 事务操作
    bool transaction();
    // 提交事务
    bool commit();
    // 事务回滚
    bool rollback();
};