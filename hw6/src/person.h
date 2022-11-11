#ifndef _PERSON_H_
#define _PERSON_H_
#include <string>


class Person{
private:
	std::string name;
public:
	Person(std::string n);
	std::string getName();
	void printAboutMe();
};

#endif
