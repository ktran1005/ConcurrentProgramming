#include <iostream>
#include "child.h"
Child::Child(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv):Person(id,b,mutx,cv){
}

Child::~Child(){};

// std::string Child::getName(){
// 	return "Child "; 
// }

void Child::display(){
	static std::mutex ioLock;
    std::lock_guard<std::mutex> lk(ioLock);
    std::cout << "Child " << myId << " travel to mainland\n";
}

void Child::run(){
	while (!atMainLand) {
	std::unique_lock<std::mutex> lk(*mutex);
	condVar->wait(lk, [this]{
		return b->isAvailable();});
	display();
	b->travel();
	atMainLand = true;
	lk.unlock();
	condVar->notify_one();
	};		
	
}