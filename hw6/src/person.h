#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <mutex>
#include <condition_variable>
#include "boat.h"


class Boat;

class Person{
public:
	Person(int id, Boat* b, std::mutex* l, std::condition_variable* cv, bool processed, int seats);
	~Person();
	void printAboutMe();
	void run();

private:
	std::string name;
	Boat* b;
	std::mutex* lock;
	std::condition_variable* condval;
	int myId;
	bool processed;
	int seats;
};

#endif
