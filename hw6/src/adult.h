#ifndef _ADULT_H_
#define _ADULT_H_
#include <string>
#include <mutex>
#include <condition_variable>
#include "boat.h"


class Boat;

class Adult{
public:
	Adult(int id, Boat* b, std::mutex* l, std::condition_variable* cv, bool processed, int seats);
	~Adult();
	void printAboutMe();
	void run();

private:
	Boat* b;
	std::mutex* lock;
	std::condition_variable* condval;
	int myId;
	bool processed;
	int seats;
};

#endif
