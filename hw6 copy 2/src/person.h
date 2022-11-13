#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <mutex>
#include <condition_variable>
#include "boat.h"


class Boat;

// this class is base class so child and adult can inherite 
class Person{
public:
	Person(std::string r, int id, Boat* b, std::mutex* l, std::condition_variable* cv, int *totaldAdult, int *totalPeople);
	~Person();
	int getTotalPeopleOnIsland();
	void setTotalPeopleOnIsLand(int newTotalPeople);
	void getOnDriver();
	void getOnPassenger();
	std::string getRole();
	void display(std::string text);
protected:
	std::string role;
	int myId;
	Boat* b;
	bool atMainLand;
	std::mutex* mutex;
	std::condition_variable* condVar;
	int *totalAdult;
	int *totalPeople;
};


#endif
