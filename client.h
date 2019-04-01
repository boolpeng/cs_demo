#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXLINE 500

class client
{
public:
	client();
	~client();

	// 相关接口
	char* Get(std::string key);
	void Put(std::string key, std::string value);
	void Scan();
	void Delete(std::string key);

private:
	char *servInetAddr = "127.0.0.1";
	int socketfd;
	struct sockaddr_in sockaddr;
	char recvline[MAXLINE], sendline[MAXLINE];
	int n;
};

#endif // !CLIENT_H

