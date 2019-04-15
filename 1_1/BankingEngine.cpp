#include "BankingEngine.h"
#include <future>
#include <thread>
#include <mutex>

mutex mut;

using namespace std;
void BankingEngine::start() {
	thread th1(Work, queueFirstOperator, operator1);
	thread th2(Work, queueSecondOperator, operator2);
	thread th3(Work, queueThirdOperator, operator3);
	thread th4(Work, queueFourthOperator, operator4);
	th1.join();
	th2.join();
	th3.join();
	th4.join();
}

void BankingEngine::Work(vector<Client*> clients, Operator* oper) {
	int count = 0;
	while (!clients.empty())
	{
		count++;
		this_thread::sleep_for(chrono::seconds(oper->getWorrkingHours()));
		mut.lock();
		cout << endl;
		cout << "Operator number " << oper->getNumber() << "  " << this_thread::get_id()<<" work time: " <<oper->getWorrkingHours()<< endl;
		switch (clients[0]->getOperationNumber()) {
		case 1:
			cout << "Credit is issued \n";
			break;
		case 2:
			switch (clients[0]->getSuboperationNumber())
			{
			case 1:
				cout << "Account is open \n";
				break;
			case 2:
				cout << "Plastic card framed \n";
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (clients[0]->getSuboperationNumber())
			{
			case 1:
				cout << "Consultation completed \n";
				break;
			case 2:
				cout << "Translation issued \n";
				break;
			default:
				break;
			}
			break;
		case 4:
			switch (clients[0]->getSuboperationNumber())
			{
			case 1:
				cout << "Payment accepted \n";
				break;
			case 2:
				cout << "Work with cash produced \n ";
				break;
			default:
				break;
			}
			break;
		}
		clients.erase(clients.begin());
		mut.unlock();
		if (count % 100 == 0) {
			Client* client = new Client(oper->getNumber());
			clients.push_back(client);
			mut.lock();
			cout << endl;
			cout << "In " << oper->getNumber() << " queue  push new client" << endl;
			mut.unlock();
		}
	/*
		if (clients.size()> 5 && countQueue[oper->getNumber()-1]<2) {
			thread th1_1(Work, clients, oper);
			mut.lock();
			countQueue[oper->getNumber() - 1]++;
			cout << endl;
			cout << "NEW " << oper->getNumber() << " OPERATOR " << endl;
			mut.unlock();
			th1_1.join();
		}*/
	}
	mut.lock();
	cout << endl;
	cout << "Thread finish " << this_thread::get_id() << endl;
	mut.unlock();
}


BankingEngine::~BankingEngine(){
}

