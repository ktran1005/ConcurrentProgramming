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
	Person(int id, Boat* b, std::mutex* l, std::condition_variable* cv);
	~Person();
	std::string getName();
	void display();
	virtual void run();
protected:
	std::string name;
	Boat* b;
	std::mutex* mutex;
	std::condition_variable* condVar;
	int myId;
	bool atMainLand;
	
};


#endif
