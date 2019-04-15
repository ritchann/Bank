#include <ctime>
#include <iostream>
#include "BankingEngine.h"

using namespace std;
int main() {
	srand(time(0));
	BankingEngine* engine = new BankingEngine();
	engine->start();
	system("pause");
}