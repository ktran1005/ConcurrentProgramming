#include <iostream>
#include "person.h"
// #include <stringstream> 


Person::Person(int id, Boat* bt, std::mutex* m, std::condition_variable* cv)
{
	myId = id;
	b = bt;
	mutex = m;
	condVar = cv;
	atMainLand = false;

}

// Destructor
Person::~Person(){}



// idea: https://www.geeksforgeeks.org/order-constructor-destructor-call-c/

Child::Child(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv):Person(id,b,mutx,cv){
}

Child::~Child(){};

std::string Child::getName(){
		// stringstream ss;
		// ss << myId;
		// string s;
		// s << ss;
	return "Child "; 
}
	
void Child::run(){
	while (atMainLand) {
	std::unique_lock<std::mutex> lk(*mutex);
	condVar->wait(lk, [this]{
		return b->isAvailable();});
	b->display(this,myId);
	b->travel();
	atMainLand = true;
	lk.unlock();
	condVar->notify_one();
	};		
	
}



Adult::Adult(int id, Boat* b, std::mutex* mutx, std::condition_variable* cv):Person(id,b,mutx,cv){
}

Adult::~Adult(){};

std::string Adult::getName(){
	// stringstream ss;
	// ss << myId;
	// string s;
	// s << ss;
	return "Adult "; 
}

void Adult::run(){
	while (atMainLand) {
	std::unique_lock<std::mutex> lk(*mutex);
	condVar->wait(lk, [this]{
		return b->isAvailable();});
	b->display(this,myId);
	b->travel();
	atMainLand = true;
	lk.unlock();
	condVar->notify_one();
	};		
};

// void Person::run() {
	// while (trapped) {
	// std::unique_lock<std::mutex> lk(*lock);
	// condval->wait(lk, [this]{
	//  	return b->isAvailable();});
	// b->display(myId);
	// b->travel();
	// trapped = false;
	// lk.unlock();
	// condval->notify_one();
	// };
// }


