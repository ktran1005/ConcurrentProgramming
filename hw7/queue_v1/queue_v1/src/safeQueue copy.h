//Mark Boady
//Drexel University 2021

//Class for a thread safe queue
#ifndef _SAFE_QUEUE_H_
#define _SAFE_QUEUE_H_

#include <mutex>
#include <condition_variable>
template <class T>
class safeQueue {
	private:
		//A node to store values in
		struct node{
			T value;
			node* next;
		};
		//Head Pointer
		node* head;
		//Tail Pointer
		node* tail;
		//Size of queue
		int size;
		//Locks for safety
		mutable std::mutex mut;
		std::condition_variable condVar;
	public:
		safeQueue();
		void push(T v);
		T waitAndPop();
		bool tryToPop(T &result);
		int length();
		bool empty();
	private:
		T front();
		void dequeue();
		void enqueue(T v);
};


//We don't need to protect the constructor
//It should be built before shared access
template <class T>
safeQueue<T>::safeQueue(){
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <class T>
void safeQueue<T>::push(T v){
	//Lock this entire method
	std::lock_guard<std::mutex> lk(mut);
	//Add value
	enqueue(v);
	//Exit and release lock
	condVar.notify_all();
}

//Wait until data is available
//then pop it
template <class T>
T safeQueue<T>::waitAndPop(){
	std::unique_lock<std::mutex> lk(mut);
	//This lambda is a method of class this
	condVar.wait(lk,
		[this]{return head!=nullptr;});
	//At this point, there is data to pop
	T result = front();
	dequeue();
	//Return the result
	return result;
}

//This version doesn't wait
//if the queue is empty it returns false
//allowing the thread to continue doing
//something else
template <class T>
bool safeQueue<T>::tryToPop(T &result){
	std::lock_guard<std::mutex> lk(mut);
	if(head==nullptr){
		return false;
	}
	//There is a value
	result = front();
	dequeue();
	return true;
}

//Ask the Size of the queue
template <class T>
int safeQueue<T>::length(){
	//Lock this entire method
	std::lock_guard<std::mutex> lk(mut);
	return size;
}

//Check if the queue is empty
template <class T>
bool safeQueue<T>::empty(){
	//Lock this entire method
	std::lock_guard<std::mutex> lk(mut);
	return head==nullptr;
}

//Private Methods from a classic queue
//These are protected by the public methods



//Get first value in the queue
template <class T>
T safeQueue<T>::front(){
	return head->value;
}

//Remove value from the queue
template <class T>
void safeQueue<T>::dequeue(){
	//Store node to delete
	node* temp = head;
	//See if this is the last value
	if(head->next == nullptr){
		head = nullptr;
		tail = nullptr;
		size = 0;
	}else
	{//Move next to front
		head = head->next;
		size = size - 1;
	}
	//Delete the node we removed
	delete temp;
}

//Add value to the queue
template <class T>
void safeQueue<T>::enqueue(T v){
	//Make a new Node
	node* n = new node();
	n->value = v;
	n->next = nullptr;
	//Is the queue empty
	if(head==nullptr){
		head = n;
		tail = n;
		size = 1;
	}else{
		tail->next = n;
		tail = n;
		size++;
	}
}

#endif
