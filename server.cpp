#include <mysql.h>
#include "server.h"
#include "mySql.h"
using namespace std;

/*构造函数主要用来封装socket 的创建，绑定与监听*/
server::server()
{
	memset(&sockaddress, 0, sizeof(sockaddr));   

	sockaddress.sin_family = AF_INET;
	sockaddress.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddress.sin_port = htons(3237);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bind(listenfd, (struct sockaddr *) &sockaddress, sizeof(sockaddr));

	listen(listenfd, 1024);
}


/*析构函数主要用来释放socket连接*/
server::~server()
{
	close(listenfd);
}

/*循环接收socket请求*/
void server::loop()
{
	while ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1)
	{
		printf("accpet socket error: %s errno :%d\n", strerror(errno), errno);
		continue;
	}
	server::channel();    // 有连接，进行事件分发
}


/*判断key是否合理 （即key为8字节）*/
bool server::isRightKey(std::string key)
{
	return key.length() == 8;
}

/*处理分析并调用对应的回调函数*/
void server::channel()
{
	n = recv(connfd, buff, MAXLINE, 0);     // 这里接收到请求

	// 对请求字符串进行解析
	request[0] = strtok(buff, " ,.");
	flag = request[0];
	int i = 0;
	while (request[i++] != NULL) {
		request[i] = strtok(NULL, " ,.");
	}
	if (request[1])
		key = request[1];
	if (request[2])
		value = request[2];

	if (flag == "Get")
		Get(key);
	else if (flag == "Put")
		Put(key, value);
	else if (flag == "Scan")
		Scan();
	else
		Delete(key);
}

std::string server::Get(std::string key)
{
	if (isRightKey(key))            
	{
		if (!hashMap[key].empty())
		{
			string buff = hashMap[key];
			send(listenfd, buff.c_str(), sizeof(buff), 0);
		}
		else
			cout << "key不存在！" << endl;
	}
	else
		cout << "key 或者 value 错误！" << endl;
}


void server::Put(std::string key, string value)
{
	if (isRightKey(key))
	{
		mySql_.addData(key, value);    // 先将数据存储于数据库
		hashMap[key] = value;          // 再存于哈希表
	}
	else
		cout << "key 或者 value 错误！" << endl;
}

void server::Scan()
{
	// 对哈希表进行遍历，将每组key与value打包发送给客户端
	for (auto iter = hashMap.begin(); iter != hashMap.end(); iter++)
	{
		string message = (*iter).first + " " + (*iter).second;
		send(listenfd, message.c_str(), sizeof(message.c_str()), 0);
	}
}

void server::Delete(std::string key)
{
	if (isRightKey(key))
	{
	    mySql_.deleteData(key);            // 先将数据从数据库中删除
		hashMap.erase(key);                // 再从哈希表中删除
	}
	else
		cout << "key 或者 value 错误！" << endl;
}

void server::rollback()
{
	mySql_.rollback();
}