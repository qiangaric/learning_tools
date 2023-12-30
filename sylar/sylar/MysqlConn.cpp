#include <MysqlConn.h>
/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-28 10:32:38
 * @LastEditors: Gao
 * @LastEditTime: 2023-12-28 11:35:35
 */

MysqlConn::MysqlConn()
{
    m_conn = mysql_init(nullptr);
    mysql_set_character_set(m_conn, "utf8");
}

// 释放数据库连接
MysqlConn::~MysqlConn()
{
    if (m_conn != nullptr)
    {
        mysql_close(m_conn);
    }
    freeResult();
}

// 连接数据库
bool MysqlConn::connect(string user, string passwd, string dbName, string ip, unsigned short port = 3306)
{
    // 尝试与运行在主机上的MySQL数据库引擎建立连接
    MYSQL *ptr = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, nullptr, 0);
    return ptr != nullptr;
}

// 更新数据库：包括 insert update delete 操作
bool MysqlConn::update(string sql)
{
    if (mysql_query(m_conn, sql.c_str()))
    {
        return false;
    }
    return true;
}

// 查询数据库
bool MysqlConn::query(string sql)
{
    // 查询前确保结果集为空
    freeResult();
    if (mysql_query(m_conn, sql.c_str()))
    {
        return false;
    }
    // 储存结果集(这是一个二重指针)
    m_result = mysql_store_result(m_conn);
    return true;
}

// 遍历查询得到的结果集
bool MysqlConn::next()
{
    if (m_result != nullptr)
    {
        m_row = mysql_fetch_row(m_result);
        if (m_row != nullptr)
        {
            return true;
        }
    }
    return false;
}

// 得到结果集中的字段值
std::string MysqlConn::value(int index)
{
    int rowCount = mysql_num_fields(m_result);
    if (index >= rowCount || index < 0)
    {
        // 获取字段索引不合法，返回空字符串
        return std::string();
    }
    // 考虑到储存的可能是二进制字符串，其中含有'\0'
    // 那么我们无法获得完整字符串，因此需要获取字符串头指针和字符串长度
    char *val = m_row[index];
    unsigned long length = mysql_fetch_lengths(m_result)[index];
    return std::string(val, length);
}

// 事务操作
bool MysqlConn::transaction()
{
    // true  自动提交
    // false 手动提交
    return mysql_autocommit(m_conn, false);
}

// 提交事务
bool MysqlConn::commit()
{
    return mysql_commit(m_conn);
}

// 事务回滚
bool MysqlConn::rollback()
{
    return mysql_rollback(m_conn);
}

// 释放结果集
void MysqlConn::freeResult()
{
    if (m_result)
    {
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}