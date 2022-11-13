// Charles Tran
// HW6

#include <iostream>
#include "adult.h"


// constructor
Adult::Adult(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv, int *adult, int *people):Person("Adult ",id,b,mutx,cv, adult, people){
}
// destructor
Adult::~Adult(){};

// entry method (function) for adult thread to enter and execute
// it checks to see if the boat is available
// check to see if the passenger seat is taken or not
// once it finishes to travel to mainland, it will notify all other threads
void Adult::run(){
	while (!atMainLand) {
	std::unique_lock<std::mutex> lk(*mutex);
	condVar->wait(lk, [this]{
		return b->isAvailable();});
	if(b->getPassenger() == nullptr){
		getOnPassenger();
		*totalAdult -=1;
		atMainLand=true;
	}
	b->travel();
	lk.unlock();
	condVar->notify_all();
	};		
};
