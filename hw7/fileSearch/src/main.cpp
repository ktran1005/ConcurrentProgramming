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
int main(int argc, char** argv){


	//Sanity Check on inputs
	// if (argc  < 2 ){
	// 	std::cout << "The program needs at least 2 inputs to run the program."
	// 		<< std::endl;
	// }

	// std::string myDirectory;
	// if (argc == 2) {
	// 	myDirectory = std::filesystem::current_path();
	// }

	// if (argc == 3) {
	// 	myDirectory = std::filesystem::current_path();
	// 	myDirectory += argv[2];
	// }

	std::string myDirectory = std::filesystem::current_path();
	myDirectory += "/test_folder"; 
	std::string target = "thread";

	int racers = std::thread::hardware_concurrency();

	//Get ready
	// std::cout << "Starting Race with "
	// 	<< racers
	// 	<< " threads."
	// 	<< std::endl;

	//Make threads
	std::thread* T = new std::thread[racers+1];
	
	std::mutex* sharedMutex= new std::mutex();

	std::condition_variable* sharedCondVar = new std::condition_variable();

	bool done = false;
	bool canStart = false;
	
	// std::string myDirectory = "/gcc";
	// std::string myDirectory = std::filesystem::current_path();
	// myDirectory += "/test_folder"; 
	// std::string target = "thread";

	//Make two queues
	std::queue<std::string>* fileList = new std::queue<std::string>();
	std::queue<std::thread::id>* workers = new std::queue<std::thread::id>();
	
	std::cout << "!---- Search Started ----! "<< "\n";
	std::cout << "Target Folder: " << myDirectory << "\n";
	std::cout << "Target Text: " << target << "\n";
	// std::cout << "Target Text: " << argv[2] << "\n";
	std::cout << "Using a Pool of " << racers << " to search." << "\n";

	//Start the racers
	T[racers] = std::thread(producer,fileList, myDirectory, &done);
	for(int i=0; i < racers; i++){
		T[i] = std::thread(worker,sharedCondVar,sharedMutex,fileList,&done, target);
	}
	//Join Everything
	for(int i=0; i < racers+1; i++){
		T[i].join();
	}

	std::cout << "!---- Search Complete ----!" << "\n";

	return 0;
}
