#pragma once
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include "Client.h"

class BankManagmentSystem {
public:
	BankManagmentSystem() {};

	void start();
	static void generateClients();
	static void processClients();

	static void chooseOperator(Client* client);
	static void Work(std::queue<Client*> *);
};
