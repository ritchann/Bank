#pragma once
#include <ctime>
#include <future>
#include <string>
#include <thread>
#include <iostream>

using namespace std;
class Operator
{
private:
	thread th();
	bool isActive;
	int number;
	int workExperience;
	int workingHours;
	int hours[30] = { 10,10,10,9,9,9,8,8,8,7,7,7,6,6,6,5,5,5,4,4,4,3,3,3,2,2,2,1,1,1 };
public:

	Operator() {
		isActive = false;
		workExperience = 1 + rand() % 30;
		workingHours = hours[workExperience - 1];
	}

	void setIsActive() {
		if (isActive == true)
			isActive = false;
		else
			isActive = true;
	}

	bool getIsActive() {
		return isActive;
	}

	void setNumber(int newNumber){
		number = newNumber;
	}

	int getNumber() {
		return number;
	}

	int getWorrkingHours() {
		return workingHours;
	}

	void Work(int number, int subnumber);

	static void Result(int number, int subnumber);

	~Operator();
};

