#include "boat.h"
// #include "person.h"
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
	Child* p2 = new Child(0, b, dockLock, dockSignal);
	Child* p3 = new Child(1, b, dockLock, dockSignal);
	Adult* p4 = new Adult(4, b, dockLock, dockSignal);
	Adult* p5 = new Adult(5, b, dockLock, dockSignal);

	myThreads[0] = std::thread([](Child* c){c->run();},p2);
	myThreads[1] = std::thread([](Child* c){c->run();},p3);

	myThreads[2] = std::thread([](Adult* a){a->run();},p4);
	myThreads[3] = std::thread([](Adult* a){a->run();},p5);	

	myThreads[0].join();
	myThreads[1].join();
	myThreads[2].join();
	myThreads[3].join();
	
	// Boat* b = new Boat();
	b->summarizeEvent();
	return 0;
}
