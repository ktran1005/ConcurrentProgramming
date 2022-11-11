#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <mutex>
#include <condition_variable>
#include "boat.h"

//Tell the compiler hats are coming
// #include "hat.h"
class Boat;

//A person has a name and can wear a hat.
class Person{
public:
	Person(int id, Boat* b, std::mutex* l, std::condition_variable* cv);
	~Person();
	// std::string getName();
	// void addHat(Hat* h);
	void printAboutMe();
	void run();
private:
	std::string name;
	Boat* b;
	std::mutex* lock;
	std::condition_variable* condval;
	int myId;
	bool trapped;
};

#endif
