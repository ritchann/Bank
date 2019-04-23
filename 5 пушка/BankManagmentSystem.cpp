#include "BankManagmentSystem.h"

std::mutex mutex;
std::mutex mutex1;

std::condition_variable cond1;
std::condition_variable cond2;

std::queue<Client*> queue;

std::queue<Client*> * queue1;
std::queue<Client*> * queue2;
std::queue<Client*> * queue3;
std::queue<Client*> * queue4;

int maximum_capacity = 5;
int capacity = 10;

std::chrono::duration<double> time_span;

void BankManagmentSystem::start() {
	queue1 = new std::queue<Client*>;
	queue2 = new std::queue<Client*>;
	queue3 = new std::queue<Client*>;
	queue4 = new std::queue<Client*>;

	std::thread Client(generateClients);
	std::thread Operator(processClients);

	std::thread Operator1(Work, std::ref(queue1)); // основной не профи (операция 2,2 и 4,4 для профи, остальные не для профи)
	std::thread Operator2(Work, std::ref(queue2)); // основной профи
	std::thread Operator3(Work, std::ref(queue3)); // неосновной не профи
	std::thread Operator4(Work, std::ref(queue4)); // неосновной профи

	Client.join();
	Operator.join();

	Operator1.join();
	Operator2.join();
	Operator3.join();
	Operator4.join();

}

void BankManagmentSystem::generateClients() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

void BankManagmentSystem::Work(std::queue<Client*> * q) {
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
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			break;
		case 2:
			switch (client->getSuboperationNumber())
			{
			case 1:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				break;
			case 2:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
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
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				break;
			case 2:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
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
				std::this_thread::sleep_for(std::chrono::milliseconds(5));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
				break;
			case 2:
				time_span = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - client->getTime());
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
				std::cout << "Customer's operation number " << client->getOperationNumber() << " " << client->getSuboperationNumber() <<
					" finished processing with waiting time " << time_span.count() << " seconds" << std::endl;
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