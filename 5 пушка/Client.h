#pragma once
#include <ctime>
#include <iostream>
#include <ratio>


class Client
{
private:
	int operationNumber;
	int suboperationNumber;

public:
	Client() {
		operationNumber = 1 + rand() % 4;
		suboperationNumber = 1 + rand() % 2;
	}

	Client(int number) {
		switch (number) {
		case 1:
			operationNumber = 1;
			break;
		case 2:
			operationNumber = 2;
			suboperationNumber = 1 + rand() % 2;
			break;
		case 3:
			operationNumber = 3;
			suboperationNumber = 1 + rand() % 2;
			break;
		case 4:
			operationNumber = 2;
			suboperationNumber = 1 + rand() % 2;
			break;
		}
	}

	int getOperationNumber() {
		return operationNumber;
	}

	int getSuboperationNumber() {
		return suboperationNumber;
	}

	~Client() {};
};