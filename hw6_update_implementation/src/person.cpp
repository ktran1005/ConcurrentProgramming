#include <iostream>
#include <chrono>
#include <thread>
#include "person.h"
// #include <stringstream> 


Person::Person(std::string r, int id, Boat* bt, std::mutex* m, std::condition_variable* cv, int *adult, int *people)
{
	role = r;
	myId = id;
	b = bt;
	mutex = m;
	condVar = cv;
	atMainLand = false;
	totalAdult = adult;
	totalPeople = people;

}

int Person::getTotalPeopleOnIsland() {
	return *totalPeople;
}

void Person::setTotalPeopleOnIsLand(int newTotalPeople) {
	*totalPeople = newTotalPeople;
}

// Destructor
Person::~Person(){}

std::string Person::getRole(){
	return role;
};

void Person::display(std::string text,bool displayrole){
    static std::mutex ioLock;
    std::lock_guard<std::mutex> lk(ioLock);
	if (displayrole)
		std::cout << getRole() << myId << " "<< text <<"\n";
	else
		std::cout << text <<"\n";

}

void Person::getOnDriver(){
	b->loadDriver(this);
	display("got into the driver's seat of the boat.",true);
}

void Person::getOnPassenger(){
	b->loadPassenger(this);
	display("got into the passenger seat of the boat.",true);
}

void Person::arrive(){
	atMainLand = true;
}

void Person::sleepRand(int maxTime){
	int time2Wait  = std::rand()%(maxTime+1);
	std::chrono::seconds t = std::chrono::seconds(time2Wait);
	std::this_thread::sleep_for(t);
}

void Person::notifyBoatToTravel(){
	return;
};