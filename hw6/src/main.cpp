#include "boat.h"
#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>




int main(int argc, char* argv[]){
	// if (argc !3) {
	// 	std::cout << "Invalid Input" << "\n";
	// }
	
	// int child = 3;
	// int adult = 5;
	
	// Person* p1 = new Person("Tuong");
	

	//Make the Locks
	std::mutex* dockLock = new std::mutex();
	std::mutex* travelLock = new std::mutex();
	//Make Condition Variables
	std::condition_variable* dockSignal = new std::condition_variable();
	std::condition_variable* travelSignal = new std::condition_variable();

	std::thread* myThreads = new std::thread[2];
	Boat* b = new Boat();
	
	Person* p2 = new Person(0, b, dockLock, dockSignal);
	myThreads[0] = std::thread([](Person* m){m->run();},p2);


	
	
	// Boat* b = new Boat();
	// b->summarizeEvent();
	return 0;
}
