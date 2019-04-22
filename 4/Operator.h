#pragma once
#include <ctime>
#include <future>
#include <string>
#include <thread>
#include <iostream>
#include "Client.h"

using namespace std;
class Operator
{
private:
	bool isSecond;
	int number;
	int workExperience;
	int workingHours;
	int hours[30] = { 10,10,10,9,9,9,8,8,8,7,7,7,6,6,6,5,5,5,4,4,4,3,3,3,2,2,2,1,1,1 };
public:
	Operator() {
		isSecond = false;
		workExperience = 1 + rand() % 30;
		workingHours = hours[workExperience - 1];
	}

	void setIsActive() {
		if (isSecond == true)
			isSecond = false;
		else
			isSecond = true;
	}

	bool getIsActive() {
		return isSecond;
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

	~Operator();
};

