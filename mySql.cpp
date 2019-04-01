#include <iostream>
#include <string>
#include "mySql.h"
using namespace std;

 MYSQL mysql, *sock;      // use to connect mysql
 MYSQL_RES * res = NULL;  // result
 MYSQL_ROW row;           // 存放记录

mySql::mySql()
{
	mysql_init(&mysql);  // 初始化数据库
	mysql_options(&mysql, MYSQL_SET_CHARSET_DIR, "gbk");   // 设置编码方式
    
	while ((sock = mysql_real_connect(&mysql, "132.232.50.116", "curry", "Curry30", "hashMap", 0, NULL, 0)) == NULL)
		;                                                  // 数据库的连接
}

mySql::~mySql()
{
	// 数据库的关闭
}

void mySql::addData(string key, string value)
{
	string message = "insert into hashMap values ('" + key + ','+ value + "')";

	int  result = mysql_query(sock, message.c_str());
	if (!result)
	{
		printf("Put success.\n");
	}
}

void mySql::deleteData(string key)
{
	string message = "delete from hashMap where key ='" + key + "'";

	int  result = mysql_query(sock, message.c_str());
	if (!result)
	{
		printf("Delete success.\n");
	}
}

void mySql::rollback()
{
	string message = "select * from hashMap";
	int result = mysql_query(sock, message.c_str());
	if (!result)
	{
		res = mysql_store_result(sock);
		int fields = mysql_num_fields(res);
		// 循环遍历进行回写
		int j = 0;
		while ((row = mysql_fetch_row(res))) {
			for (int i = 0; i < fields; i++) {
				//  将row写到result
			}
			j++;
		}
		// 这里将result写回unordered_map    

	}
}
