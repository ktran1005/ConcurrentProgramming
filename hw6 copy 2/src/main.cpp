#include "boat.h"
#include "person.h"
#include "child.h"
#include "adult.h"
#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>


// global variable
int totalAdult;
int totalChild;
int totalPeople;


int main(int argc, char* argv[]){

	// check to see if user provides enough arguments	
	if (argc != 3) {
		std::cout << "Invalid Input. The program needs 3 arguments to run" << "\n";
		return 1;
	}

	// store input as string
	std::string numberOfAdult(argv[1]);
	std::string numberOfChild(argv[2]);

	// error checking on bad command line arguments
	try {
		totalAdult = stoi(numberOfAdult);
	} catch (std::invalid_argument e) {
		std::cout << "number of adult is not a number" << std::endl;
		return 2;
	}

	try {
		totalChild = stoi(numberOfChild);
	} catch (std::invalid_argument e) {
		std::cout << "number of adult is not a number" << std::endl;
		return 3;
	}

	// calculate total people on the island
	totalPeople = totalChild + totalAdult;

	//Make the Locks
	std::mutex* sharedMutex= new std::mutex();
	// Make conditonal variable
	std::condition_variable* sharedCondVar = new std::condition_variable();

	// create an array of thread
	std::thread* myThreads = new std::thread[totalPeople];
	// create a boat instance
	Boat* b = new Boat();

	// Assign each child thread
	for(int i=0;i<totalChild;i++){
		Child* c = new Child(i, b,sharedMutex,sharedCondVar, &totalAdult, &totalPeople);
		myThreads[i] = std::thread([](Child* c){c->run();},c);
	}

	// Assign each adult thread
	for(int i=totalChild;i<totalPeople;i++){
		Adult* a = new Adult(i-totalChild, b,sharedMutex,sharedCondVar, &totalAdult, &totalPeople);
		myThreads[i] = std::thread([](Adult* a){a->run();},a);
	}

	// Join the threads
	for (int i=0;i<totalPeople;i++){
		myThreads[i].join();
	}
	
	// Print out the summary of event
	b->summarizeEvent();
	return 0;
}
