#include <iostream>
#include "child.h"
Child::Child(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv, int *adult, int *people):Person("Child ",id,b,mutx,cv, adult, people){
}

Child::~Child(){};

void Child::run(){
	while (!atMainLand) {
	std::unique_lock<std::mutex> lk(*mutex);
	condVar->wait(lk, [this]{
		return (b->isAvailable());});
	if (b->getDriver() == nullptr)
		getOnDriver();	
		
	if (*totalAdult == 0 && b->getPassenger() == nullptr && b->getDriver()!= this){
		getOnPassenger();
		atMainLand = true;
	}
	
	if (getTotalPeopleOnIsland() == 2)
		atMainLand = true;
	
	b->travel();
	lk.unlock();
	condVar->notify_all();
	};		
	
}