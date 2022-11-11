#include <iostream>
#include "boat.h"

Boat::Boat(){
    numOfTravel = 0;
    numOfReturn = 0;
    numOfTwoChildTrip = 0;
    numOfChildAdultTrip = 0;
    numOfOnePersonTrip = 0;
    atIsland = 0;
    // driver = nullptr;
    // passenger = nullptr;
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


void Boat::goToIsland(){
    std::cout << "Driver: " << driver->getName() << "\n"; 
    std::cout << "Passenger: " << passenger->getName() << "\n"; 
}