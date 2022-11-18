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
    void loadPeople(Person* Driver,Person* Passenger);
    void goToMainland();
    int isAvailable();
    void display(int id);
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