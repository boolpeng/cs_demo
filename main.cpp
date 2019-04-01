#include "client.h"
#include <string>
#include<iostream>
using namespace std;

int main(int argc, char **argv)
{
	client myClient;
	string key = "ping_cap" ;
	string vaule = "aaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeee";

	myClient.Put(key, value);
	myClient.Get(key);
	myClient.Delete(key);
	myClient.Scan();

	return 0;
	
}
