#include <iostream>
#include <vector>
#include <thread>

int binarySearch(int target, std::vector<int> &a, int start, int stop) {
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

void merge(std::vector<int> &a, int start,int mid ,int end) {
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

void msort(std::vector<int> &a, int start,int end) {
	
	if (start < end) {
		int mid = (start + end)/2;
		msort(a, start, mid);
		msort(a, mid + 1, end);
		merge(a, start,mid ,end);
	}
}

void mergesort(std::vector<int> &a, int size) {
	msort(a, 0, size);

}
void mergeAllSections(std::vector <int> &a,int size ,std::vector <int> startIndexes, std::vector <int> stopIndexes, int numThreads) {
	std::vector<int> temp1, temp2;
	std::vector <std::thread> threads;

	int n1 = (stopIndexes[0] - startIndexes[0]) + 1;
	int n2 = (stopIndexes[1] - startIndexes[1]) + 1;
	// int* n3 = new int[n1 + n2]{0};
	std::vector<int> n3;
	int mid_1 = (stopIndexes[0] - startIndexes[0]) / 2;
	int mid_2 = binarySearch(a[mid_1], a, startIndexes[1], stopIndexes[1]);
	
	//std::cout << "The middle point of sorted list " << a[mid_1] << "\n";
	//std::cout << "the idx of midpoint from sorted list 1 at sorted list 2 is: " << mid_2 << std::endl;
	
	/*for (int i=0; i < mid_1; i++)
		temp1.push_back(a[i]);
	int k = startIndexes[1];
	while (a[k] != mid_2) {
		temp1.push_back(a[k]);
		k++;
	}*/
	int n=0;
	// int q3 = (mid_1 - startIndexes[0]) + ((mid_2 + 1) - stopIndexes[1]);
	// n3[q3] = a[mid_1];
	for (int i=0; i < mid_1; i++) {
		// n3[i] = a[i];
		// n++;
		n3.push_back(a[i]);
	}

	for (int k = startIndexes[1]; k <= mid_2; k++) {
		// n3[n] = a[k];
		// n++;
		n3.push_back(a[k]);
	}

	// n3[n] = a[mid_1];
	// n++;
	n3.push_back(a[mid_1]);
	// for (int i=0; i < 5; i++) {
	// 	std::cout << n3[i] << std::endl;
	// }
	for (int i=mid_1 + 1; i <= stopIndexes[0]; i++) {
		// n3[n] = a[i];
		// n++;
		n3.push_back(a[i]);
	}

	for (int j=mid_2+1; j <= stopIndexes[1]; j++) {
		// n3[n] = a[j];
		// n++;
		n3.push_back(a[j]);
	}
	/*	
	for (int i=0; i < 10; i++) 
		std::cout << n3[i] << " ";
	std::cout << "\n";
	*/

	std::vector<int> new_start_idx;
	std::vector<int> new_stop_idx;
	new_start_idx.push_back(0);
	new_start_idx.push_back(5);
	new_stop_idx.push_back(3);
	new_stop_idx.push_back(9);

	for (int i=0; i < numThreads; i++)
		threads.push_back(std::thread(msort, std::ref(n3), new_start_idx[i], new_stop_idx[i])); 
  
	for (int i=0; i < numThreads; i++)
		threads[i].join();


	for (int i=0; i < n3.size(); i++)
		a[i] = n3[i];
}


void tmergesort(std::vector<int> &a, int size, int numThreads) {
	if (numThreads == 1) {
		mergesort(a, size - 1);
		return;
	}

	std::vector <int> start_idx, stop_idx;
	std::vector <std::thread> threads;
	int number_per_thread = size / numThreads;
	//std::cout << "Number per threads: " << number_per_thread << std::endl;
	for (int i=0; i < numThreads; i++) {
		int start = i * number_per_thread;
		int end;
		if (i == numThreads-1)
			end = size -1;
		else 
			end = (i + 1) * number_per_thread - 1;
		start_idx.push_back(start);
		stop_idx.push_back(end);
	}

	for (int i = 0; i < numThreads; i++) {
   		threads.push_back(std::thread(msort,std::ref(a),start_idx[i],stop_idx[i]));
	}

	std::cout << "Use thread the 1st time" << "\n";
	for (int f:a) {
		std::cout << f << " ";
	}
	std::cout << "\n";
	
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

    mergeAllSections(a, size ,start_idx, stop_idx, numThreads);

}

				


int main() {
	std::vector<int> a {5, 9, 1, 8, 4, 6, 6, 3, 7, 2};
	std::cout << "Before sorted: " << "\n";
	for (int f:a) {
		std::cout << f << " ";
	}
	std::cout << "\n";
	
	tmergesort(a, a.size(), 2);
	//mergesort(a, a.size());
	std::cout << "Use thread the 2nd time: " << "\n";
	for (int f:a) {
		std::cout << f << " ";
	}
	std::cout << std::endl;
}
