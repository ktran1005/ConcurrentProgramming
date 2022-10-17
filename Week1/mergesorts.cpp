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
	/*for (int i = 0; i < numThreads; i++) {
		int left = startIndexes[i];
		int right = stopIndexes[;
		int middle = left + (right - left) / 2;
		merge(a, left, middle, right);
		msort(a, left, right);
	}*/
	std::vector<int> temp1, temp2;
	std::vector <std::thread> threads;

	int n1 = (stopIndexes[0] - startIndexes[0]) + 1;
	int n2 = (stopIndexes[1] - startIndexes[1]) + 1;
	
	int mid_1 = (stopIndexes[0] - startIndexes[0]) / 2;
	int mid_2 = binarySearch(a[mid_1], a, startIndexes[1], stopIndexes[1]);
	
	std::cout << "The middle point of sorted list " << a[mid_1] << "\n";
	std::cout << "the idx of midpoint from sorted list 1 at sorted list 2 is: " << mid_2 << std::endl;
	for (int i=0; i < mid_1; i++)
		temp1.push_back(a[i]);
	int k = startIndexes[1];
	while (a[k] != mid_2) {
		temp1.push_back(a[k]);
		k++;
	}
	int l = mid_2 + 1;
	for (int i=mid_1+1; i <= stopIndexes[0]; i++)
		temp2.push_back(a[i]);
	for (int j=mid_2+1; j <= stopIndexes[1]; j++)
		temp2.push_back(a[j]);
	int* n3 = new int[n1 + n2];
	for (int first=0; first < temp1.size(); first++)
		std::cout << temp1[first] << " ";
	std::cout << "\n";

	for (int second=0; second < temp2.size(); second++)
		std::cout << temp2[second] << " ";
	std::cout << "\n";

	/*mergesort(temp1, temp1.size());
  for (int f= 0; f < temp1.size(); f++) 
    std::cout << temp1[f] << " ";
	std::cout << "\n";

	mergesort(temp2, temp2.size());
	for (int k:temp2)
    std::cout << k << " ";
  */
	for (int i=0; i < numThreads; i++)
				threads.push_back(std::thread(mergesort, std::ref(temp1), temp1.size()));
  
	for (int i=0; i < numThreads; i++)
				threads[i].join();
}


void tmergesort(std::vector<int> &a, int size, int numThreads) {
	if (numThreads == 1) {
		mergesort(a, size - 1);
		return;
	}

	std::vector <int> start_idx, stop_idx;
	std::vector <std::thread> threads;
	std::thread* myThreads = new std::thread[numThreads];
	int number_per_thread = size / numThreads;
	std::cout << "Number per threads: " << number_per_thread << std::endl;
	for (int i=0; i < numThreads; i++) {
		int start = i * number_per_thread;
		int end = (i + 1) * number_per_thread - 1;
		start_idx.push_back(start);
		stop_idx.push_back(end);
	}

	for (int i = 0; i < numThreads; i++) {
		//myThreads[i] = std::thread(mergesort,std::ref(a), stop_idx[i] - start_idx[i]);
   threads.push_back(std::thread(msort,std::ref(a),start_idx[i],stop_idx[i]));
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
		//myThreads[i].join();
		threads[i].join();
	}

    mergeAllSections(a, size ,start_idx, stop_idx, numThreads);

}

				


int main() {
	std::vector<int> a {5, 9, 1, 8, 4, 6, 6, 3, 7, 2};
	tmergesort(a, a.size(), 2);
//	mergesort(a, sizeof(a)/sizeof(int));
	//for (int f:a) {
	//	std::cout << f << " ";
	//}
	std::cout << "\n";
	//std::cout << a.size() << std::endl;
	//mergesort(a, 10);
	for (int f:a) {
		std::cout << f << " ";
	}
	std::cout << std::endl;
}
