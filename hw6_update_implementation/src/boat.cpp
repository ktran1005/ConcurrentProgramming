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
    numOfChildDriverTrip = 0;
    numOfAdultDriverTrip = 0;
    atIsland = true;
    driver = nullptr;
    passenger = nullptr;
};

void Boat::summarizeEvent(){
    std::cout << "Summary of Events \n";
    
    std::cout << "Boat traveled to the mainland: " << numOfTravel << "\n"; 
    std::cout <<  "Boat returned to the island: " << numOfTravel - 1  << "\n";
    std::cout <<  "Boats with 2 children: " << numOfChildAdultTrip << "\n";
    std::cout <<  "Boats with 1 child and 1 adult: " << numOfTwoChildTrip << "\n";
    std::cout <<  "Boats with only 1 person (child or adult): " << numOfOnePersonTrip << "\n";
    std::cout <<  "Times adults where the driver: " << numOfAdultDriverTrip<< "\n";
    std::cout <<  "Times children where the driver: " << numOfChildDriverTrip << "\n";
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

Person* Boat::getPrevDriver() {
    return prevDriver;
}


void Boat::tracking(Person* driver, Person* passenger) {
    numOfTravel++;
    if (driver->getRole().compare("Child ") == 0){
        numOfChildDriverTrip++;
        if (passenger->getRole().compare("Child ") == 0)
            numOfTwoChildTrip++;
        else
            numOfChildAdultTrip++;
    }
    else{
        numOfAdultDriverTrip++;
        if (passenger->getRole().compare("Child ") == 0)
            numOfChildAdultTrip++;
            
    }

    if (passenger == nullptr)
        numOfOnePersonTrip++;
}

void Boat::travel(){
    if (driver != nullptr && passenger != nullptr)
    {
        atIsland = false;
        std::cout << "Boat is traveling from island to mainland  \n"; 
        int time2Wait = std::rand()%5+1;
        std::chrono::seconds t = std::chrono::seconds(time2Wait);
        std::this_thread::sleep_for(t);
        std::cout << "Boat is traveling from mainland to island \n\n"; 
        std::this_thread::sleep_for(t);
        tracking(driver,passenger);
        passenger->arrive();
        int curTotalPeople = driver->getTotalPeopleOnIsland()-1;
        if (curTotalPeople == 1){
            driver->arrive();
        }
        driver->setTotalPeopleOnIsLand(curTotalPeople);
        std::cout << "Total people on island: " << curTotalPeople << "\n\n";
        prevDriver = driver;
        driver = nullptr;
        passenger = nullptr; 
        atIsland = true;  
    }
}

bool Boat::readyToGo(){
    return driver != nullptr && passenger != nullptr;
}

void Boat::goToMainLand(){
    atIsland = false;
    tracking(driver,passenger);
    passenger->arrive();
    int curTotalPeople = driver->getTotalPeopleOnIsland()-1;
    if (curTotalPeople == 1){
        driver->arrive();
    }
    driver->setTotalPeopleOnIsLand(curTotalPeople);
};
void Boat::goToIsland(){
    prevDriver = driver;
    driver = nullptr;
    passenger = nullptr; 
    atIsland = true;  
};

