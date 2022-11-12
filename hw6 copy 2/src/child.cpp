#include <iostream>
#include "child.h"
Child::Child(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv, int adult, int child):Person(id,b,mutx,cv, adult, child){
}

Child::~Child(){};

// std::string Child::getName(){
// 	return "Child "; 
// }

void Child::display(std::string text){
	static std::mutex ioLock;
    std::lock_guard<std::mutex> lk(ioLock);
    std::cout << "Child " << myId << " " <<text << "\n";
}

void Child::getOnDriver(){
	b->loadDriver(this);
	display("got into the driver's seat of the boat.");
}

void Child::getOnPassenger(){
	b->loadPassenger(this);
	display("got into the passenger seat of the boat.");
}

void Child::run(){
	while (!atMainLand) {
	std::unique_lock<std::mutex> lk(*mutex);
	condVar->wait(lk, [this]{
		return b->isAvailable();});
	getOnDriver();
	b->travel();
	if (totalChild > 0)
		atMainLand = true;
	lk.unlock();
	condVar->notify_all();
	};		
	
}