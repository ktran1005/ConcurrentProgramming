#include <iostream>
#include "person.h"
// #include <stringstream> 


Person::Person(int id, Boat* bt, std::mutex* m, std::condition_variable* cv, int *adult, int *people)
{
	myId = id;
	b = bt;
	mutex = m;
	condVar = cv;
	atMainLand = false;
	totalAdult = adult;
	totalPeople = people;

}

int Person::getTotalPeople() {
	return *totalPeople;
}

void Person::setTotalPeople(int newTotalPeople) {
	*totalPeople = newTotalPeople;
}


// Destructor
Person::~Person(){}

// std::string getName(){
// 	return "Person ";
// }

// void Person::display() {
//     static std::mutex ioLock;
//     std::lock_guard<std::mutex> lk(ioLock);
//     std::cout << "Person " << myId << " travel to mainland\n";
// }

// void Person::run(){
// 	return;
// }

// idea: https://www.geeksforgeeks.org/order-constructor-destructor-call-c/




// void Person::run() {
	// while (trapped) {
	// std::unique_lock<std::mutex> lk(*lock);
	// condval->wait(lk, [this]{
	//  	return b->isAvailable();});
	// b->display(myId);
	// b->travel();
	// trapped = false;
	// lk.unlock();
	// condval->notify_one();
	// };
// }


