#include <iostream>
#include <vector>
#include <thread>

int binarySearch(int target, int a[], int start, int stop) {
	int low = start;
	int high = stop;
	while (low < high) {
	
		int middle = (high + low)/2;
		if (a[middle] == target) {
			return middle;
		}
		
		else if (a[middle] < target) {
			low = middle+1;
		}else {
			high = middle-1;
		}
	}
	return high;
}

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

void msort(int a[], int start,int end) {
	
	if (start < end) {
		int mid = (start + end)/2;
		msort(a, start, mid);
		msort(a, mid + 1, end);
		merge(a, start,mid ,end);
	}
}

void mergesort(int a[], int size) {
	msort(a, 0, size);

}

void mergeAllSections(int a[],int size ,int* startIndexes, int* stopIndexes, int numThreads) {
	std::thread* threads = new std::thread[32];
	int n1 = (stopIndexes[0] - startIndexes[0]) + 1;
	int n2 = (stopIndexes[1] - startIndexes[1]) + 1;
	int* n3 = new int[n1+n2]{0};
	int* new_start_idx = new int[10];
	int* new_stop_idx = new int[10];

	int mid_1 = (stopIndexes[0] - startIndexes[0]) / 2;
	int mid_2 = binarySearch(a[mid_1], a, startIndexes[1], stopIndexes[1]);

	int q3 = (mid_1 - startIndexes[0]) + ((mid_2 + 1) -startIndexes[1]);
	n3[q3] = a[mid_1];
	std::cout << "q3: " << q3 << " n3[q3]: " <<n3[q3] << "\n";
	int n = 0;

	for (int i=0; i < mid_1; i++) {
		n3[i] = a[i];
		n++;
	}

	for (int k= startIndexes[1]; k <= mid_2; k++) {
		n3[n] = a[k];
		n++;
	}
	if (n == q3)
		n++;
	std::cout << "n: " << n << "\n";

	for (int i= mid_1 + 1; i <= stopIndexes[0]; i++) {
		n3[n] = a[i];
		n++;
	}

	for (int j=mid_2+1; j <= stopIndexes[1]; j++) {
		n3[n] = a[j];
		n++;
	}
	new_start_idx[0] = 0;
	new_stop_idx[1] = 3;
	new_start_idx[0] = 5;
	new_stop_idx[1] = 9;

	for (int i=0; i < numThreads; i++) {
		threads[i] = std::thread(msort, n3, new_start_idx[i], new_stop_idx[i]); 
	}

	for (int i=0; i < numThreads; i++) {
		threads[i].join();
	}
	for (int i=0; i < size; i++)
		a[i] = n3[i];
	

}


void tmergesort(int a[], int size, int numThreads) {
	if (numThreads == 1) {
		mergesort(a, size - 1);
		return;
	}

	std::thread *threads = new std::thread[32];
	int number_per_thread = size / numThreads;
	int* start_idx = new int[number_per_thread]{0};
	int* stop_idx = new int[number_per_thread]{0};
	std::cout << "Number per threads: " << number_per_thread << std::endl;
	for (int i=0; i < numThreads; i++) {
		int start = i * number_per_thread;
		int end = (i + 1) * number_per_thread - 1;
		start_idx[i] = start;
		stop_idx[i] = end;
	}

	for (int i = 0; i < numThreads; i++) {
		threads[i] = std::thread(msort, a, start_idx[i], stop_idx[i]);
	}
  
	/*
	for (int f:start_idx) {
				std::cout << f << " ";
	}
    std::cout <<std::endl;
	for (int a:stop_idx) {
				std::cout << a << " ";

	}
    std::cout << std::endl; 
	*/
	for (int i=0; i < numThreads;i++) {
		threads[i].join();
	}
	// for (int i=0; i < 10; i++)
	// 	std::cout << a[i] << " ";
	// std::cout << "\n";

    mergeAllSections(a, size ,start_idx, stop_idx, numThreads);

}

				


int main() {
	int a[] =  {5, 9, 1, 8, 4, 6, 6, 3, 7, 2};
	
	tmergesort(a, sizeof(a) / sizeof(int), 2);
	//mergesort(a, sizeof(a)/sizeof(int));
	//std::cout << a.size() << std::endl;
	//mergesort(a, a.size());
	for (int f:a) {
		std::cout << f << " ";
	}
	std::cout << std::endl;
	/*
	int* A =  new int[5];
	A[0] = 7;
	A[1] = 8;
	A[2] = 1;
	A[3] = 3;
	A[4] = 7;
	int temp = binarySearch(2, A, 2, 4);
	std::cout << temp << std::endl;
	*/
}
