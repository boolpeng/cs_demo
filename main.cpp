#include "server.h"
#include "mySql.h"

int main()
{
	server myServer;
	mySql mySql_;

	myServer.rollback();     // ��������������mysql������д�ء�
	myServer.loop();         // ��������

	return 0;
}