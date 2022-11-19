//Mark Boady
//Drexel University 2021

//Race some cars!

#include <iostream>
#include <thread>
#include <queue>
#include "race.h"
#include <condition_variable>
#include <filesystem>
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

	// int racers = 3;
	int racers = std::thread::hardware_concurrency();
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
	
	std::string myDirectory = "/gcc";
	std::string target = "<thread>";

	//Make two queues
	std::queue<std::string>* fileList = new std::queue<std::string>();
	std::queue<std::thread::id>* workers = new std::queue<std::thread::id>();
	
	std::cout << "!---- Search Started ----! "<< "\n";
	std::cout << "Target Folder: " << myDirectory << "\n";
	std::cout << "Target Text: " << target << "\n";


	//Start the racers
	T[racers] = std::thread(producer,fileList, myDirectory, &done);
	for(int i=0; i < racers; i++){
		T[i] = std::thread(worker,sharedCondVar,sharedMutex,fileList,&done, target);
	}
	//Join Everything
	for(int i=0; i < racers+1; i++){
		T[i].join();
	}
	return 0;
}
