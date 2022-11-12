#ifndef _CHILD_H_
#define _CHILD_H_
#include <string>
#include <mutex>
#include <condition_variable>
#include "person.h"

class Child: public Person{
public:
	Child(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv);
	~Child();
	std::string getName();
	void run();
};

#endif