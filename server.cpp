#include <mysql.h>
#include "server.h"
#include "mySql.h"
using namespace std;

/*���캯����Ҫ������װsocket �Ĵ������������*/
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


/*����������Ҫ�����ͷ�socket����*/
server::~server()
{
	close(listenfd);
}

/*ѭ������socket����*/
void server::loop()
{
	while ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1)
	{
		printf("accpet socket error: %s errno :%d\n", strerror(errno), errno);
		continue;
	}
	server::channel();    // �����ӣ������¼��ַ�
}


/*�ж�key�Ƿ���� ����keyΪ8�ֽڣ�*/
bool server::isRightKey(std::string key)
{
	return key.length() == 8;
}

/*������������ö�Ӧ�Ļص�����*/
void server::channel()
{
	n = recv(connfd, buff, MAXLINE, 0);     // ������յ�����

	// �������ַ������н���
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
			cout << "key�����ڣ�" << endl;
	}
	else
		cout << "key ���� value ����" << endl;
}


void server::Put(std::string key, string value)
{
	if (isRightKey(key))
	{
		mySql_.addData(key, value);    // �Ƚ����ݴ洢�����ݿ�
		hashMap[key] = value;          // �ٴ��ڹ�ϣ��
	}
	else
		cout << "key ���� value ����" << endl;
}

void server::Scan()
{
	// �Թ�ϣ����б�������ÿ��key��value������͸��ͻ���
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
	    mySql_.deleteData(key);            // �Ƚ����ݴ����ݿ���ɾ��
		hashMap.erase(key);                // �ٴӹ�ϣ����ɾ��
	}
	else
		cout << "key ���� value ����" << endl;
}

void server::rollback()
{
	mySql_.rollback();
}