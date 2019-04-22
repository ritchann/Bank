#include "BankingEngine.h"
#include <future>
#include <thread>
#include <mutex>
#include <thread>
#include <windows.h>

mutex mut;

using namespace std;
void BankingEngine::start() {
	//cout << queueFirstOperator.size() << endl;
	//thread th1_1;
	thread queues(newClients, ref(queueFirstOperator), ref(queueSecondOperator), ref(queueThirdOperator), ref(queueFourthOperator));
	thread th1(Work, ref(queueFirstOperator), operator1,ref(countQueue));
	thread th2(Work, ref(queueSecondOperator), operator2, ref(countQueue));
	thread th3(Work, ref(queueThirdOperator), operator3, ref(countQueue));
	thread th4(Work, ref(queueFourthOperator), operator4, ref(countQueue));
	thread th1_1;
	//condition_variable m_alarm;
	//mutex m_mutex;
	//unique_lock<mutex> lock(m_mutex);
	//while (true){
	//	if (queueFirstOperator.empty()) {
	//		m_alarm.wait(lock);
	//		cout << "1 OPERATOR LOCK" << endl;
	//		while (queueFirstOperator.empty()) {

	//		}
	//		cout << "1 OPERATOR UNLOCK" << endl;
	//		m_alarm.notify_one();
	//	}
	//}
	/*while (true) {
		if (queueFirstOperator.size() > 8 && countQueue[0] < 1) {
			cout << "NEW OPERATOR IN 1 QUEUE" << endl;
			cout << queueFirstOperator.size() << endl;
			countQueue[0] += 1;
			th1_1 = thread(Work, ref(queueFirstOperator), operator1_1, ref(countQueue));
		}
		this_thread::sleep_for(chrono::seconds(2));
		cout << queueFirstOperator.size() << endl;
	}*/

	//while (true) {
	//	if (queueFirstOperator.size() > 5 && countQueue[0]>1) {
	//		cout << "NEW OPERATOR IN 1 QUEUE" << endl;
	//		countQueue[0] += 1;
	//		th1_1 = thread(Work, ref(queueFirstOperator), operator1_1, ref(countQueue));
	//	}
	//	else {
	//		if (queueFirstOperator.empty()) {
	//			if (th1_1.joinable()) {
	//				
	//			}
	//		}
	//	}
	//}

	th1.join();
	th2.join();
	th3.join();
	th4.join();
	if (!th1.joinable() && !th2.joinable() && !th3.joinable() && !th4.joinable()) {
		queues.detach();
		//this_thread::yield();
	
	}
	//if (!th1.joinable()) {
	//	queues.detach();
	//}
	//queues.join();

}

void BankingEngine::Work(vector<Client*> &clients, Operator* oper, vector<int> &countQueue) {
	while (true)
	{
		if (clients.empty()) {
			this_thread::sleep_for(chrono::seconds(11));
			if (clients.empty()) {
				mut.lock();
				cout << endl;
				cout << "SLEEP  OPERATOR " << oper->getNumber() << endl;
				mut.unlock();
				while (clients.empty()) {
					this_thread::sleep_for(chrono::seconds(1));
				}
				mut.lock();
				cout << endl;
				cout << "DO WORK OPERATOR " << oper->getNumber() << endl;
				mut.unlock();
			}
		}
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
	
		//if (clients.size()> 5 && countQueue[oper->getNumber()-1]<2) {
		//	cout << "NEW " << oper->getNumber() << " OPERATOR " << endl;
		//	thread th1_1(Work, clients, oper,ref(countQueue));
		//	mut.lock();
		//	countQueue[oper->getNumber() - 1]+=1;
		//	cout << endl;
		//	//cout << "NEW " << oper->getNumber() << " OPERATOR " << endl;
		//	mut.unlock();
		//	th1_1.join();
		//}
	}
	mut.lock();
	cout << endl;
	cout << "Thread finish " << this_thread::get_id() << endl;
	mut.unlock();
}

void BankingEngine::newClients(vector<Client*> &queueFirstOperator, vector<Client*> &queueSecondOperator, vector<Client*> &queueThirdOperator, vector<Client*> &queueFourthOperator) {
	int time;
	bool flag = true;
	while(flag){
		time=5+rand()%10;
		this_thread::sleep_for(chrono::seconds(time));
		Client* client = new Client();
		mut.lock();
		if (client->getOperationNumber() == 1) {
			queueFirstOperator.push_back(client);
			cout << endl;
			cout << "NEW CLIENT IN 1 QUEUE " <<", CURRENT SIZE QUEUE "<< queueFirstOperator.size()<< endl;
		}
		if (client->getOperationNumber() == 2) {
			queueSecondOperator.push_back(client);
			cout << endl;
			cout << "NEW CLIENT IN 2 QUEUE" << ", CURRENT SIZE QUEUE " << queueSecondOperator.size() << endl;
		}
		if (client->getOperationNumber() == 3) {
			queueThirdOperator.push_back(client);
			cout << endl;
			cout << "NEW CLIENT IN 3 QUEUE" << ", CURRENT SIZE QUEUE " << queueThirdOperator.size() << endl;
		}
		if (client->getOperationNumber() == 4) {
			queueFourthOperator.push_back(client);
			cout << endl;
			cout << "NEW CLIENT IN 4 QUEUE" << ", CURRENT SIZE QUEUE " << queueFourthOperator.size() << endl;;
		}
		mut.unlock();
		/*if (queueFirstOperator.size() == 0 && queueSecondOperator.size() == 0 && queueThirdOperator.size() == 0 && queueFourthOperator.size() == 0) {
			flag = false;
		}*/
	}
 }


BankingEngine::~BankingEngine(){
}
