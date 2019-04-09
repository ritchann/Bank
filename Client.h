#pragma once
#include <ctime>
#include <iostream>

using namespace std;
class Client
{
private:
	int operationNumber;
	int suboperationNumber;
public:
	Client() {
		operationNumber= 1 + rand()%4;
		suboperationNumber = 1 + rand()%2;
	}

	int getOperationNumber() {
		return operationNumber;
	}

	int getSuboperationNumber() {
		return suboperationNumber;
	}
	~Client();
};

