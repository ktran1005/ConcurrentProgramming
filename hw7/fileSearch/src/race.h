//Mark Boady
//Drexel University 2021

//Functions for Simulating the race

#ifndef _RACE_H_
#define _RACE_H_

#include <queue>
#include <thread>
#include <condition_variable>
#include <cstring>

//Simulate the Game Master
void producer(std::queue<std::string>* filesQueue, std::string dirToSearch,bool* donePushingIntoQueue);

//Simulate one Racer
void worker(std::condition_variable *cv, std::mutex *mutex,std::queue<std::string>* files, bool* donePushingIntoQueue, std::string target);
	
//Sleep between 0 and 2 seconds
void randomSleep();

//Print a Move
void printChar(std::string str, int i, std::string line);

#endif
