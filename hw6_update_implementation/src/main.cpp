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
int totalChild;
int totalPeople;
int main(int argc, char* argv[]){
	// if (argc !3) {
	// 	std::cout << "Invalid Input" << "\n";
	// }
	// bool processed = true;
	totalChild = 7;
	totalAdult = 9;
	totalPeople = totalChild + totalAdult;
	// Person* p1 = new Person("Tuong");
	// totalAdult = 7;
	// int &n = totalAdult;
	// totalPeople	 = 12;

	//Make the Locks
	std::mutex* sharedMutex= new std::mutex();
	// std::mutex* travelLock = new std::mutex();
	//Make Condition Variables
	std::condition_variable* sharedCondVar = new std::condition_variable();
	// std::condition_variable* travelSignal = new std::condition_variable();

	std::thread* myThreads = new std::thread[totalPeople];
	Boat* b = new Boat();

	for(int i=0;i<totalChild;i++){
		Child* c = new Child(i, b,sharedMutex,sharedCondVar, &totalAdult, &totalPeople);
		myThreads[i] = std::thread([](Child* c){c->run();},c);
	}

	for(int i=totalChild;i<totalPeople;i++){
		Adult* a = new Adult(i-totalChild, b,sharedMutex,sharedCondVar, &totalAdult, &totalPeople);
		myThreads[i] = std::thread([](Adult* a){a->run();},a);
	}

	for (int i=0;i<totalPeople;i++){
		myThreads[i].join();
	}
	
	b->summarizeEvent();
	return 0;
}
