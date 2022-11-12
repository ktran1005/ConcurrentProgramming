#include <iostream>
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

void Person::display(std::string text){
    static std::mutex ioLock;
    std::lock_guard<std::mutex> lk(ioLock);
    std::cout << getRole() << myId << " "<< text <<"\n";
}

void Person::getOnDriver(){
	b->loadDriver(this);
	display("got into the driver's seat of the boat.");
}

void Person::getOnPassenger(){
	b->loadPassenger(this);
	display("got into the passenger seat of the boat.");
}


