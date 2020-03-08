#include <stdio.h>
#include <stdlib.h>

// array output
void printArr(int* arr, int size){
  for (int x = 0; x < size; x++) {
      printf("%d\t", arr[x]);
  }
  prinft("\n");
}

// Array Creation
int* CreateRndArray(int size, int low, int high) {
  srand((time(0)));

   int* arr = calloc(size, sizeof(int));
  for (int x = 0; x < size; x++) {
    arr[x] = rand() % (high-low+1) + low;
  }
  return arr;
}

// merger helper function
void merge(int* arr, int size, int start, int mid, int end) {
  int* temp = calloc(size, sizeof(int));
  // creation of temp Array
  
  int pos1 = start;
  int pos2 = mid+1;
  int spot = start; // pointer locations
  
  // merging process using original array as reference for comparisons
  while (!(pos1 > mid && pos2 > end)) {
    if ((pos1 > mid) || ((pos2 <= end) && (arr[pos2] < arr[pos1]))) {
      temp[spot] = arr[pos2];
      pos2++;
    } 
    else {
      temp[spot] = arr[pos1];
      pos1++;
    }
    spot ++;
  }
  
  // recopy temp arr back to main arr
  for (int x = start; x <= end; x ++) {
    arr[x] = temp[x];
  }

  free(temp);
  // merge complete
}

// main recursive mergesort
void mergeSort(int* arr, int size, int start, int end){
  if (start < end) {
    int mid = (start + end) / 2;
    mergeSort(arr, size, start, mid);
    mergeSort(arr, size, mid+1, end);
    merge(arr, size, start, mid, end);
  }
  // very important to control start < end otherwise it runs forever lol
  
}

// overloaded receiver method like in quicksort
void mergeSort(int* arr, int size) {
  mergeSort(arr, size, 0, size-1);
}
