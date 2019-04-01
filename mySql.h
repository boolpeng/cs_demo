#ifndef mySql_H
#define mySql_H

#include <string>
#include <vector>
#include <mysql.h>

using namespace std;

class server;
class mySql
{
public:
	mySql();
	~mySql();

	void addData(string key, string value);
	void deleteData(string key);
	void rollback();
private:
	vector<vector<string>> result;     // ��ά���鴢��ع��������
};

#endif

