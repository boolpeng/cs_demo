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
	vector<vector<string>> result;     // 二维数组储存回滚遍历结果
};

#endif

