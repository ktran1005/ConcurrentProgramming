//Mark Boady
//Drexel University 2021

//Race some cars!

#include <iostream>
#include <thread>
#include <queue>
#include "race.h"
#include <condition_variable>
// bool canStart;
int main(int argv, char** argc){
	//Sanity Check on inputs
	// if(argv!=2){
	// 	std::cout << "Number of racers required."
	// 		<< std::endl;
	// }
	// int temp =atoi(argc[1]);
	// if(temp < 1){
	// 	std::cout << "Not Enough racers." << std::endl;
	// }

	int racers = 3;
	//Get ready
	std::cout << "Starting Race with "
		<< racers
		<< " threads."
		<< std::endl;
	//Make threads
	std::thread* T = new std::thread[racers+1];
	
	std::mutex* sharedMutex= new std::mutex();

	std::condition_variable* sharedCondVar = new std::condition_variable();

	bool done = false;
	bool canStart = false;
	
	//Make two queues
	std::queue<char>* charList = new std::queue<char>();
	std::queue<std::thread::id>* workers = new std::queue<std::thread::id>();
	
	//Start the racers

	T[racers] = std::thread(producer,charList,&done);
	for(int i=0; i < racers; i++){
		T[i] = std::thread(worker,sharedCondVar,sharedMutex,charList,&done);
	}
	//Join Everything
	for(int i=0; i < racers+1; i++){
		T[i].join();
	}
	return 0;
}
