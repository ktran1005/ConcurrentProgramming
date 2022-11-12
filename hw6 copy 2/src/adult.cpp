// #include <iostream>
// #include "adult.h"



// Adult::Adult(int id, Boat* bt, std::mutex* lk, std::condition_variable* cv, bool proc, int num_seats)
// {
// 	myId = id;
// 	b = bt;
// 	// trapped=true;
// 	lock = lk;
// 	condval = cv;
// 	processed = proc;
// 	seats = num_seats;
// }

// // Destructor
// Adult::~Adult(){}


// void Adult::run() {
// 	// while (trapped) {
// 	std::unique_lock<std::mutex> lk(*lock);
// 	condval->wait(lk, [this]{
// 	 	return seats;});
	
// 	b->display(myId);
// 	// printf("Cur seats: %d\n", seats)''

// }


// void Adult::printAboutMe(){
// 	std::cout << myId;
// 	std::cout << std::endl;
// }
