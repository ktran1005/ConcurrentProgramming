#include <iostream>
#include "adult.h"



Adult::Adult(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv):Person(id,b,mutx,cv){
}

Adult::~Adult(){};

// std::string Adult::getName(){
// 	return "Adult "; 
// }

void Adult::display(){
	static std::mutex ioLock;
    std::lock_guard<std::mutex> lk(ioLock);
    std::cout << "Adult " << myId << " travel to mainland\n";
}


void Adult::run(){
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
};
