#include <iostream>
#include "person.h"



Person::Person(int id, Boat* bt, std::mutex* lk, std::condition_variable* cv, bool proc, int num_seats)
{
	myId = id;
	b = bt;
	// trapped=true;
	lock = lk;
	condval = cv;
	processed = proc;
	seats = num_seats;
}

// Destructor
Person::~Person(){}


void Person::run() {
	// while (trapped) {
	std::unique_lock<std::mutex> lk(*lock);
	condval->wait(lk, [this]{
	 	return seats;});
	
	b->display(myId);
	// printf("Cur seats: %d\n", seats)''

}


void Person::printAboutMe(){
	std::cout << myId;
	std::cout << std::endl;
}
