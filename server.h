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
	server();            // ��װsocket����
	~server();           // �ͷ�����

	void loop();          // ��������
	void rollback();      // ���ݳ־û�
	
private:
	void channel();       // ���������ִ����Ӧ����
	bool isRightKey(string key);     // �ж�key����ȷ��

	// ��Ӧ�ͻ�����Ϣ�ӿ�
	std::string Get(string key);
	void Put(string key, string value);
	void Scan();
	void Delete(string key);

private:
	// ����socket����
	int listenfd, connfd;
	struct sockaddr_in sockaddress;

	std::vector<char*> request{ NULL };              // �ͻ����������
	std::unordered_map<string, string> hashMap;      // �洢����
	
	char buff[MAXLINE];
	int n;
	string flag, key;
	string value;
};

#endif