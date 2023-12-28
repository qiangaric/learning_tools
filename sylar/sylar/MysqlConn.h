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
    // ��ʼ�����ݿ�����
    MysqlConn();
    // �ͷ����ݿ⺯��
    ~MysqlConn();
    // �������ݿ�
    bool connect(string user, string passwd, string dbName, string ip, unsigned short port = 3306);
    // �������ݿ�
    bool update(string sql);
    // ��ѯ���ݿ�
    bool query(string sql);

    // ������ѯ�õ��Ľ����
    bool next(string sql);
    // �õ�������е��ֶ�ֵ
    string value(int index);

    // �������
    bool transaction();
    // �ύ����
    bool commit();
    // ����ع�
    bool rollback();
};