#include "Operator.h"
#include <mutex>
#include <chrono>

std::mutex g_lock;

void Operator::Work(int number, int subnumber) {
	thread th(Result, number, subnumber);
	this_thread::sleep_for(chrono::seconds(workingHours));
	th.join();
}

void Operator::Result(int number, int subnumber) {
	switch (number) {
	case 1:
		cout << "Credit is issued \n";
		break;
	case 2:
		switch (subnumber)
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
		switch (subnumber)
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
		switch (subnumber)
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
}


Operator::~Operator(){

}
