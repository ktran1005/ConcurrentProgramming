//Mark Boady
//Drexel University 2021

#include "race.h"
#include <thread>
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
//Racer and Game Master Implementations
bool canStartApp = true;
//Simulate the Game Master
void producer(std::queue<std::string>* filesQueue, std::string dirToSearch,bool* donePushingIntoQueue)
{

	// std::string current_directory = std::filesystem::current_path();
	// current_directory = current_directory + "/SomeLocalDir" + dirToSearch;
	// std::cout << "The full path is: " << current_directory << "\n";

	for (const auto &p : std::filesystem::recursive_directory_iterator(dirToSearch))
    {

        std::filesystem::path file = p.path();
        // std::string fileName = file.filename();
        std::string extension = file.extension();
        if (extension == ".cc" || extension == ".c" || extension == ".cpp" || extension == ".h" || extension == ".hpp" || extension == ".pl" || extension == ".sh" || extension == ".py" || extension == ".txt")
        {
            std::string element = file;
            filesQueue->push(element);
        }
    }

	*donePushingIntoQueue = true;
	// std::cout << "done scanning files\n";

}
	
//Simulate one Racer
void worker(std::condition_variable *cv, std::mutex *mutex,std::queue<std::string>* files, bool* donePushingIntoQueue, std::string target)
{
	// while (!canStartApp){};
	std::ifstream myFile;
	// std::cout << "thread starts\n";
	while(*donePushingIntoQueue != true || files->size()!=0){
		std::unique_lock<std::mutex> lk(*mutex);

		cv->wait(lk,[]{
			return canStartApp;}); 
		std::string str;
		if (files->size() == 0){
			goto UNLOCK;
		}
		str = files->front();
		files->pop();
		myFile.open(str);
		if (myFile.is_open()) {
			std::string line;
			int i=0;
			while (getline(myFile, line)) {
				i++;
				if (strstr(line.c_str(), target.c_str()))
					printChar(str, i, line);
			}
			myFile.close();
		}
		// printChar(str);
	UNLOCK:
		lk.unlock();
		cv->notify_all();
	}
}


//Helper for sleeping
void randomSleep(){
	int time2Wait = std::rand()%3;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	std::this_thread::sleep_for(t);
}

//Print a Move
void printChar(std::string str, int i, std::string line){
	static std::mutex ioLock;
	std::lock_guard<std::mutex> lk(ioLock);
	std::cout << "--------" << "\n";
	std::cout << "Thread "<< std::this_thread::get_id() << " found a match." << std::endl;
	std::cout << "File: " << str << "\n";
	std::cout << "Line " << i << ": " << line << "\n";
	std::cout << "--------" << "\n";
	
}
