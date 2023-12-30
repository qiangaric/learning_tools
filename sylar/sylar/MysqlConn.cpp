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

// �ͷ����ݿ�����
MysqlConn::~MysqlConn()
{
    if (m_conn != nullptr)
    {
        mysql_close(m_conn);
    }
    freeResult();
}

// �������ݿ�
bool MysqlConn::connect(string user, string passwd, string dbName, string ip, unsigned short port = 3306)
{
    // �����������������ϵ�MySQL���ݿ����潨������
    MYSQL *ptr = mysql_real_connect(m_conn, ip.c_str(), user.c_str(), passwd.c_str(), dbName.c_str(), port, nullptr, 0);
    return ptr != nullptr;
}

// �������ݿ⣺���� insert update delete ����
bool MysqlConn::update(string sql)
{
    if (mysql_query(m_conn, sql.c_str()))
    {
        return false;
    }
    return true;
}

// ��ѯ���ݿ�
bool MysqlConn::query(string sql)
{
    // ��ѯǰȷ�������Ϊ��
    freeResult();
    if (mysql_query(m_conn, sql.c_str()))
    {
        return false;
    }
    // ��������(����һ������ָ��)
    m_result = mysql_store_result(m_conn);
    return true;
}

// ������ѯ�õ��Ľ����
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

// �õ�������е��ֶ�ֵ
std::string MysqlConn::value(int index)
{
    int rowCount = mysql_num_fields(m_result);
    if (index >= rowCount || index < 0)
    {
        // ��ȡ�ֶ��������Ϸ������ؿ��ַ���
        return std::string();
    }
    // ���ǵ�����Ŀ����Ƕ������ַ��������к���'\0'
    // ��ô�����޷���������ַ����������Ҫ��ȡ�ַ���ͷָ����ַ�������
    char *val = m_row[index];
    unsigned long length = mysql_fetch_lengths(m_result)[index];
    return std::string(val, length);
}

// �������
bool MysqlConn::transaction()
{
    // true  �Զ��ύ
    // false �ֶ��ύ
    return mysql_autocommit(m_conn, false);
}

// �ύ����
bool MysqlConn::commit()
{
    return mysql_commit(m_conn);
}

// ����ع�
bool MysqlConn::rollback()
{
    return mysql_rollback(m_conn);
}

// �ͷŽ����
void MysqlConn::freeResult()
{
    if (m_result)
    {
        mysql_free_result(m_result);
        m_result = nullptr;
    }
}