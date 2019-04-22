#include <thread>
#include "BankManagmentSystem.h"


int main() {
	BankManagmentSystem* bms = new BankManagmentSystem();
	bms->start();
	system("pause");
	return 0;
}