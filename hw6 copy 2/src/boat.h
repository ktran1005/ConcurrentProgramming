#ifndef _BOAT_H_
#define _BOAT_H_
#include <string>
#include "person.h"

class Person;

class Boat{
public:
    Boat();
    ~Boat();
    void summarizeEvent();
    void loadDriver(Person* Driver);
    void loadPassenger(Person* Passenger);
    void travel();
    int isAvailable();
    Person* getDriver();
    Person* getPassenger();
    
private:
    int numOfTravel;
    int numOfReturn;
    int numOfTwoChildTrip;
    int numOfChildAdultTrip;
    int numOfOnePersonTrip;
    bool atIsland;
    Person* driver;
    Person* passenger;
};

#endif