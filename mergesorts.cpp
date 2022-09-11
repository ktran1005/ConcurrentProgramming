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


void mergeAllSections(int a[],int size ,std::vector <int> startIndexes, std::vector <int> stopIndexes, int numThreads) {
				for (int i = 0; i < numThreads; i++) {
								int left = startIndexes[i];
								std::cout << i << ": left value is: " << left << std::endl;
								int right = stopIndexes[i];
								std::cout << i << ": right value is: " << right << std::endl;
								int middle = left + (right - left) / 2;
								merge(a, left, middle, right);
				}
			//	if (numThreads / 2 >= 1) {
			//					mergeAllSections(a, size, startIndexes, stopIndexes, numThreads);
			//	}

}


void tmergesort(int a[], int size, int numThreads) {
	if (numThreads == 1) {
		//mergesort(a, 0, sizeof(a)/sizeof(int) - 1);
		return;
	}

	std::vector <int> start_idx, stop_idx;
	std::vector <std::thread> threads;
	int number_per_thread = size / numThreads;
	std::cout << "Number per threads: " << number_per_thread << std::endl;
	for (int i=0; i < numThreads; i++) {
		int start = i * (number_per_thread);
		int end = (i + 1) * (number_per_thread) - 1;
		start_idx.push_back(start);
		stop_idx.push_back(end);
		threads.push_back(std::thread(mergesort, a, start, end));
	}
  
	for (int f:start_idx) {
				std::cout << f << " ";
	}
  std::cout <<std::endl;
	for (int a:stop_idx) {
				std::cout << a << " ";

	}
  std::cout << std::endl; 
	for (int i=0; i < numThreads;i++) {
		threads[i].join();
	}

  //mergeAllSections(a, size ,start_idx, stop_idx, numThreads);

}

				


int main() {
	int a[] = {5, 9, 1, 8, 4, 6, 6, 3};
	mergesort(a, 0 ,sizeof(a)/sizeof(int) - 1);
	//tmergesort(a, sizeof(a)/sizeof(int)-1,2);
	for (int f:a) {
		std::cout << f << " ";
	}
	std::cout << std::endl;
}
