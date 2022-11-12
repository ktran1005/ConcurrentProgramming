int seatAvailable = 2;
#include "boat.h"
#include "person.h"
#include "child.h"
#include "adult.h"
#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>




int totalAdult;
int totalPeople;
int main(int argc, char* argv[]){
	// if (argc !3) {
	// 	std::cout << "Invalid Input" << "\n";
	// }
	// bool processed = true;
	// int child = 3;
	// int adult = 5;
	
	// Person* p1 = new Person("Tuong");
	totalAdult = 7;
	// int &n = totalAdult;
	totalPeople	 = 12;

	//Make the Locks
	std::mutex* dockLock = new std::mutex();
	std::mutex* travelLock = new std::mutex();
	//Make Condition Variables
	std::condition_variable* dockSignal = new std::condition_variable();
	std::condition_variable* travelSignal = new std::condition_variable();

	std::thread* myThreads = new std::thread[11];
	Boat* b = new Boat();
	// Boat* c = new Boat();
	// Person::seatAvailable = 2;
	for(int i=0;i<5;i++){
		Child* c = new Child(i, b, dockLock, dockSignal, &totalAdult, &totalPeople);
		myThreads[i] = std::thread([](Child* c){c->run();},c);
	}

	for(int i=5;i<12;i++){
		Adult* a = new Adult(i-5, b, dockLock, dockSignal, &totalAdult, &totalPeople);
		myThreads[i] = std::thread([](Adult* a){a->run();},a);

	}

	// Child* p3 = new Child(1, b, dockLock, dockSignal, &totalAdult, &totalPeople);
	// Adult* p4 = new Adult(4, b, dockLock, dockSignal, &totalAdult, &totalPeople);
	// Adult* p5 = new Adult(5, b, dockLock, dockSignal, &totalAdult, &totalPeople);

	// myThreads[0] = std::thread([](Child* c){c->run();},p2);
	// myThreads[1] = std::thread([](Child* c){c->run();},p3);

	// myThreads[2] = std::thread([](Adult* a){a->run();},p4);
	// myThreads[3] = std::thread([](Adult* a){a->run();},p5);	
	for (int i=0;i<12;i++){
		myThreads[i].join();
	}
	// myThreads[0].join();
	// myThreads[1].join();
	// myThreads[2].join();
	// myThreads[3].join();
	
	// Boat* b = new Boat();
	b->summarizeEvent();
	return 0;
}
