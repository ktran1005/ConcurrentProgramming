//Mark Boady
//Drexel University 2021

#include "race.h"
#include <thread>
#include <iostream>

//Racer and Game Master Implementations
bool canStartApp = true;
//Simulate the Game Master
void producer(std::queue<char>* chars,bool* donePushingIntoQueue)
{
	// canStartApp = true;

	FILE *fp;
    char ch;
    int n;
    // printf("Enter file Name :");
    // gets(fname);
    
	char fname[20] = "./bin/file.md"; 
    fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("file can't be opened");
        exit(0);
    }
	std::cout << "open file now\n";
    fseek(fp,0,0);
    ch=fgetc(fp);
	
    while(ch!=EOF){
		chars->push(ch);
        ch=fgetc(fp);
        }
    fclose(fp); 
	*donePushingIntoQueue = true;
	std::cout << "done scanning characters\n";

}
	
//Simulate one Racer
void worker(std::condition_variable *cv,std::mutex *mutex,std::queue<char>* chars,bool* donePushingIntoQueue)
{
	// while (!canStartApp){};
	std::cout << "thread starts\n";
	while(*donePushingIntoQueue != true || chars->size()!=0){
		// std::cout << "got in while loop\n";
		std::unique_lock<std::mutex> lk(*mutex);

		cv->wait(lk,[]{
			// std::cout << "Yes I was called\n";
			// std::cout << canStartApp << "\n";
			return canStartApp;}); 
		// std::cout << "got after cv\n";
		char ch;
		if (chars->size() == 0){
			// std::cout << "done value: "<< *done << "\n";
			goto UNLOCK;
		}
		ch = chars->front();
		chars->pop();
		printChar(ch);
		randomSleep();
		UNLOCK:
		lk.unlock();
		cv->notify_all();
	}
	// winners->push(std::this_thread::get_id());
}


//Helper for sleeping
void randomSleep(){
	int time2Wait = std::rand()%3;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	std::this_thread::sleep_for(t);
}

//Print a Move
void printChar(char ch){
	static std::mutex ioLock;
	std::lock_guard<std::mutex> lk(ioLock);


	std::cout << "Thread "
		<< std::this_thread::get_id()
		<< " found: "
		<< ch
		<< std::endl;
	// printf("%c\n",ch);
}
