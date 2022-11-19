//Mark Boady
//Drexel University 2021

//Functions for Simulating the race

#ifndef _RACE_H_
#define _RACE_H_

#include <queue>
#include <thread>

//Simulate the Game Master
void producer(std::queue<char>* chars,bool* donePushingIntoQueue);

//Simulate one Racer
void worker(
	std::condition_variable *cv,
	std::mutex *mutex,
	std::queue<char>* chars,
	bool* donePushingIntoQueue);
	
//Sleep between 0 and 2 seconds
void randomSleep();

//Print a Move
void printChar(char ch);

#endif
