#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>
#include <mutex>
#include <condition_variable>
#include "boat.h"


class Boat;

//A person has a name and can wear a hat.
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
	void arrive();
protected:
	bool atMainLand;
	std::string role;
	int myId;
	Boat* b;
	std::mutex* mutex;
	std::condition_variable* condVar;
	int *totalAdult;
	int *totalPeople;
};


#endif
