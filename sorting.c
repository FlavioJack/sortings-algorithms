#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
void swap(int arr[], const size_t index1, const size_t index2){
	int temp=arr[index1];
	arr[index1]=arr[index2];
	arr[index2]=temp;
}

/*	================================	*/
/*	====	SORTING ALGORITHMS  ====	*/
/*	================================	*/

void selection(int arr[], const size_t size){
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

void selection_rev(int arr[], const size_t size){
	for(size_t i=size-1; i>0; i--){
		size_t max = i;

		for(size_t j=0; j<i; j++){
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

void bubble(int arr[], const size_t size){
	bool ordinated = false;	
	while(!ordinated){
		ordinated = true;
		for(size_t i=0; i<size-1; i++){
			if(arr[i]>arr[i+1]){ 
			    ordinated=false;
			    swap(arr, i, i+1);
			}
		}
	}
}

void insertion(int arr[], const size_t size){
	for(size_t i=1; i<size; i++){
	   int selected = arr[i];
	   size_t j = i;
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
    printf("SORTING ALGORITHMS AND THEIR EXECUTION TIME\n");
    printf("Press Ctrl+Z on Windows or Ctrl+D on Linux/MacOS to end the program," 
    " any other key to continue\n");
    
    while( getchar() != EOF ){
	
	printf("Enter the array size; the number of items must be greater then zero: ");
	int tmp_n;
	scanf("%d", &tmp_n);
	while(tmp_n<=0){
	    printf("You entered zero/negative number; size must be greater then 0: ");
	    scanf("%d", &tmp_n);
	}
	size_t n = (size_t)tmp_n;
	
	printf("ARRAY FILLING VALUES\n1)Random values\n2)Already ordered values\n");
	int choice;
	printf("Choose: ");
	scanf("%d", &choice);
	while(choice<1 || choice>2){
	    printf("You entered wrong value. 1)Random values or 2)Ordered values: ");
	    scanf("%d", &choice);
	}
    
	srand(time(NULL));
	int array[n];
	int wrkarr[n];

	if(choice == 1){
	    printf("Filling the array with random numbers...");
	    for(size_t i=0; i<n; i++)
	    	array[i] = rand();
	}
	else if(choice == 2){
	    printf("Filling the array with ordered numbers...");
	    for(size_t i=0; i<n; i++)
		array[i]=i;
	} 
	printf("Done.\n");

	printf("Starting sorting algorithms...\n");
	
	memcpy(wrkarr, array, sizeof(array));
	clock_t start = clock();
	selection_rev(wrkarr, n);
	clock_t end = clock();
	double time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Selection rev time: \t%f s\n", time_spent);

	memcpy(wrkarr, array, sizeof(array));
	start = clock();
	selection(wrkarr, n);
	end = clock();
	time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Selection sort time:\t%f s\n", time_spent);

	memcpy(wrkarr, array, sizeof(array));
	start = clock();
	bubble(wrkarr, n);
	end = clock();
	time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Bubble sort time:\t%f s\n", time_spent);
	
	memcpy(wrkarr, array, sizeof(array));
	start = clock();
	insertion(wrkarr, n);
	end = clock();
	time_spent = (double)(end-start)/CLOCKS_PER_SEC;
        printf("Insertion sort time:\t%f s\n", time_spent);
      
	memcpy(wrkarr, array, sizeof(array));
	start = clock();
	quick_sort(wrkarr, 0, n-1);
	end = clock();
	time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Quick sort time:\t%f s\n", time_spent); 
	
	memcpy(wrkarr, array, sizeof(array));
	start = clock();
	heap_sort(wrkarr, n);
	end = clock();
	time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Heap sort time:\t\t%f s\n", time_spent);

	memcpy(wrkarr, array, sizeof(array));
	start = clock();
	merge_sort(wrkarr, 0, n-1);
	end = clock();
	time_spent = (double)(end-start)/CLOCKS_PER_SEC;
	printf("Merge sort time:\t%f s\n", time_spent);

	printf("Done.\n");

	printf("Press Ctrl+Z on Windows or Ctrl+D on Linux/MacOS to end the program," 
	" any other key to continue\n");
	if(getchar()=='\n')
		;
    }
}
