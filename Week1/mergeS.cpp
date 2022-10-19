#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

int binarySearch(int target, int a[], int start, int stop) {
	int low = start;
	//int high = std::max(start, stop + 1);
	int high = stop + 1;
	while (low < high) {
	
		int middle = (high + low)/2;
		if (a[middle] == target) {
			return middle;
		}
		
		else if (a[middle] <= target) {
			low = middle+1;
		}else {
			high = middle;
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

void mergeAllSections(int a[],int size ,int startIdx, int stopIdx, int numThreads) {
	std::thread* threads = new std::thread[8];
	int numPerThread = size / numThreads;
	int start_2 = startIdx + numPerThread;
	int stop_1 = start_2 - 1;

	std::cout << "start[0]: " << startIdx << "\n";
	std::cout << "stop[0]: " << stop_1 << "\n";
	std::cout << "start[1]: " << start_2 << "\n";
	std::cout << "stop[1]: " << stopIdx << "\n";
	
	
	// int n1 = (stopIndexes[0] - startIndexes[0]) + 1;
	int n1 = (stop_1 - startIdx) + 1;
	//std::cout << "n1: " << n1 << "\n";
	// int n2 = (stopIndexes[1] - startIndexes[1]) + 1;
	int n2 = (stopIdx - start_2) + 1; 
	//std::cout << "n2: " << n2 << "\n";
	int* startIndexes = new int[2];
	int* stopIndexes = new int[2];
	startIndexes[0] = startIdx;
	startIndexes[1] = start_2;
	stopIndexes[0] = stop_1;
	stopIndexes[1] = stopIdx;

	for (int i=0; i < numThreads; i++) {
		std::cout << startIndexes[i] << " ";
		std::cout << stopIndexes[i] << " ";
	}
	std::cout << "\n";

	if (n1 < n2) {
		// swap start
		// int temp1 = startIndexes[0];
		int temp1 = startIdx;
		startIndexes[0] = startIndexes[1];
		startIndexes[1] = temp1;
		// swap end
		int temp2 =  stopIndexes[0];
		stopIndexes[0] = stopIndexes[1];
		stopIndexes[1] = temp2;
		// swap size
		int temp3 = n1;
		n1 = n2;
		n2 = temp3;

	}
	// std::cout << "After swap ";
	// for (int i=0; i < numThreads; i++)
	// 	std::cout << startIndexes[i] << " ";
	// std::cout << "\n"; 

	int* n3 = new int[n1+n2]{0};
	int* new_start_idx = new int[numPerThread]{0};
	int* new_stop_idx = new int[numPerThread]{0};

	int mid_1 = (stopIndexes[0] - startIndexes[0]) / 2;
	//std::cout << "mid_1: " << mid_1 << "\n";
	int mid_2 = binarySearch(a[mid_1], a, startIndexes[1], stopIndexes[1]);
	//std::cout << "mid_2: " << mid_2 << "\n";

	//int q3 = (mid_1 - startIndexes[0]) + ((mid_2+1) - startIndexes[1]);
	int q3 = (mid_1 - startIndexes[0]) + (mid_2 - startIndexes[1]);
	//std::cout << "q3: " << q3 << "\n";
	n3[q3] = a[mid_1];
	//std::cout << "n3[q3]: " << n3[q3] << "\n";
	int n = 0;

	for (int i=0; i < mid_1; i++) {
		n3[i] = a[i];
		//std::cout << "checking" << "\n";
		n++;
	}

	for (int k = startIndexes[1]; k < mid_2; k++) {
		n3[n] = a[k];
		n++;
	}
	if (n == q3)
		n++;

	//std::cout << "n: " << n << "\n";

	for (int i= mid_1 + 1; i <= stopIndexes[0]; i++) {
		n3[n] = a[i];
		// std::cout << "a[i]: " << a[i] << "\n";
		n++;
	}

	for (int j=mid_2; j <= stopIndexes[1]; j++) {
		n3[n] = a[j];
		// std::cout << "a[j]: " << a[j] << "\n";
		n++;
	}	
	new_start_idx[0] = startIndexes[0];
	new_stop_idx[0] = q3 - 1;
	new_start_idx[1] = q3 + 1;
	new_stop_idx[1] = stopIndexes[1];


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

	std::thread *threads = new std::thread[8];
	int number_per_thread = size / numThreads;
	int* start_idx = new int[number_per_thread]{0};
	int* stop_idx = new int[number_per_thread]{0};
	std::cout << "Number per threads: " << number_per_thread << std::endl;
	for (int i=0; i < numThreads; i++) {
		int start = i * number_per_thread;
		//int end = (i + 1) * number_per_thread - 1;
		
		int end;
		if (i == numThreads-1)
			end = size -1;
		else 
			end = (i + 1) * number_per_thread - 1;
		
		
		start_idx[i] = start;
		stop_idx[i] = end;
	}


	for (int i = 0; i < numThreads; i++) {
		threads[i] = std::thread(msort, a, start_idx[i], stop_idx[i]);
	}
  
	for (int i=0; i < numThreads;i++) {
		threads[i].join();
	}
	

	std::cout << "start idx: " << " ";
	for (int i=0; i < numThreads; i++)
		std::cout << start_idx[i] << " ";
	std::cout << "\n";

	std::cout << "stop idx: " << " "; 
	for (int i=0; i < numThreads; i++)
		std::cout << stop_idx[i] << " ";
	std::cout << "\n";


	for (int i=0; i < size; i++)
		std::cout << a[i] << " ";
	std::cout << "\n\n";
	
	//std::cout << "Merge All section starts here" << "\n";
	
	while (numThreads != 1) {
		numThreads /= 2;
		number_per_thread = size / numThreads;
		//int* start_idx = new int[numThreads]{0};
		//int* stop_idx = new int[numThreads]{0};
		// std::cout << "Number per threads: " << number_per_thread << std::endl;
		for (int i=0; i < numThreads; i++) {
			int start = i * number_per_thread;
			int end;
			if (i == numThreads-1)
				end = size -1;
			else 
				end = (i + 1) * number_per_thread - 1;
		
		
			start_idx[i] = start;
			stop_idx[i] = end;
		}
		std::cout << "start idx: " << " ";
		for (int i=0; i < numThreads; i++)
			std::cout << start_idx[i] << " ";
		std::cout << "\n";

		std::cout << "stop idx: " << " "; 

		for (int i=0; i < numThreads; i++)
			std::cout << stop_idx[i] << " ";
		std::cout << "\n\n";
		
		
		std::cout << "start[0]: " << start_idx[0] << "\n";
		std::cout << "stop[0]: " << stop_idx[0] << "\n\n";
		for (int i = 0; i < numThreads; i++) {
			threads[i] = std::thread(mergeAllSections, a, size ,start_idx[i], stop_idx[i], numThreads);
		}
  
		for (int i=0; i < numThreads;i++) {
			threads[i].join();
		}
		
		// mergeAllSections(a, size ,0, 9, numThreads);
	}
	//mergeAllSections(a, size ,0, 3, numThreads);
	
}

				


int main() {
	int a[] =  {15, 0, 10, 5, 9, 1, 13, 3, 7, 2, 12,8,4,14,11,6};
	tmergesort(a, sizeof(a) / sizeof(int),8);
	
	// int b[] = {15, 5, 10, 3};	
	// tmergesort(b,sizeof(b)/sizeof(int),2);
	
	// int c[] = {8,7,1,3};
	// tmergesort(c, sizeof(c) / sizeof(int), 2);
	
	for (int f:a) {
		std::cout << f << " ";
	}
	std::cout << std::endl;
	
	// for (int k:b) {
	// 	std::cout << k << " ";
	// }
	// std::cout << std::endl;
	
	// for (int l:c) {
	// 	std::cout << l << " ";
	// }
	// std::cout << std::endl;

}
