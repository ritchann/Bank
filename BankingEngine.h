#pragma once
#include <vector>
#include "Client.h"
#include "Operator.h"

using namespace std;
class BankingEngine
{
private:
	vector<Client*> clients;
	vector<Operator*> operators;
public:
	BankingEngine() {
		clients.push_back(new Client());
		clients.push_back(new Client());
		clients.push_back(new Client());
		for (int i = 0; i < 12; i++){
			Operator* op=new Operator();
			op->setNumber(i / 3 + 1);
			operators.push_back(op);
		}
	}

	void start();
	~BankingEngine();
};

