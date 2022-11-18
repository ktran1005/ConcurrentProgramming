// Charles Tran

// Adult will always be passenger to prevent unsolvable case


#ifndef _ADULT_H_
#define _ADULT_H_
#include <string>
#include <mutex>
#include <condition_variable>
#include "person.h"


class Adult : public Person{
public:
	Adult(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv, int *adult, int *people);
	~Adult();
	void run();
};

#endif
