#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex myLock;

void printArray(int *A, int size);
void sleepSort(int *A, int size);
void sleepThread(int value, int *A, int &counter);

int main(int argc, char** argv){
	// Let's make an array
	int size = 6;
	int *A = new int[size];
	A[0] = 2;
	A[1] = 1;
	A[2] = 1;
	A[3] = 1;
	A[4] = 1;
	A[5] = 2;
	std::cout << "Starting Array: ";
	printArray(A, size);
	sleepSort(A, size);
	std::cout << "Final Array: ";
	printArray(A, size);
	return 0;
}

void printArray(int *A, int size){
	std::cout << "[";
	for (int i=0; i < size; i++) {
		std::cout << A[i] << " ";
	}

	std::cout << "]" << std::endl;
}

void sleepSort(int *A, int size){
	int count = 0;
	std::thread *T = new std::thread[size];
	for (int i=0; i < size; i++){
		T[i] = std::thread(sleepThread, A[i], A, std::ref(count));
	}
	for (int i=0; i < size; i++){
		T[i].join();
	}
}

void sleepThread(int value, int *A, int &counter){
	std::thread::id myID = std::this_thread::get_id();
	std::chrono::seconds waitTime = std::chrono::seconds(value);
	std::this_thread::sleep_for(waitTime);
	myLock.lock();
	std::cout << myID << " " << value << std::endl;
	int myVal = counter;
	counter++;
	myLock.unlock();
	A[myVal] = value;
	return;
	
}
