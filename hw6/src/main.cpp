#include "boat.h"
#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>


int seatAvailable = 2;

bool processed = true;
// bool ready = false;

int totalPeople = 2;
int main(int argc, char* argv[]){
	// if (argc !3) {
	// 	std::cout << "Invalid Input" << "\n";
	// }
	// bool processed = true;
	// int child = 3;
	// int adult = 5;
	
	// Person* p1 = new Person("Tuong");
	

	//Make the Locks
	std::mutex* dockLock = new std::mutex();
	std::mutex* travelLock = new std::mutex();
	//Make Condition Variables
	std::condition_variable* dockSignal = new std::condition_variable();
	std::condition_variable* travelSignal = new std::condition_variable();

	std::thread* myThreads = new std::thread[4];
	Boat* b = new Boat();
	// Boat* c = new Boat();
	// Person::seatAvailable = 2;
	Person* p2 = new Person(0, b, dockLock, dockSignal, processed, seatAvailable);
	Person* p3 = new Person(1, b, dockLock, dockSignal, processed, seatAvailable);
	Person* p4 = new Person(4, b, dockLock, dockSignal, processed, seatAvailable);
	Person* p5 = new Person(5, b, dockLock, dockSignal, processed, seatAvailable);

	myThreads[0] = std::thread([](Person* m){m->run();},p2);
	myThreads[1] = std::thread([](Person* m){m->run();},p3);

	myThreads[2] = std::thread([](Person* m){m->run();},p4);
	myThreads[3] = std::thread([](Person* m){m->run();},p5);	

	myThreads[0].join();
	myThreads[1].join();
	myThreads[2].join();
	myThreads[3].join();
	
	// Boat* b = new Boat();
	// b->summarizeEvent();
	return 0;
}
