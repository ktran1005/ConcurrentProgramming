#include <iostream>
#include "child.h"

// Constructor
Child::Child(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv, int *adult, int *people):Person("Child ",id,b,mutx,cv, adult, people){
}

// Destructor
Child::~Child(){};


// Entry method for child thread enter and execute
// check to see if the boat is available
// if it is, then check if there are still adults on the island. if adults are still on the island, check if the driver's seat taken or not
// otherwise, child can seat in driver or passenger
void Child::run(){
	while (!atMainLand) {
	std::unique_lock<std::mutex> lk(*mutex);
	condVar->wait(lk, [this]{
		return (b->isAvailable());});
	if (atMainLand)
		goto UNLOCK;

	if (b->getDriver() == nullptr && this != b->getPrevDriver())
		getOnDriver();	
		
	if (*totalAdult == 0 && b->getPassenger() == nullptr && b->getDriver()!= this){
		getOnPassenger();
		atMainLand = true;
	}
	
	b->travel();
	
UNLOCK:
	lk.unlock();
	condVar->notify_all();
	};		
	
}