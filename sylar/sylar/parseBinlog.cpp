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

// MySQL Binlog Event 结构定义
struct BinlogEvent
{
    uint8_t header[19]; // Binlog Event 头部
    // 其他可能的字段，根据实际需求添加
};

// MySQL Write Rows Event 结构定义
struct WriteRowsEvent
{
    uint8_t header[19]; // Event 头部
    // 其他可能的字段，根据实际需求添加
    uint64_t tableId;
    // 其他可能的字段，根据实际需求添加
    char sqlStatement[1000]; // 假设 SQL 语句最大长度为 1000 字符
};

// MySQL Update Rows Event 结构定义
struct UpdateRowsEvent
{
    uint8_t header[19]; // Event 头部
    // 其他可能的字段，根据实际需求添加
    uint64_t tableId;
    // 其他可能的字段，根据实际需求添加
    char sqlStatement[1000]; // 假设 SQL 语句最大长度为 1000 字符
};

// MySQL Delete Rows Event 结构定义
struct DeleteRowsEvent
{
    uint8_t header[19]; // Event 头部
    // 其他可能的字段，根据实际需求添加
    uint64_t tableId;
    // 其他可能的字段，根据实际需求添加
    char sqlStatement[1000]; // 假设 SQL 语句最大长度为 1000 字符
};

int main()
{
    // 请替换为实际的 binlog 文件路径
    std::cout << "begin to open binlog file" << std::endl;
    std::string binlogFilePath = "/pgdata/binlog/mysql-bin.000031";
    std::cout << "alrady  open binlog file" << std::endl;

    // 打开二进制文件
    std::ifstream binlogFile(binlogFilePath, std::ios::binary);

    if (!binlogFile.is_open())
    {
        std::cout << "Failed to open binlog file" << std::endl;
        std::cerr << "Failed to open binlog file" << std::endl;
        return -1;
    }
    std::cout << "test to open binlog file" << std::endl;

    // 读取文件内容到缓冲区
    binlogFile.seekg(0, std::ios::end);
    std::streampos fileSize = binlogFile.tellg();
    binlogFile.seekg(0, std::ios::beg);

    std::vector<char> buffer(fileSize);
    binlogFile.read(buffer.data(), fileSize);

    binlogFile.close();

    // 解析二进制数据，处理 binlog 事件
    // 具体的解析逻辑取决于 binlog 格式和事件类型

    // 示例：解析 Binlog Event
    std::cout << "test to open binlog file___________" << std::endl;
    for (size_t i = 0; i < fileSize;)
    {
        BinlogEvent *binlogEvent = reinterpret_cast<BinlogEvent *>(&buffer[i]);
        std::cout << "test to open binlog file----******" << std::endl;
        // 根据事件类型判断是何种事件
        uint8_t eventType = binlogEvent->header[4];
        if (eventType == 0x1e)
        { // Write Rows Event
            WriteRowsEvent *writeEvent = reinterpret_cast<WriteRowsEvent *>(binlogEvent);
            // 处理 Insert 事件
            std::cout << "Insert SQL Statement: " << writeEvent->sqlStatement << std::endl;
            std::cout << "test to open binlog file----*****werwerwer*" << std::endl;
        }
        else if (eventType == 0x15)
        { // Update Rows Event
            UpdateRowsEvent *updateEvent = reinterpret_cast<UpdateRowsEvent *>(binlogEvent);
            // 处理 Update 事件
            std::cout << "Update SQL Statement: " << updateEvent->sqlStatement << std::endl;
        }
        else if (eventType == 0x1d)
        { // Delete Rows Event
            DeleteRowsEvent *deleteEvent = reinterpret_cast<DeleteRowsEvent *>(binlogEvent);
            // 处理 Delete 事件
            std::cout << "Delete SQL Statement: " << deleteEvent->sqlStatement << std::endl;
        }

        // 计算下一个事件的位置
        i += binlogEvent->header[0] + (binlogEvent->header[1] << 8) + (binlogEvent->header[2] << 16);
    }

    return 0;
}
