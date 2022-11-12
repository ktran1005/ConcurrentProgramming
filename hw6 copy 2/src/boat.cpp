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
    atIsland = true;
    driver = nullptr;
    passenger = nullptr;
};

void Boat::summarizeEvent(){
    std::cout << "Summary of Events \n";
    
    std::cout << "Boat traveled to the mainland: " << numOfTravel << "\n"; 
    std::cout <<  "Boat returned to the island: " << numOfReturn << "\n";
    std::cout <<  "Boats with 2 children: " << numOfChildAdultTrip << "\n";
    std::cout <<  "Boats with 1 child and 1 adult: " << numOfChildAdultTrip << "\n";
    std::cout <<  "Boats with only 1 person (child or adult): " << numOfOnePersonTrip << "\n";

}

void Boat::loadDriver(Person* Driver){
    driver = Driver;
}

void Boat::loadPassenger(Person* Passenger){
    passenger = Passenger;
}

int Boat::isAvailable() {
    return atIsland;
}

Person* Boat::getDriver() {
    return driver;
}

Person* Boat::getPassenger() {
    return passenger;
}



// void Boat::display(Person* p, int id) {
//     static std::mutex ioLock;
//     std::lock_guard<std::mutex> lk(ioLock);
//     std::cout << p->getName() << id << " travel to mainland\n";
// }

void Boat::travel(){
    if (driver != nullptr && passenger != nullptr)
    {
        atIsland = false;
        std::cout << "Boat is traveling from island to mainland  \n"; 
        int time2Wait = std::rand()%5+1;
        std::chrono::seconds t = std::chrono::seconds(time2Wait);
        std::this_thread::sleep_for(t);
        std::cout << "Boat is traveling from mainland to island  \n"; 
        std::this_thread::sleep_for(t);
        atIsland = true;
        passenger->atMainLand = true;
        // if (driver->getTotalPeople() == 2){
        //     driver->atMainLand = true;
        //     atIsland = false;
        // }     
        int curTotalPeople = driver->getTotalPeople()-1;
        std::cout <<"People on island: " << curTotalPeople << "\n";
        driver->setTotalPeople(curTotalPeople);        
        driver = nullptr;
        passenger = nullptr;
    }
}


