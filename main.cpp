#include "server.h"
#include "mySql.h"

int main()
{
	server myServer;
	mySql mySql_;

	myServer.rollback();     // 服务器重启，将mysql的数据写回。
	myServer.loop();         // 接收请求

	return 0;
}