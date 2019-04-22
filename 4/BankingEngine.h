#pragma once
#include <vector>
#include "Client.h"
#include "Operator.h"
#include <thread>


using namespace std;
class BankingEngine
{
private:
	vector<Client*> queueFirstOperator;
	vector<Client*> queueSecondOperator;
	vector<Client*> queueThirdOperator;
	vector<Client*> queueFourthOperator;

	Operator* operator1;
	Operator* operator1_1;
	Operator* operator2;
	Operator* operator3;
	Operator* operator4;

	vector<int> countQueue;

public:

	BankingEngine() {
		for (int i = 0; i < 5; i++) {
			Client* client = new Client();
			if (client->getOperationNumber() == 1)
				queueFirstOperator.push_back(client);
			if (client->getOperationNumber() == 2)
				queueSecondOperator.push_back(client);
			if (client->getOperationNumber() == 3)
				queueThirdOperator.push_back(client);
			if (client->getOperationNumber() == 4)
				queueFourthOperator.push_back(client);
		}
		operator1 = new Operator();
		operator1->setNumber(1);

		operator1_1 = new Operator();
		operator1_1->setNumber(1);

		operator2 = new Operator();
		operator2->setNumber(2);

		operator3 = new Operator();
		operator3->setNumber(3);

		operator4 = new Operator();
		operator4->setNumber(4);
		
		countQueue.resize(4);
	}

	void start();
	static void newClients(vector<Client*> &queueFirstOperator, vector<Client*> &queueSecondOperator, vector<Client*> &queueThirdOperator,vector<Client*> &queueFourthOperator);
	static void Work(vector<Client*> &clients,Operator* oper,vector<int> &countQueue);
	~BankingEngine();
};

