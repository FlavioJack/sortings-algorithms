#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 10000

// Print an array on screen
void print_array(int arr[], const size_t size){
	printf("array[");
	for(size_t i=0; i<size; i++){
		printf("%d", arr[i]);
		if(i<size-1) printf(",");
	}
	printf("]\n");
}

// Swap items in the array
void swap(int arr[], const int index1, const int index2){
	int temp=arr[index1];
	arr[index1]=arr[index2];
	arr[index2]=temp;
}

/*	================================	*/
/*	====	SORTING ALGORITHMS	====	*/
/*	================================	*/

void selection(int arr[], const int size){
	for(size_t i=0; i<size; i++){
		int max = i;
		for(int j=i+1; j<size; j++){
			if(arr[max] < arr[j])
				max = j;
		}
		if(max!=i)
			swap(arr, max, i);
	}
}

void selection_rev(int arr[], const int size){
	for(size_t i=size-1; i>0; i--){
		int max = i;
		for(int j=i-1; j>=0; j--){
			if(arr[max] < arr[j]) 
				max = j;
		}
		if(max!=i) 
			swap(arr, max, i);
	}
}

/* Complessità di entrambi 𝑂(𝑛^2)
 * Nella versione selection_rev, l’inner loop scorre verso il basso (j--), 
 * quindi legge elementi che sono vicini in memoria e già caricati in cache.
 * 
 * Nella versione selection, l’inner loop scorre verso l’alto (j++), 
 * e questo può portare a più cache miss, soprattutto su array grandi. */

void bubble(int arr[], const int size){
	bool ordinated = false;	
	while(!ordinated){
		//counter++;
		ordinated = true;
		for(int j=0; j<size-1; j++){
			if(arr[j]>arr[j+1]){ 
				ordinated=false;
				swap(arr, j, j+1);
			}
		}
	}
}

void insertion_sort(int arr[], const int size){
	for(int i = 1; i < size; i++){
    	int selected = arr[i];
    	int j = i;
    	for(; j >= 1 && selected < arr[j - 1]; j--)
      		arr[j] = arr[j - 1];

      	arr[j] = selected;
	}
}


void quick_sort(int arr[], const int left, const int right){
	int pivot=arr[(right+left)/2];
	int i=left, j=right;
	
	if(left>=right) return;
	while(i<=j){
		while(arr[i]<pivot) i++;
		while(arr[j]>pivot) j--;
		if(i<=j){
			if(i<j) swap(arr, i, j);
			i++;
			j--;	
		}
	}
	if(left < j) quick_sort(arr, left, j);
	if(right > i) quick_sort(arr, i, right);
}

void merge(int arr[], const int left, const int center, const int right){
	int temp[right-left+1];
	// i is the start of the first half subarray, j is the start of the second half subarray
	int i=left, j=center+1, k=0; // k is start index of the temp array

	while(i<=center && j<=right){
		if(arr[i]<arr[j]){
			temp[k]=arr[i]; 
			i++;
		}
		else {
			temp[k]=arr[j];
			j++;
		}
		k++;
	}
	while(i<=center){
		temp[k]=arr[i];
		k++;
		i++;
	}
	while(j<=right){
		temp[k]=arr[j];
		k++;
		j++;
	}

	for(int i=left; i<=right; i++)
		arr[i]=temp[i-left];
}
void merge_sort(int arr[], const int left, const int right){
	if(left==right)
		return;
	else{
		int center=(left+right)/2;
		merge_sort(arr, left, center);
		merge_sort(arr, center+1, right);
		merge(arr, left, center, right);
	}
}

void heapify(int arr[], const int i, const int size){
	int left=2*i + 1; // left son of i
	int right=left+1; // right son of i
	int largest = i;
	
	while(left < size && arr[largest] < arr[left])
		largest = left;

	while(right < size && arr[largest] < arr[right])
		largest = right;

	if(largest != i){
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		heapify(arr, largest, size);
	}

}
void heap_sort(int arr[], const int size){
	int start_node;
	for(start_node = size/2 - 1; start_node>=0; start_node--)
		heapify(arr, start_node, size);

	for(int i = size-1; i>=0; i--){
		swap(arr, i, 0);
		heapify(arr, 0, i);
	}
}


/* -- THIS IS THE MAIN -- */

int main(void){
	size_t n = N;

	srand(time(NULL));
	int array[n];
	for(size_t i=0; i<n; i++){
		array[i] = rand();
	}
	
	// Selection sort
	clock_t start = clock();
	selection_rev(array, n);
	clock_t end = clock();
	double time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Selection reversed sort ha impiegato\t%f secondi\n", time_spent);

	start = clock();
	selection(array, n);
	end = clock();
	time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Selection sort ha impiegato\t\t%f secondi\n", time_spent);
	
	start = clock();
	bubble(array, n);
	end = clock();
	time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Bubble sort ha impiegato\t\t%f secondi\n", time_spent);
	

	/*
	printf("Quick sort: ");
	quick_sort(array, 0, N-1);
	*/
	
	/*
	printf("Heap sort: ");
	heap_sort(array, N);
	*/

	/*
	cout<<"Merge sort: ";
	merge_sort(array, 0, N-1);
	*/

}