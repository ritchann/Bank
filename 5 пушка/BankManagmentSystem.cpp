#include "BankManagmentSystem.h"

std::mutex mutex;
std::condition_variable cond1;
std::condition_variable cond2;
std::queue<Client*> queue;

std::queue<Client*> queue1;
std::queue<Client*> queue2;
std::queue<Client*> queue3;
std::queue<Client*> queue4;

int maximum_capacity = 5;
int capacity = 20;

void BankManagmentSystem::start() {
	std::thread Client(generateClients);
	std::thread Operator(processClients);

	std::thread Operator1(Work, queue1); // основной не профи (операция 2,2 и 4,4 для профи, остальные не для профи)
	std::thread Operator2(Work, queue2); // основной профи
	std::thread Operator3(Work, queue3); // неосновной не профи
	std::thread Operator4(Work, queue4); // неосновной профи

	Client.join();
	Operator.join();

	Operator1.join();
	Operator2.join();
	Operator3.join();
	Operator4.join();

}

void BankManagmentSystem::generateClients() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
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

	    queue.pop();

		std::cout << "Customer's operation number " << tmp->getOperationNumber() << " " << tmp->getSuboperationNumber() <<
			" finished processing" << std::endl;

		cond2.notify_one();
	}
}

void BankManagmentSystem::Work(std::queue<Client*> queue) {
	while (queue.empty()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	Client* client = queue.front();
	queue.pop();

	switch (client->getOperationNumber()) {
	case 1:
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		//std::cout << "Credit is issued \n";
		break;
	case 2:
		switch (client->getSuboperationNumber())
		{
		case 1:
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			//std::cout << "Account is open \n";
			break;
		case 2:
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//std::cout << "Plastic card framed \n";
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (client->getSuboperationNumber())
		{
		case 1:
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			//std::cout << "Consultation completed \n";
			break;
		case 2:
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			//std::cout << "Translation issued \n";
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (client->getSuboperationNumber())
		{
		case 1:
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
			//std::cout << "Payment accepted \n";
			break;
		case 2:
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//std::cout << "Work with cash produced \n ";
			break;
		default:
			break;
		}
		break;
	}
}

void BankManagmentSystem::chooseOperator(Client* client) {

	if ((queue1.size() == 5) && (queue2.size() == 5)) {
		if ((client->getOperationNumber() % 2 == 0) && (client->getSuboperationNumber() % 2 == 0)) {
			std::cout << "Customer " << client->getOperationNumber() << " " << client->getSuboperationNumber() << " goes to 4 operator" << std::endl;
			queue4.push(client);
		}
		else {
			std::cout << "Customer " << client->getOperationNumber() << " " << client->getSuboperationNumber() << " goes to 3 operator" << std::endl;
			queue3.push(client);
		}
	}

	else if ((client->getOperationNumber() % 2 == 0) && (client->getSuboperationNumber() % 2 == 0)) {
		std::cout << "Customer " << client->getOperationNumber() << " " << client->getSuboperationNumber() << " goes to 1 operator" << std::endl;
		queue1.push(client);
	}
	else {
		std::cout << "Customer " << client->getOperationNumber() << " " << client->getSuboperationNumber() << " goes to 2 operator" << std::endl;
		queue2.push(client);
	}

}