#include <string>
#include <iostream>
#include "client.h"
using namespace std;

client::client()
{
	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_port = htons(3237);
	inet_pton(AF_INET, servInetAddr, &sockaddr.sin_addr);
	if ((connect(socketfd, (struct sockaddr*)&sockaddr, sizeof(sockaddr))) < 0)
	{
		printf("connect error %s errno: %d\n", strerror(errno), errno);
		exit(0);
	}
}

client::~client()
{
	close(socketfd);
}

char* client::Get(std::string key)
{
	string s = "Get, " + key;
	if ((send(socketfd, s.c_str(), strlen(s.c_str()), 0)) < 0)
	{
		printf("send mes error: %s errno : %d", strerror(errno), errno);
		exit(0);
	}
	int n = recv(socketfd, recvline, MAXLINE, 0);     // 这里接收到请求
	cout << recvline;

}

void client::Put(std::string key, std::string value)
{
	std::string s = "Put, " + key + ", " + value;

	if ((send(socketfd, s.c_str(), strlen(s.c_str()), 0)) < 0)
	{
		printf("send mes error: %s errno : %d", strerror(errno), errno);
		exit(0);
	}
}

void client::Delete(std::string key)
{
	string s = "Get, " + key;
	if ((send(socketfd, s.c_str(), strlen(s.c_str()), 0)) < 0)
	{
		printf("send mes error: %s errno : %d", strerror(errno), errno);
		exit(0);
	}
}

void client::Scan()
{
	string s = "Scan. ";
	if ((send(socketfd, s.c_str(), strlen(s.c_str()), 0)) < 0)
	{
		printf("send mes error: %s errno : %d", strerror(errno), errno);
		exit(0);
	}
	while ((n = recv(socketfd, recvline, MAXLINE, 0)) != -1)
		;// 这里处理回传列表
}