#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include "mySql.h"


#define MAXLINE 500
using namespace std;

mySql mySql_;

class server
{
public:
	server();            // 封装socket连接
	~server();           // 释放连接

	void loop();          // 接收请求
	void rollback();      // 数据持久化
	
private:
	void channel();       // 请求解析并执行相应函数
	bool isRightKey(string key);     // 判断key的正确性

	// 响应客户端信息接口
	std::string Get(string key);
	void Put(string key, string value);
	void Scan();
	void Delete(string key);

private:
	// 用于socket连接
	int listenfd, connfd;
	struct sockaddr_in sockaddress;

	std::vector<char*> request{ NULL };              // 客户端请求解析
	std::unordered_map<string, string> hashMap;      // 存储数据
	
	char buff[MAXLINE];
	int n;
	string flag, key;
	string value;
};

#endif