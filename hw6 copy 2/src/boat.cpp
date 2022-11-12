#include <iostream>
#include "boat.h"
#include <mutex>
#include <chrono>
#include <thread>


Boat::Boat(){
    numOfTravel = 0;
    numOfReturn = 0;
    numOfTwoChildTrip = 0;
    numOfChildAdultTrip = 0;
    numOfOnePersonTrip = 0;
    atIsland = 1;
    //driver = nullptr;
    //passenger = nullptr;
};

void Boat::summarizeEvent(){
    std::cout << "Summary of Events \n";
    
    std::cout << "Boat traveled to the mainland: " << numOfTravel << "\n"; 
    std::cout <<  "Boat returned to the island: " << numOfReturn << "\n";
    std::cout <<  "Boats with 2 children: " << numOfChildAdultTrip << "\n";
    std::cout <<  "Boats with 1 child and 1 adult: " << numOfChildAdultTrip << "\n";
    std::cout <<  "Boats with only 1 person (child or adult): " << numOfOnePersonTrip << "\n";
        // Times adults where the driver: 4
        // Times children where the driver: 11
}

void Boat::loadPeople(Person* Driver,Person* Passenger){
    driver = Driver;
    passenger = Passenger;

}

int Boat::isAvailable() {
    return atIsland;
}

// void Boat::display(Person* p, int id) {
//     static std::mutex ioLock;
//     std::lock_guard<std::mutex> lk(ioLock);
//     std::cout << p->getName() << id << " travel to mainland\n";
// }

void Boat::travel(){
    atIsland = false;
    std::cout << "Boat is traveling from island to mainland  \n"; 

    // std::cout << "Passenger: " << passenger->getName() << "\n"; 
    int time2Wait = std::rand()%6;
    std::chrono::seconds t = std::chrono::seconds(time2Wait);
    std::this_thread::sleep_for(t);
    std::cout << "Boat is traveling from mainland to island  \n"; 
    std::this_thread::sleep_for(t);
    atIsland = true;
    return;
}


