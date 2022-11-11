#include <iostream>
#include "person.h"



Person::Person(int id, Boat* b, std::mutex* lk, std::condition_variable* cv)
{
	myId = id;
	boat = b;
	trapped=true;
	lock = lk;
	condval = cv;
}

// Destructor
Person::~Person(){}

std::string Person::getName(){
	return name;
}

void Person::run() {
	while (trapped) {
		std::unique_lock<std::mutex> lk(*lock);
		condval->wait(lk, []{
			return boat->isAvailable();
		});
		boat->display();

	}

}


void Person::printAboutMe(){
	std::cout << name;
	// if(myHat!=nullptr){
	// 	std::cout << " has a hat with "
	// 	<< myHat->info();
	// }
	std::cout << std::endl;
}
