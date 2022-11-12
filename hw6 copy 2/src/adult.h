#ifndef _ADULT_H_
#define _ADULT_H_
#include <string>
#include <mutex>
#include <condition_variable>
#include "person.h"


class Adult : public Person{
public:
	Adult(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv);
	~Adult();
	// std::string getName();
	void display();
	void run();
};

#endif
