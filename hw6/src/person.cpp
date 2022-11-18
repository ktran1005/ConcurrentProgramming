#include <iostream>
#include "person.h"



Person::Person(int id, Boat* bt, std::mutex* lk, std::condition_variable* cv)
{
	myId = id;
	b = bt;
	trapped=true;
	lock = lk;
	condval = cv;
}

// Destructor
Person::~Person(){}


void Person::run() {
	while (trapped) {
	std::unique_lock<std::mutex> lk(*lock);
	condval->wait(lk, [this]{
	 	return b->isAvailable();});
	b->display(myId);
	b->goToMainland();
	trapped = false;
	// condval->notify_one();
	};
	
	

}


void Person::printAboutMe(){
	std::cout << myId;
	std::cout << std::endl;
}
