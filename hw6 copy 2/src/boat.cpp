#include <iostream>
#include "boat.h"
#include <mutex>
#include <chrono>
#include <thread>

// constructor
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

// method to print statistics of the program
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

//Print Out with a lock
void Boat::display(std::string text){
	static std::mutex ioLock;
	std::lock_guard<std::mutex> lk(ioLock);
    std::cout << "Boat "
        << text << "."
        << std::endl;
}


// Setter to set child as driver
void Boat::loadDriver(Person* Driver){
    driver = Driver;
}

// Setter to set adult and child as passenger
void Boat::loadPassenger(Person* Passenger){
    passenger = Passenger;
}

// check to see if boat is available
int Boat::isAvailable() {
    return atIsland;
}

// check who is the driver
Person* Boat::getDriver() {
    return driver;
}

// check who is the passenger
Person* Boat::getPassenger() {
    return passenger;
}

// getter to get the previous driver
Person* Boat::getPrevDriver() {
    return prevDriver;
}

// this method checks who are on the boat when traveling from island to mainland
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

// method to sleep between 1-4 seconds
void Boat::sleepRand() {
    int time2Wait = std::rand()%5+1;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	std::this_thread::sleep_for(t);
    return;
}

// this method will do the travel from island to mainland and vice versa
// and it only runs when driver and passenger are all set
// once driver and passenger are taken, it will sleep between 1-4 second demonstrate from island to mainland and vice versa
void Boat::travel(){
    if (driver != nullptr && passenger != nullptr)
    {
        atIsland = false;
        display("is traveling from island to mainland");
        sleepRand(); 
        display("is traveling from mainland to island");
        sleepRand();
        tracking(driver,passenger);
        passenger->arrive();
        // decrease the number of people on the island
        int curTotalPeople = driver->getTotalPeopleOnIsland()-1;
        if (curTotalPeople == 1){
            driver->arrive();
        }
        driver->setTotalPeopleOnIsLand(curTotalPeople);
        // reset the driver, passenger and atIsland 
        prevDriver = driver;
        driver = nullptr;
        passenger = nullptr;         
        atIsland = true;  
    }
}


