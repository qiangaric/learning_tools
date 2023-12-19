#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <stdint.h>
#include <cstdint>
#include <stdio.h>
#include <stdlib.h>

// using std::uint8_t;
// using namespace  std;

/*
 * @Descripttion:
 * @version:
 * @Author: Gao
 * @Date: 2023-12-11 10:40:58
 * @LastEditors: sch
 * @LastEditTime: 2023-12-11 13:32:11
 */

// MySQL Binlog Event �ṹ����
struct BinlogEvent
{
    uint8_t header[19]; // Binlog Event ͷ��
    // �������ܵ��ֶΣ�����ʵ���������
};

// MySQL Write Rows Event �ṹ����
struct WriteRowsEvent
{
    uint8_t header[19]; // Event ͷ��
    // �������ܵ��ֶΣ�����ʵ���������
    uint64_t tableId;
    // �������ܵ��ֶΣ�����ʵ���������
    char sqlStatement[1000]; // ���� SQL �����󳤶�Ϊ 1000 �ַ�
};

// MySQL Update Rows Event �ṹ����
struct UpdateRowsEvent
{
    uint8_t header[19]; // Event ͷ��
    // �������ܵ��ֶΣ�����ʵ���������
    uint64_t tableId;
    // �������ܵ��ֶΣ�����ʵ���������
    char sqlStatement[1000]; // ���� SQL �����󳤶�Ϊ 1000 �ַ�
};

// MySQL Delete Rows Event �ṹ����
struct DeleteRowsEvent
{
    uint8_t header[19]; // Event ͷ��
    // �������ܵ��ֶΣ�����ʵ���������
    uint64_t tableId;
    // �������ܵ��ֶΣ�����ʵ���������
    char sqlStatement[1000]; // ���� SQL �����󳤶�Ϊ 1000 �ַ�
};

int main()
{
    // ���滻Ϊʵ�ʵ� binlog �ļ�·��
    std::cout << "begin to open binlog file" << std::endl;
    std::string binlogFilePath = "/pgdata/binlog/mysql-bin.000031";
    std::cout << "alrady  open binlog file" << std::endl;

    // �򿪶������ļ�
    std::ifstream binlogFile(binlogFilePath, std::ios::binary);

    if (!binlogFile.is_open())
    {
        std::cout << "Failed to open binlog file" << std::endl;
        std::cerr << "Failed to open binlog file" << std::endl;
        return -1;
    }
    std::cout << "test to open binlog file" << std::endl;

    // ��ȡ�ļ����ݵ�������
    binlogFile.seekg(0, std::ios::end);
    std::streampos fileSize = binlogFile.tellg();
    binlogFile.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    binlogFile.read(buffer.data(), fileSize);

    binlogFile.close();

    // �������������ݣ����� binlog �¼�
    // ����Ľ����߼�ȡ���� binlog ��ʽ���¼�����

    // ʾ�������� Binlog Event
    std::cout << "test to open binlog file___________" << std::endl;
    for (size_t i = 0; i < fileSize;)
    {
        BinlogEvent *binlogEvent = reinterpret_cast<BinlogEvent *>(&buffer[i]);
        std::cout << "test to open binlog file----******" << std::endl;
        // �����¼������ж��Ǻ����¼�
        uint8_t eventType = binlogEvent->header[4];
        if (eventType == 0x1e)
        { // Write Rows Event
            WriteRowsEvent *writeEvent = reinterpret_cast<WriteRowsEvent *>(binlogEvent);
            // ���� Insert �¼�
            std::cout << "Insert SQL Statement: " << writeEvent->sqlStatement << std::endl;
            std::cout << "test to open binlog file----*****werwerwer*" << std::endl;
        }
        else if (eventType == 0x15)
        { // Update Rows Event
            UpdateRowsEvent *updateEvent = reinterpret_cast<UpdateRowsEvent *>(binlogEvent);
            // ���� Update �¼�
            std::cout << "Update SQL Statement: " << updateEvent->sqlStatement << std::endl;
        }
        else if (eventType == 0x1d)
        { // Delete Rows Event
            DeleteRowsEvent *deleteEvent = reinterpret_cast<DeleteRowsEvent *>(binlogEvent);
            // ���� Delete �¼�
            std::cout << "Delete SQL Statement: " << deleteEvent->sqlStatement << std::endl;
        }

        // ������һ���¼���λ��
        i += binlogEvent->header[0] + (binlogEvent->header[1] << 8) + (binlogEvent->header[2] << 16);
    }

    return 0;
}
