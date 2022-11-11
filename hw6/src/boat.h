#ifndef _BOAT_H_
#define _BOAT_H_
#include <string>

class Boat{
public:
    Boat();
    ~Boat();
    void summaryEvent();
private:
    int numOfTravel;
    int numOfReturn;
    int numOfTwoChildTrip;
    int numOfChildAdultTrip;
    int numOfOnePersonTrip;
    bool atIsland;
};

#endif