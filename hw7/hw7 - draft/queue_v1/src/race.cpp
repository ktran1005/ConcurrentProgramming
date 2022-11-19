//Mark Boady
//Drexel University 2021

#include "race.h"
#include <thread>
#include <iostream>

//Racer and Game Master Implementations

//Simulate the Game Master
void gameMaster(
	std::condition_variable* cv,
	std::mutex* mutex ,
	std::queue<char>* chars,
	std::queue<std::thread::id>* workers,
	bool* done,
	bool* canStart)
{
	// while(winners->length() != players){
	// 	//Step 1: select a random number between 0 and 5
	// 	int k = std::rand()%6;
	// 	//Step 2: Roll k dice
	// 	for(int i=0; i < k; i++){
	// 		int roll = std::rand()%6+1;
	// 		//Step 3: Add to queue
	// 		dice->push(roll);
	// 	}
	// 	//Sleep
	// 	randomSleep();
	// }

	FILE *fp;
    char ch;
    int n;
    // printf("Enter file Name :");
    // gets(fname);
    char fname[20] = "file.md"; 
    fp=fopen(fname,"r");
    if(fp==NULL)
    {
        printf("file can't be opened");
        exit(0);
    }
    fseek(fp,0,0);
    ch=fgetc(fp);
    while(ch!=EOF){
        // n=ftell(fp);
        // printf("%c ",ch);
        // printf("%d \n",n);
		chars->push(ch);
        ch=fgetc(fp);
        }
    fclose(fp);
}
	
//Simulate one Racer
void racer(
	std::condition_variable* cv,
	std::mutex* mutex ,
	std::queue<char>* chars,
	std::queue<std::thread::id>* workers,
	bool* done,
	bool* canStart)
{

	while(!done){
		std::unique_lock<std::mutex> lk(*mutex);
		cv->wait(lk,[&]{return *canStart;}); 
		char ch = chars->front();
		chars->pop();
		printChar(ch);
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
		<< " found "
		<< ch
		<< std::endl;
}
