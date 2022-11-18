#include "boat.h"
#include "person.h"
int main(int argv, char** argc){
	Person* p1 = new Person("Tuong");
	Person* p2 = new Person("Khanh");
	// b->goToIsland(p1,p2);
	Boat* b = new Boat();
	b->loadPeople(p1,p2);
	b->goToIsland();
	b->summarizeEvent();

	return 0;
}
