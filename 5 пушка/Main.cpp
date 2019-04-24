#include <thread>
#include <ctime>
#include <random>
#include "BankManagmentSystem.h"


int main() {
	BankManagmentSystem* bms = new BankManagmentSystem();
	srand(time(0));
	bms->start();
	system("pause");
	return 0;
}