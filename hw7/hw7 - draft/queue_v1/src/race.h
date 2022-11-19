//Mark Boady
//Drexel University 2021

//Functions for Simulating the race

#ifndef _RACE_H_
#define _RACE_H_

#include <queue>
#include <thread>
//Simulate the Game Master
void gameMaster(
	std::condition_variable cv,
	std::mutex lock,
	std::queue<char>* chars,
	std::queue<std::thread::id>* workers,
	bool* done)
	
//Simulate one Racer
void racer(
	std::condition_variable cv,
	std::mutex lock,
	std::queue<char>* chars,
	std::queue<std::thread::id>* workers,
	bool* done);
	
//Sleep between 0 and 2 seconds
void randomSleep();

//Print a Move
void printChar(char ch);

#endif
