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
	virtual std::string getName();
protected:
	std::string name;
	Boat* b;
	std::mutex* mutex;
	std::condition_variable* condVar;
	int myId;
	bool atMainLand;
	
};


class Adult : public Person{
public:
	Adult(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv);
	~Adult();
	std::string getName();
	void run();
};


class Child: public Person{
public:
	Child(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv);
	~Child();
	std::string getName();
	void run();
};

#endif
