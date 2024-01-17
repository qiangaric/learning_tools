/*************************************************************************
  > File Name: main.c
  > Author: gaopeng QQ:22389860 all right reserved
  > Mail: gaopp_200217@163.com
  > Created Time: Thu 02 Mar 2017 08:51:54 PM CST
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "event_header.h"
#define LOG_USE_COLOR 1
#include "log.h"
#include "logger.h"

static MAP_TAB my_tab;
static QUERY_EVENT my_query;
static uint64_t GTID_GNO_;
static HEAD_P HEAD_PI;
static HEAD_P HEAD_TRX;
// add 2017 08 12 for lager time trx 存放长时间链表
static HEAD_P HEAD_MT;
// add 2017 9 27 for binlog for every table
static HEAD_P HEAD_TAB;

static int GT = 1;

// add  2018 07 02 for unkown error check!!

unsigned int FORCE = 0;

int check_asii_num(const char *num)
{
	int i;
	int ret = 0;

	for (i = 0; i < (int)strlen(num); i++)
	{
		if (*(num + i) < 0X30 || *(num + i) > 0x39)
		{
			ret = -1;
			break;
		}
	}
	if (ret == -1)
	{
		printf(" parameter must number type %s %d \n", ERR_POST);
		return ret;
	}

	return ret;
}

void test(void)
{
	;
}

int xfree(void *p)
{
	if (p == NULL)
	{
		return 0;
		printf("NULL mem free!\n");
	}
	free(p);
	p = NULL;
	return 0;
}

// 1: Big_endian
// 0: Little_endian
// 2: Unkown
int check_lit(void)
{
	char *test = NULL;
	short *m = NULL;

	test = (char *)calloc(2, 1);

	strcpy(test, "lb");
	m = (short *)test;

	if (*m == 0x626c)
	{
		// printf("Check is Little_endian\n");
		Log(INFO, "Check is Little_endian\n");
		return 0;
	}
	else if (*m == 0x6c62)
	{
		printf("Check is Big_endian\n");
		return 1;
	}
	else
	{
		printf("Check is Unkown\n");
		return 2;
	}
}

int check_bin_format(FILE *fd)
{
	int ret = 0;
	FILE *fds = NULL;
	char bin_maico[4];
	uint16_t binlog_format = 0;
	char mysql_format[51];
	uint32_t event_header_size = 0;
	int32_t *bin_maico_nu = NULL;
	uint16_t flags;
	uint64_t totalsize;

	// 前4字节魔数
	memset(bin_maico, 0, 4);
	memset(mysql_format, 0, 51);
	fds = fd;
	if (fd == NULL)
	{
		ret = 1;
		printf("check_bin_format == NULL? %s %d \n", ERR_POST);
		return ret;
	}
	/***
	 * size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
	 * 	ptr：指向要存储数据的内存块的指针。
	 * 	size：每个数据项的字节数。
	 *	count：要读取的数据项的数量。
	 *	stream：指向 FILE 对象的指针，它标识了要读取的文件。
	 */
	// 读取FDS前四字节 到bin_maico
	// Log(INFO,"");

	if (fread(bin_maico, BIN_LOG_HEADER_SIZE, O_MEM, fds) != O_MEM)
	{
		ret = 2;
		printf("check_bin_format fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	// Log(WARN, "bin_maico =  %s\n", *bin_maico);
	bin_maico_nu = (int32_t *)bin_maico;
	// Log(WARN, "bin_maico = %u", bin_maico);
	Log(WARN, "bin_maico_nu = %ld", *bin_maico_nu);
	// fseek(fds,LOG_EVENT_HEADER_LEN,SEEK_CUR);
	// add
	//
	// fseek 函数用于在文件中移动文件指针的位置
	// 向前移动17个字节
	// 获取移动后的当前位置
	long currentPosition = ftell(fds);
	Log(DEBUG, "Current position after fseek: %ld\n", currentPosition);

	fseek(fds, LOG_POS_OFFSET, SEEK_CUR);
	// 获取移动后的当前位置
	Log(DEBUG, "Current position after fseek: %ld\n", ftell(fds));
	// flag信息 19-17=2
	if (fread(&flags, FLAGS_OFFSET - LOG_POS_OFFSET, O_MEM, fds) != O_MEM)
	{
		ret = 20;
		printf("check_bin_format fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	Log(DEBUG, "Current position after fseek: %ld\n", ftell(fds));

	// end
	// binlog_format 版本信息 21-19=2字节
	if (fread(&binlog_format, FORMAT_V - FLAGS_OFFSET, O_MEM, fds) != O_MEM)
	{
		ret = 3;
		printf("check_bin_format fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	Log(DEBUG, "Current position after fseek: %ld\n", ftell(fds));

	// fseek(fds,1,SEEK_CUR);
	// 数据库版本信息 52-2=50字节
	if (fread(mysql_format, FED_MYSQL_FORMAT - FED_BINLOG_FORMAT, O_MEM, fds) != O_MEM)
	{
		ret = 4;
		printf("check_bin_format fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	Log(DEBUG, "Current position after fseek: %ld\n", ftell(fds));
	// 从当前位置推进（偏移）4字节
	fseek(fds, FED_USED - FED_MYSQL_FORMAT, SEEK_CUR);
	// 头长度 57-56
	if (fread(&event_header_size, FED_EVENT_HEADER - FED_USED, O_MEM, fds) != O_MEM)
	{
		ret = 5;
		printf("check_bin_format fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	Log(DEBUG, "Current position after fseek: %ld\n", ftell(fds));
	/**
	 * 什么是魔数
	 * 魔数通常是4个字节的值。在MySQL 5.6及更高版本中，魔数的十六进制表示为 fe 62 69 6e。
	 * 具体来说，这4个字节的十六进制值分别是 fe、62、69、6e，对应ASCII字符为 "þ"、"b"、"i"、"n"。因此，这个魔数通常被称为 "bin"。
	 * 16进制字符串对应关系  https://blog.csdn.net/u010033786/article/details/126275465
	 */
	if (*bin_maico_nu != BINLOG_MAICO)
	{
		ret = 6;
		printf("check_bin_format:not binlogfile? ERROR  %s %d \n", ERR_POST);
		return ret;
	}

	// 判断头长度是否是19字节 bin版本是否是4
	Log(DEBUG, "BINLOG_HEADER_LENGTH: %ld\n", BINLOG_HEADER_LENGTH, "BINLOG_VERSION = %d", BINLOG_VERSION);
	Log(DEBUG, "BINLOG_VERSION = %d", BINLOG_VERSION);
	if (event_header_size != BINLOG_HEADER_LENGTH || binlog_format != BINLOG_VERSION)
	{
		ret = 7;
		printf("check_bin_format:binlog_format not v4? ERROR %s %d \n", ERR_POST);
		return ret;
	}

	/*
		printf("%ld,%s,%ld\n",binlog_format,mysql_format,event_header_size);
		printf("%d\n",*bin_maico_nu);
		*/
	fseek(fds, 0, SEEK_END);
	totalsize = ftell(fds);
	Log(DEBUG, "binlog total size : %ld\n", ftell(fds));
	// 数据库版本
	// printf("Check Mysql Version is:%s\n", mysql_format);
	// printf("Check Mysql binlog format ver is:V%u\n", binlog_format);
	Log(INFO, "Check Mysql Version is:%s\n ", mysql_format);
	Log(INFO, "Check Mysql binlog format ver is:V%u", binlog_format);
	Log(INFO, "flags is:%u", flags);
	/**
	 * binlog flags：
	 * 	 1 为未关闭
	 * 	 0 关闭
	 */
	if (flags == (uint16_t)1)
	{
		// printf("Warning:Check This binlog is not closed!\n");
		Log(WARN, "Check This binlog is not closed!\n");
	}
	else
	{
		// printf("Check This binlog is closed!\n");
		Log(INFO, "Check This binlog is closed!\n");
	}
	// printf("Check This binlog total size:%lu(bytes)\n", totalsize);
	// printf("Note:load data infile not check!\n");
	Log(INFO, "Check This binlog total size:%lu(bytes)\n", totalsize);
	Log(INFO, "Note:load data infile not check!\n");
	return ret;
}

int gtid_an(unsigned char *gtid_buf)
{
	int i = 0;
	int ret = 0;
	uint64_t *gno = NULL;

	memset(&GTID_GNO_, 0, sizeof(uint64_t));

	if (gtid_buf == NULL)
	{
		ret = 1;
		printf("gtid_an:gtid_buf == NULL ? ERROR %s %d \n", ERR_POST);
		return ret;
	}
	if (GT)
	{
		printf("Gtid:");
	}
	for (i = 0; i < 16; i++)
	{
		if (i == 4)
		{
			if (GT)
			{
				printf("-");
			}
		}
		if (i == 6)
		{
			if (GT)
			{
				printf("-");
			}
		}
		if (i == 8)
		{
			if (GT)
			{
				printf("-");
			}
		}
		if (i == 10)
		{
			if (GT)
			{
				printf("-");
			}
		}
		if (GT)
		{
			printf("%x", gtid_buf[i + 1]);
		}
	}

	gno = (uint64_t *)(gtid_buf + 17);
	GTID_GNO_ = *gno;
	if (GT)
	{
		printf(":%lu", *gno);
	}
	return ret;
}

int gtid_com_an(unsigned char *gtid_co_seq)
{
	int ret = 0;
	uint64_t *data;

	if (gtid_co_seq == NULL)
	{
		ret = 1;
		printf("gtid_com_an:gtid_com_seq == NULL ? ERROR %s %d \n", ERR_POST);
		return ret;
	}

	data = (uint64_t *)gtid_co_seq;

	if (GT)
	{
		printf(" last_committed=%ld  sequence_number=%ld\n", *(data), *(data + 1));
	}

	return ret;
}

int map_an(FILE *fds)
{
	int ret = 0;
	uint8_t tab_id[6];
	uint8_t db_len = 0;
	uint8_t tab_len = 0;

	if (fds == NULL)
	{
		ret = 10;
		printf("map_an:fds == NULL? ERROR %s %d \n", ERR_POST);
		return ret;
	}
	memset(&my_tab, 0, sizeof(MAP_TAB));
	memset(tab_id, 0, 6);
	if (fread(tab_id, MAP_TABLE_ID, O_MEM, fds) != O_MEM)
	{
		ret = 1;
		printf("map_an:fread ERROR %s %d \n", ERR_POST);
		return ret;
	}

	memcpy(&my_tab.table_id, tab_id, 6);
	if (GT)
	{
		printf("TABLE_ID:%lu ", my_tab.table_id);
	}

	fseek(fds, MAP_UNSUED - MAP_TABLE_ID, SEEK_CUR);

	if (fread(&db_len, MAP_DB_LENGTH, O_MEM, fds) != O_MEM ||
		fread(my_tab.db_name, db_len, O_MEM, fds) != O_MEM)
	{
		ret = 2;
		printf("map_an:fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	if (GT)
	{
		printf("DB_NAME:%s ", my_tab.db_name);
	}
	fseek(fds, 1, SEEK_CUR); // 0X00

	if (fread(&tab_len, MAP_TABLE_LENGTH, O_MEM, fds) != O_MEM ||
		fread(my_tab.tab_name, tab_len, O_MEM, fds) != O_MEM)
	{
		ret = 3;
		printf("map_an:fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	if (GT)
	{
		printf("TABLE_NAME:%s Gno:%lu\n", my_tab.tab_name, GTID_GNO_);
	}
	return ret;
}

int dml_an(FILE *fds)
{
	int ret = 0;
	uint8_t tab_id[6];
	uint64_t table_id = 0;

	if (fds == NULL)
	{
		ret = 10;
		printf("dml_an:fds == NULL? ERROR %s %d \n", ERR_POST);
		return ret;
	}
	memset(tab_id, 0, 6);
	if (fread(tab_id, DML_TABLE_ID, O_MEM, fds) != O_MEM)
	{
		ret = 1;
		printf("dml_an:fread ERROR %s %d \n", ERR_POST);
		return ret;
	}

	memcpy(&table_id, tab_id, 6);

	if (table_id == my_tab.table_id)
	{
		if (GT)
		{
			printf("Dml on table: %s.%s  table_id:%lu Gno:%lu \n", my_tab.db_name, my_tab.tab_name, my_tab.table_id, GTID_GNO_);
		}
	}
	else
	{
		if (FORCE == 0)
		{
			ret = 2;
			printf("dml_an: table_id cmp ERROR %s %d \n", ERR_POST);
			return ret;
		}
	}

	return ret;
}

int query_an(FILE *fds, uint32_t event_size, uint32_t event_pos)
{
	int ret = 0;
	uint8_t db_len = 0;
	uint16_t meta_len = 0;
	uint32_t sta_len = 0;
	char sta[36];

	if (fds == NULL)
	{
		;
	}
	POS_T = 0; // global var to set 0 will check this event part is DML or DDL

	memset(&my_query, 0, sizeof(QUERY_EVENT));
	memset(sta, 0, 35);

	fseek(fds, QUERY_T_ID, SEEK_CUR); // skip thread_id 4 bytes
	// 执行时间
	if (fread(&my_query.exe_time, QUERY_EXE_T - QUERY_T_ID, O_MEM, fds) != O_MEM)
	{
		ret = 1;
		printf("query_an:fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	if (fread(&db_len, QUERY_DEFAULT_DB_LEN - QUERY_EXE_T, O_MEM, fds) != O_MEM)
	{
		ret = 2;
		printf("query_an:fread ERROR %s %d \n", ERR_POST);
		return ret;
	}
	// printf("%d\n",ftell(fds));
	fseek(fds, QUERY_ERR_CODE - QUERY_DEFAULT_DB_LEN, SEEK_CUR); // skip error_code
	// printf("%d\n",ftell(fds));

	// 可变数据的长度
	if (fread(&meta_len, QUERY_META_BLOCK_LEN - QUERY_ERR_CODE, O_MEM, fds) != O_MEM)
	{
		ret = 3;
		printf("query_an:fread ERROR %s %d \n", ERR_POST);
		return ret;
	}

	fseek(fds, meta_len, SEEK_CUR);
	if (db_len != 0)
	{
		if (fread(my_query.db_name, db_len, O_MEM, fds) != O_MEM)
		{
			ret = 4;
			printf("query_an:fread ERROR %s %d \n", ERR_POST);
			return ret;
		}
	}
	else
	{
		strcpy(my_query.db_name, "!<slave?nodbname>");
	}

	fseek(fds, O_MEM, SEEK_CUR);
	// SQL语句     本事件大小  19u头信息         query_event固定数据    可变数据长度  数据库名字长度 默认一个00字节 CRC校验值
	sta_len = event_size - LOG_EVENT_HEADER_LEN - QUERY_META_BLOCK_LEN - meta_len - db_len - O_MEM - CRC_LEN;

	if ((my_query.statment = (uint8_t *)calloc(O_MEM, sta_len + 5)) == NULL)
	{
		ret = 5;
		printf("query_an:calloc ERROR %s %d \n", ERR_POST);
		return ret;
	}

	if (fread(my_query.statment, sta_len, O_MEM, fds) != O_MEM)
	{
		ret = 6;
		printf("query_an:fread ERROR %s %d \n", ERR_POST);
		return ret;
	}

	strncpy(sta, my_query.statment, 35);
	// printf("db_len:%u meta len:%u  sta len: %u \n",db_len,meta_len,sta_len);
	Log(WARN, "db_len:%u meta len:%u  sta len: %u \n", db_len, meta_len, sta_len);
	if (GT)
	{
		printf("Exe_time:%u  Use_db:%s Statment(35b-trun):%s", my_query.exe_time, my_query.db_name, sta);
	}
	// add 2017 08 12
	EXE_T = my_query.exe_time;
	// Log(DEBUG, "事件开始pos点: %s", sta);
	// Log(DEBUG, "sta : %s", sta);
	// Log(DEBUG, "!strcmp(sta, BEGIN) : %u", !strcmp(sta, "BEGIN") || !strcmp(sta, "B"));
	if (!strcmp(sta, "BEGIN") || !strcmp(sta, "B"))

	//! strcmp(sta,"B") 5.5 only
	{
		Log(DEBUG, "sta : %s", sta);
		POS_T = (uint64_t)event_pos;
		Log(DEBUG, "事件开始pos点: %u", POS_T);

		if (GT)
		{
			printf(" /*!Trx begin!*/ Gno:%lu\n", GTID_GNO_);
		}
	}
	else
	{
		if (GT)
		{
			printf(" Gno:%lu\n", GTID_GNO_);
		}
	}

	xfree(my_query.statment);

	return ret;
}

int analyze_binlog(FILE *fd, uint32_t pi, uint64_t mi, uint32_t mt)
{

	int ret = 0;
	FILE *fds = NULL;
	uint32_t event_pos = 0;
	uint32_t event_time = 0;
	uint8_t event_type = 0;
	uint32_t event_next = 4;
	uint64_t max_file_size = 0;

	uint32_t event_size = 0;

	unsigned char gtid_buf[25];
	unsigned char gtid_co_seq[16];
	int n = 0;
	uint64_t node = 0;

	fds = fd;
	Log(DEBUG, "bengin to analysis log, current postion : %ld\n", ftell(fds));
	if (fds == NULL)
	{
		ret = 10;
		printf("analyze_binlog:fds == NULL? ERROR %s %d \n", ERR_POST);
		return ret;
	}
	// 初始化内存块
	memset(gtid_buf, 0, 25);
	memset(gtid_co_seq, 0, 16);
	memset(&HEAD_PI, 0, sizeof(HEAD_P));
	memset(&HEAD_TRX, 0, sizeof(HEAD_P));
	fseek(fds, OFFSET_0, SEEK_END);
	// 文件大小
	max_file_size = ftell(fds);
	MAX_FILE_Z = max_file_size;
	// Log(DEBUG, " max_file_size : %ld\n", max_file_size);
	// Log(DEBUG, " (uint64_t)pi : %ld\n", (uint64_t)pi);
	PI_SIZE = max_file_size / ((uint64_t)pi);

	fseek(fds, BIN_LOG_HEADER_SIZE, SEEK_SET);
	// Log(DEBUG, " current postion : %ld\n", ftell(fds));
	if (GT)
	{
		printf("------------Detail now--------------\n");
	}
	while ((max_file_size - (uint64_t)event_next) > LOG_EVENT_HEADER_LEN)
	{
		POS_E = 0; // init global var to 0 to check trx end normal?
		// Log(DEBUG, " 事件开始位置: %ld\n", ftell(fds));
		/**
		 * event_next 下一个事件位置，初始为4 （除去魔数）
		 */
		// 向前推进到事件开始位置
		fseek(fds, event_next, SEEK_SET);
		// Log(DEBUG, " current postion : %ld\n", ftell(fds));
		event_pos = ftell(fds);
		// Log(DEBUG, " 事件position点 : %ld\n", event_pos);
		test();
		if (fread(&event_time, EVENT_TIMESTAMP, O_MEM, fds) != O_MEM)
		{
			ret = 2;
			printf("analyze_binlog:fread ERROR %s %d \n", ERR_POST);
			return ret;
		}
		// Log(DEBUG, " current postion after event_time : %ld\n", ftell(fds));
		// 向前偏移1字节
		if (fread(&event_type, EVENT_TYPE_OFFSET - EVENT_TIMESTAMP, O_MEM, fds) != O_MEM)
		{
			ret = 3;
			printf("analyze_binlog:fread ERROR %s %d \n", ERR_POST);
			return ret;
		}
		// Log(DEBUG, " current postion after event_type : %ld\n", ftell(fds));
		// 向前偏移8字节
		fseek(fds, EVENT_LEN_OFFSET - EVENT_TYPE_OFFSET, SEEK_CUR);
		// Log(DEBUG, " current postion after server id : %ld\n", ftell(fds));

		// 下一个event 位置 :event_next
		if (fread(&event_next, LOG_POS_OFFSET - EVENT_LEN_OFFSET, O_MEM, fds) != O_MEM)
		{
			ret = 4;
			printf("analyze_binlog:fread ERROR %s %d \n", ERR_POST);
			return ret;
		}
		// Log(DEBUG, " current postion after event_next : %ld\n", ftell(fds));

		// Log(WARN, " 下一个事件的位置 : %ld\n", event_next);
		// Log(DEBUG, " 事件的Pos点 : %ld\n", event_pos);
		event_size = event_next - event_pos;
		// Log(DEBUG, " 当前事件的大小 : %ld\n", event_size);
		EVE_TOTAL++;
		printf("---------------事件分割线--------------- \n");
		Log(ERROR, " 第  %ld 个事件", EVE_TOTAL);
		// Log(DEBUG, " event_size : %ld\n", event_size);
		// Log(DEBUG, " MAX_EVE : %ld\n", MAX_EVE);
		// 获取最大事件以及pos点
		if (event_size > MAX_EVE) // get max event info
		{
			MAX_EVE = (uint64_t)event_size;
			MAX_EVE_P = (uint64_t)event_pos;
		}

		if (event_pos > PI_SIZE * n)
		{
			POS_TIME = event_time;

			if (init_chain(PI_SIZE, (uint64_t)POS_TIME, &HEAD_PI) != 0) // add import
			{
				ret = 31;
				printf("analyze_binlog:call init_chain  ERROR %s %d \n", ERR_POST);
				return ret;
			}
			n++;
		}
		// Log(WARN, "测试-------------------------------------------%lu", n);

		// 小于19字节，结束
		if ((max_file_size - (uint64_t)event_next) < LOG_EVENT_HEADER_LEN) // add
		{
			END_TIME = event_time;
		}
		Log(WARN, " 当前事件的POS点 : %ld", ftell(fds));
		Log(WARN, " 下一个事件的位置 : %ld", event_next);
		Log(WARN, "事件类型: %lu", event_type);
		switch (event_type)
		{
		case 30:
			if (GT)
			{
				printf("------>Insert Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			fseek(fds, FLAGS_OFFSET - LOG_POS_OFFSET, SEEK_CUR);
			if (dml_an(fds) != 0)
			{
				ret = 8;
				printf("analyze_binlog:dml_an ERROR %s %d \n", ERR_POST);
				return ret;
			}

			if (add_chain_op(my_tab.db_name, my_tab.tab_name, (uint64_t)(event_next - event_pos), 0, 0, 1, 0, 0, &HEAD_TAB) != 0)
			{
				ret = 8;
				printf("add_chain_op() ERROR%s %d \n", ERR_POST);
				return ret;
			}

			break;
		case 31:
			if (GT)
			{
				printf("------>Update Event:Pos:%u(0X%x) N_pos is:%u(0X%x) time:%u event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			fseek(fds, FLAGS_OFFSET - LOG_POS_OFFSET, SEEK_CUR);
			if (dml_an(fds) != 0)
			{
				ret = 9;
				printf("analyze_binlog:dml_an ERROR %s %d \n", ERR_POST);
				return ret;
			}
			if (add_chain_op(my_tab.db_name, my_tab.tab_name, 0, (uint64_t)(event_next - event_pos), 0, 0, 1, 0, &HEAD_TAB) != 0)
			{
				ret = 8;
				printf("add_chain_op() ERROR%s %d \n", ERR_POST);
				return ret;
			}
			break;
		case 32:
			if (GT)
			{
				printf("------>Delete Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			fseek(fds, FLAGS_OFFSET - LOG_POS_OFFSET, SEEK_CUR);
			if (dml_an(fds) != 0)
			{
				ret = 10;
				printf("analyze_binlog:dml_an ERROR %s %d \n", ERR_POST);
				return ret;
			}
			if (add_chain_op(my_tab.db_name, my_tab.tab_name, 0, 0, (uint64_t)(event_next - event_pos), 0, 0, 1, &HEAD_TAB) != 0)
			{
				ret = 8;
				printf("add_chain_op() ERROR%s %d \n", ERR_POST);
				return ret;
			}
			break;
		case 19:
			if (GT)
			{
				printf("---->Map Event:Pos%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			fseek(fds, FLAGS_OFFSET - LOG_POS_OFFSET, SEEK_CUR);

			if (map_an(fds) != 0)
			{
				ret = 7;
				printf("analyze_binlog:map_an ERROR %s %d \n", ERR_POST);
				return ret;
			}

			break;
		case 33:
			if (GT)
			{
				printf(">Gtid Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			fseek(fds, FLAGS_OFFSET - LOG_POS_OFFSET, SEEK_CUR);

			if (fread(gtid_buf, GTID_GNO, O_MEM, fds) != O_MEM)
			{
				ret = 6;
				printf("analyze_binlog:fread gtid_buf ERROR %s %d \n", ERR_POST);
				return ret;
			}

			if (gtid_an(gtid_buf) != 0)
			{
				ret = 5;
				printf("analyze_binlog:gtid_an() ERROR %s %d \n", ERR_POST);
				return ret;
			}

			if (event_size > (uint32_t)44)
			{
				fseek(fds, GTID_FLAG - GTID_GNO, SEEK_CUR);
				if (fread(gtid_co_seq, GTID_SEQ - GTID_FLAG, O_MEM, fds) != O_MEM)
				{
					ret = 7;
					printf("analyze_binlog:fread gtid_co_seq ERROR %s %d \n", ERR_POST);
					return ret;
				}
				if (gtid_com_an(gtid_co_seq) != 0)
				{
					ret = 8;
					printf("analyze_binlog:gtid_com_an() ERROR %s %d \n", ERR_POST);
					return ret;
				}
			}

			memset(gtid_buf, 0, 25);
			memset(gtid_co_seq, 0, 16);
			break;
			// QUERY_EVENT = 2,
		case 2:
			if (GT)
			{
				printf("-->Query Event:Pos:%u(0X%x) N_Pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			fseek(fds, FLAGS_OFFSET - LOG_POS_OFFSET, SEEK_CUR);
			// 事件开始时间
			QUR_T = (uint32_t)event_time; // 获得query event 时间
			Log(DEBUG, "事件开始时间: %u", QUR_T);
			QUR_POS = (uint32_t)event_pos; // 获得query event pos位置 OK

			if (query_an(fds, event_size, event_pos) != 0)
			{
				ret = 12;
				printf("analyze_binlog:query_an ERROR %s %d \n", ERR_POST);
				return ret;
			}

			break;
			//  XID_EVENT = 16
			/**
			 * QUERY_EVENT = 2标记着事务开始的时间
			 * XID_EVENT   = 16 标记着事务结束的时间
			 */
		case 16:
			if (GT)
			{
				printf(">Xid Event:Pos:%u(0X%x) N_Pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			// 事务结束pos点
			POS_E = (uint64_t)event_next;
			Log(DEBUG, "事件结束pos点: %u", POS_E);
			QUR_X = (uint32_t)event_time; // 获得xid event时间   本事件结束时间 OK
			Log(DEBUG, "事件结束时间: %u", QUR_X);
			Log(DEBUG, "事件开始时间: %u", QUR_T);
			Log(DEBUG, "事件总共耗时: %u", QUR_X - QUR_T);
			QUR_POS_END = (uint64_t)event_next; // 获得xid event 结束位置
			TRX_TOTAL++;
			// 大事务判断

			if (POS_E - POS_T > mi)
			{
				if (node < (uint64_t)MAX_MEM_COUNT)
				{
					//  POS_E:事件结束位置 bPOS_T：事件开始位置
					if (init_chain(POS_E, POS_T, &HEAD_TRX) != 0) // add import
					{
						node++;
						ret = 30;
						printf("analyze_binlog:call init_chain ERROR %s %d \n", ERR_POST);
						return ret;
					}
				}
				else
				{
					ret = 31;
					printf("analyze_binlog:call init_chain MAX_MEM 2G %s %d \n", ERR_POST);
					return ret;
				}
			}
			node = 0;
			// 长时间事务监控
			if (QUR_X > QUR_T && QUR_X - QUR_T > mt && QUR_T > 0)
			{
				if (node < (uint64_t)MAX_MEM_COUNT)
				{
					/**
					 * *trx_ar = a;	    // end time
					 *(trx_ar + 1) = b; // begin time
					 *(trx_ar + 2) = c; // query pos pos点开始位置
					 *(trx_ar + 3) = d; // query end  pos点结束位置
					 *(trx_ar + 4) = e; // query exe_time
					 *
					 */
					// Log(DEBUG, "结束时间 : %s \n", utime_local(QUR_X));
					Log(ERROR, " 第  %ld 个事件 \n", EVE_TOTAL);
					// HEAD_MT 长时间事务
					if (init_chain2((uint64_t)QUR_X, (uint64_t)QUR_T, (uint64_t)QUR_POS, (uint64_t)QUR_POS_END, (uint64_t)EXE_T, &HEAD_MT) != 0) // add import
					{
						node++;
						ret = 30;
						printf("analyze_binlog:call init_chain ERROR %s %d \n", ERR_POST);
						return ret;
					}
				}
				else
				{
					ret = 31;
					printf("analyze_binlog:call init_chain MAX_MEM 2G %s %d \n", ERR_POST);
					return ret;
				}
			}

			if (GT)
			{
				printf("COMMIT; /*!Trx end*/ Gno:%lu\n", GTID_GNO_);
			}
			break;
		case 34:
			if (GT)
			{
				printf(">Anonymous gtid Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
				printf("Gtid:Anonymous(Gno=0)");
			}
			if (event_size > (uint32_t)44)
			{
				fseek(fds, FLAGS_OFFSET - LOG_POS_OFFSET, SEEK_CUR);
				fseek(fds, GTID_FLAG, SEEK_CUR);
				if (fread(gtid_co_seq, GTID_SEQ - GTID_FLAG, O_MEM, fds) != O_MEM)
				{
					ret = 50;
					printf("analyze_binlog:fread gtid_co_seq ERROR %s %d \n", ERR_POST);
					return ret;
				}
				if (gtid_com_an(gtid_co_seq) != 0)
				{
					ret = 51;
					printf("analyze_binlog:gtid_com_an() ERROR %s %d \n", ERR_POST);
					return ret;
				}
			}
			memset(gtid_buf, 0, 25);
			memset(gtid_co_seq, 0, 16);
			break;
		case 35:
			if (GT)
			{
				printf(">Previous gtid Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			break;
		case 3:
			if (GT)
			{
				printf(">Stop log Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			break;
		case 4:
			if (GT)
			{
				printf(">Rotate log Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			break;
		case 5:
			if (GT)
			{
				printf(">Intvar log Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			break;
		case 6:
			if (GT)
			{
				printf(">Rand log Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			break;
		case 15:
			if (GT)
			{
				printf(">Format description log Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			BEG_TIME = event_time; // add
			break;
		case 29:
			if (GT)
			{
				printf("-->Rows query(use execute sql) log Event:Pos:%u(0X%x) N_pos:%u(0X%x) Time:%u Event_size:%u(bytes) \n", event_pos, event_pos, event_next, event_next, event_time, event_size);
			}
			break;
		default:
			break;
		}
	}

	return ret;
}

// bin_file: fd
// pi: how many piece split to total part 拆分多少块
// mi: large than mi(MB) will to total part 大事件大小阈值
// mt: larger than mt(sec) will to toal part 长时间事件阈值
int a_binlog(const char *bin_file, uint32_t pi, uint64_t mi, uint32_t mt)
{
	int ret = 0;
	FILE *fd;
	if (bin_file == NULL)
	{
		ret = 1;
		printf("a_binlog:bin_file == NULL? %s %d \n", ERR_POST);
		return ret;
	}

	// 读取binlog文件
	if ((fd = fopen(bin_file, "r")) == NULL)
	{
		ret = 2;
		printf("a_binlog:fopen() binlog file error %s %d \n", ERR_POST);
		perror("openfile error");
		return ret;
	}

	// 检查binlog日志信息
	if (check_bin_format(fd) != 0)
	{
		ret = 3;
		printf("a_binlog:check_bin_format() binlog error %s %d \n", ERR_POST);
		return ret;
	}
	// 分析日志
	if (analyze_binlog(fd, pi, mi, mt) != 0)
	{
		ret = 4;
		printf("a_binlog:analyze_binlog() error %s %d \n", ERR_POST);
		return ret;
	}
	// HEAD_TRX 大于2M事务 HEAD_MT 10秒以上事务
	if (print_total(&HEAD_PI, &HEAD_TRX, &HEAD_MT, &HEAD_TAB, mi, mt) != 0)
	{
		ret = 5;
		printf("a_binlog:print_total() error %s %d \n", ERR_POST);
		return ret;
	}

	return ret;
}

int usage(void)
{
	printf("[Author]: gaopeng [QQ]:22389860 [blog]:http://blog.itpub.net/7728585/ \n");
	printf("--USAGE:./infobin binlogfile pieces bigtrxsize bigtrxtime [-t] [-force]\n");
	printf("[binlogfile]:binlog file!\n");
	printf("[piece]:how many piece will split,is a Highly balanced histogram,\n");
	printf("        find which time generate biggest binlog.(must:piece<2000000)\n");
	printf("[bigtrxsize](bytes):larger than this size trx will view.(must:trx>256(bytes))\n");
	printf("[bigtrxtime](sec):larger than this sec trx will view.(must:>0(sec))\n");
	printf("[[-t]]:if [-t] no detail is print out,the result will small\n");
	printf("[[-force]]:force analyze if unkown error check!!\n");
	return 0;
}

static check_force(int argc, char *argv[])
{
	int i = 0;
	for (i = 1; i < argc; i++)
	{
		if (!strcmp(*(argv + i), "-force"))
		{
			return 1;
		}
	}
	return 0;
}

int main(int argc, char *argv[])
{

	// 日志输出

	log_set_level(0);
	log_set_quiet(0);

	// log_debug("debug");
	// log_info("info");
	// log_warn("warn");

	/**
	 *第一个20 是分片数量,将binlog分为大小相等的片段，生成时间越短则这段时间生成binlog量越大，则事物越频繁。
	 *第二个2000000 是大于2M左右的事物定义为大事物。
	 *第三个10 是大于10秒未提交的事物定义为长期未提交的事物。 *
	 *第四个-t 代表不做详细event解析输出，仅仅获取相应的结果
	 */
	int ret = 0;
	uint32_t pi = 0;
	uint64_t mi = 0;
	uint32_t mt = 0;

	// printf("argv + 1 : ", argv + 1);
	// log_info("argv + 1 :  %d", argc);
	log_info("*(argv + 1) :  %s \n", *(argv + 1));
	Log(INFO, "this is info %s", *(argv + 1));
	if (argc == 2 && !strcmp(*(argv + 1), "--help"))
	{
		ret = 1;
		usage();
		return ret;
	}

	if (argc != 5)
	{
		if (argc == 6 && !strcmp(*(argv + 5), "-t"))
		{
			GT = 0;
		}
		else if (argc == 6 && check_force(argc, argv))
		{
			FORCE = 1;
		}
		else if (argc == 7 && check_force(argc, argv) && !strcmp(*(argv + 5), "-t"))
		{
			GT = 0;
			FORCE = 1;
		}
		else
		{
			ret = 1;
			printf("USAGE ERROR!\n");
			usage();
			return ret;
		}
	}

	if (check_asii_num(*(argv + 2)) == -1 || check_asii_num(*(argv + 3)) == -1 || check_asii_num(*(argv + 4)) == -1)
	{
		ret = 101;
		printf("parameter 2 3 4 must number \n");
		usage();
		return ret;
	}

	// 从控制台读取参数
	sscanf(*(argv + 2), "%u", &pi);
	sscanf(*(argv + 3), "%ld", &mi);
	sscanf(*(argv + 4), "%u", &mt);
	if (pi >= 2000000 || mi <= 256)
	{
		ret = 5;
		printf("ERROR: piece>=2000000 || bigtrxsize <= 256(bytes)\n");
		usage();
		return ret;
	}

	if (mt == 0) // add used TOTAL long TRX
	{
		ret = 100;
		printf("ERROR: mt can't 0 \n");
		usage();
		return ret;
	}

	// 检查大端或者 小端
	if (check_lit() != 0)
	{
		ret = 3;
		printf("ERROR:This tool only Little_endian platform!\n");
		return ret;
	}

	printf("[Author]: gaopeng [QQ]:22389860  [blog]:http://blog.itpub.net/7728585/\n");
	printf("Warning: This tool only Little_endian platform!\n");
	printf("Little_endian check ok!!!\n");
	printf("-------------Now begin--------------\n");
	// 10 pi
	// mi (kb)
	// mt (sec)
	//  *(argv + 1) : /pgdata/projetcs/cJSON/infobin-master/binlog/mysql-bin.000004
	if (a_binlog(*(argv + 1), pi, mi, mt) != 0)
	{
		ret = 2;
		printf("ERROR:a_binlog fun error\n");
		return ret;
	}

	return ret;
}
