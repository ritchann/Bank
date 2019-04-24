#include "BankManagmentSystem.h"

std::mutex mutex;

std::condition_variable cond1;
std::condition_variable cond2;

std::queue<Client*> queue;

std::queue<Client*> * queue1;
std::queue<Client*> * queue2;
std::queue<Client*> * queue3;
std::queue<Client*> * queue4;

int maximum_capacity = 5;
int capacity = 10;
int hours[30] = { 10,10,10,9,9,9,8,8,8,7,7,7,6,6,6,5,5,5,4,4,4,3,3,3,2,2,2,1,1,1 };

std::chrono::duration<double> middleTime_value;
int middleTime_count;

std::chrono::duration<double> time_span;

void BankManagmentSystem::start() {
	queue1 = new std::queue<Client*>;
	queue2 = new std::queue<Client*>;
	queue3 = new std::queue<Client*>;
	queue4 = new std::queue<Client*>;

	int stage1 = 1 + rand() % 30;
	int stage2 = 1 + rand() % 30;
	int stage3 = 1 + rand() % 30;
	int stage4 = 1 + rand() % 30;

	std::thread Client(generateClients);
	std::thread Operator(processClients);

	std::thread Operator1(Work, std::ref(queue1), stage1); 
	std::thread Operator2(Work, std::ref(queue2), stage2); 
	std::thread Operator3(Work, std::ref(queue3), stage3); 
	std::thread Operator4(Work, std::ref(queue4), stage4); 


	Client.join();
	Operator.join();

	Operator1.join();
	Operator2.join();
	Operator3.join();
	Operator4.join();

}

void BankManagmentSystem::generateClients() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(2500 + rand() % 10000));
		std::unique_lock<std::mutex> mlock(mutex); 
		while (queue.size() == capacity) { cond2.wait(mlock); }
		Client* client = new Client();
		std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client-> getSuboperationNumber() << std::endl;
		queue.push(client);
		mlock.unlock();
		cond1.notify_one();
	}
}

void BankManagmentSystem::processClients() {
	while (true) {
		std::unique_lock<std::mutex> mlock(mutex);
		while (queue.empty()) { cond1.wait(mlock); }
		std::cout << "Customer's operation number " << queue.front()->getOperationNumber() << " " << queue.front()->getSuboperationNumber() << 
			" is going to process" << std::endl;

		Client* tmp = queue.front();
		chooseOperator(tmp);

		std::cout << "First = " << queue1->size() << " Second  = " << queue2->size() << " Third = " << queue3->size() << " Fourth = " << queue4->size() << std::endl;

	    queue.pop();

		cond2.notify_one();
	}
}

void BankManagmentSystem::Work(std::queue<Client*> * q, int stage) {
	while (true) {
		while (q->empty()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		std::unique_lock<std::mutex> mlock(mutex);
		Client* client = q->front();
		q->pop();
		mlock.unlock();

		switch (client->getOperationNumber()) {
		case 1:
			time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
			std::this_thread::sleep_for(std::chrono::milliseconds(hours[stage - 1]));
			break;
		case 2:
			switch (client->getSuboperationNumber())
			{
			case 1:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(hours[stage - 1]));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				std::cout << std::endl;
				middleTime_value = middleTime_value + time_span;
				middleTime_count += 1;
				std::cout << "SUM WAITING TIME: " << middleTime_value.count() / middleTime_count << std::endl;
				std::cout << std::endl;
				break;
			case 2:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(hours[stage - 1]));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				std::cout << std::endl;
				middleTime_value = middleTime_value + time_span;
				middleTime_count += 1;
				std::cout << "SUM WAITING TIME: " << middleTime_value.count() / middleTime_count << std::endl;
				std::cout << std::endl;
				break;
			default:
				break;
			}
			break;
		case 3:
			switch (client->getSuboperationNumber())
			{
			case 1:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(hours[stage - 1]));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				std::cout << std::endl;
				middleTime_value = middleTime_value + time_span;
				middleTime_count += 1;
				std::cout << "SUM WAITING TIME: " << middleTime_value.count() / middleTime_count << std::endl;
				std::cout << std::endl;
				break;
			case 2:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(hours[stage - 1]));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				std::cout << std::endl;
				middleTime_value = middleTime_value + time_span;
				middleTime_count += 1;
				std::cout << "SUM WAITING TIME: " << middleTime_value.count() / middleTime_count << std::endl;
				std::cout << std::endl;
				break;
			default:
				break;
			}
			break;
		case 4:
			switch (client->getSuboperationNumber())
			{
			case 1:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(hours[stage - 1]));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				std::cout << std::endl;
				middleTime_value = middleTime_value + time_span;
				middleTime_count += 1;
				std::cout << "SUM WAITING TIME: " << middleTime_value.count() / middleTime_count << std::endl;
				std::cout << std::endl;
				break;
			case 2:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(hours[stage - 1]));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				std::cout << std::endl;
				middleTime_value = middleTime_value + time_span;
				middleTime_count += 1;
				std::cout << "SUM WAITING TIME: " << middleTime_value.count() / middleTime_count << std::endl;
				std::cout << std::endl;
				break;
			default:
				break;
			}
			break;
		}
	}
}

void BankManagmentSystem::chooseOperator(Client* client) {

	if ((queue1->size() == 5) || (queue2->size() == 5)) {
		if ((client->getOperationNumber() % 2 == 0) && (client->getSuboperationNumber() % 2 == 0)) {
			std::cout << "Customer " << client->getOperationNumber() << " " << client->getSuboperationNumber() << " goes to 4 operator" << std::endl;
			queue4->push(client);
		}
		else {
			std::cout << "Customer " << client->getOperationNumber() << " " << client->getSuboperationNumber() << " goes to 3 operator" << std::endl;
			queue3->push(client);
		}
	}

	else if ((client->getOperationNumber() % 2 == 0) && (client->getSuboperationNumber() % 2 == 0)) {
		std::cout << "Customer " << client->getOperationNumber() << " " << client->getSuboperationNumber() << " goes to 1 operator" << std::endl;
		queue1->push(client);
	}
	else {
		std::cout << "Customer " << client->getOperationNumber() << " " << client->getSuboperationNumber() << " goes to 2 operator" << std::endl;
		queue2->push(client);
	}

}