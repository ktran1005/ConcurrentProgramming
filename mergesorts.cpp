#include <iostream>
#include <vector>
#include <thread>


void merge(int a[], int start,int mid ,int end) {
	std::vector <int> b1, b2;
	for (int i = start; i <= mid; i++) {
		b1.push_back(a[i]);
	}

	for (int i = mid + 1; i <= end; i++) {
		b2.push_back(a[i]);
	}

	int p1 = 0, p2 = 0, p3 = start;
	while (p1 < b1.size() && p2 < b2.size()) {
		if (b1[p1] < b2[p2]) {
			a[p3++] = b1[p1++];
		} else {
			a[p3++] = b2[p2++];
		}
	}

	while (p1 < b1.size()) {
		a[p3++] = b1[p1++];
	}

	while (p2 < b2.size()) {
		a[p3++] = b2[p2++];
	}
}

void mergesort(int a[], int start,int end) {
	
	if (start < end) {
		int mid = (start + end)/2;
		mergesort(a, start, mid);
		mergesort(a, mid + 1, end);
		merge(a, start,mid ,end);
	}
}

void mergeAllSections(int a[], int startIndexes, int stopIndexes, int numThreads) {

}

void tmergesort(int a[], int size, int numThreads) {
	if (numThreads == 1) {
		mergesort(a, 0, 8);
		return;
	}

	std::vector <int> start_idx, stop_idx;
	std::thread *T = new std::thread[numThreads];
	std::vector <std::thread> threads;
	int number_per_thread = size / numThreads;
	for (int i=0; i < numThreads; i++) {
		int start = i * (number_per_thread);
		int end = (i + 1) * (number_per_thread) - 1;
		start_idx.push_back(start);
		stop_idx.push_back(end);
		threads.push_back(std::thread(mergesort, a, start, end));
	}

	for (int i=0; i < numThreads;i++) {
		threads[i].join();
	}

}



int main() {
	int a[] = {5, 9, 1, 3, 4, 6, 6, 3,2};
	mergesort(a, 0 ,sizeof(a)/sizeof(int) - 1);
	for (int f:a) {
		std::cout << f << " ";
	}
	std::cout << std::endl;
}
