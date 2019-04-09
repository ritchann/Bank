#include "BankingEngine.h"
#include <future>
#include <thread>

void BankingEngine::start() {
	while (!clients.empty()) {
		operators[clients[0]->getOperationNumber()]->Work(clients[0]->getOperationNumber(), clients[0]->getSuboperationNumber());
		clients.erase(clients.begin());
	}
}

BankingEngine::~BankingEngine()
{
}
