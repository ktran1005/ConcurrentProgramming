#include <iostream>
#include "adult.h"



Adult::Adult(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv, int *adult, int *people):Person("Adult ",id,b,mutx,cv, adult, people){
}

Adult::~Adult(){};


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
