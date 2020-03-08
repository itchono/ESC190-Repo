#include <stdio.h>
#include <stdlib.h>

// array output
void printArr(int* arr, int size){
  for (int x = 0; x < size; x++) {
      printf("%d\t", arr[x]);
  }
  printf("\n");
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

void quickSorter(int* arr, int low, int high) {
  const int LEFT = 0;
  const int RIGHT = 1;
  
  if (low < high) {
    int left = low;
    int right = high;
    // LR pointers
    
    int currentDir = LEFT; // dir of motion
    int pivot = arr[low]; // temp var to store pivot
    
    while (left < right) {
      // We now start the main process
      
      if (currentDir == LEFT) {
        // if moving left, look for values that exceed pivot (via R ptr)
        while ((arr[right] >= pivot) && (left < right)){
          right --; // decrement R pointer until exception occurs
        }
        arr[left] = arr[right];
        // swap and change direction
        currentDir = RIGHT;
      }
      if (currentDir == RIGHT) {
        // if moving left, look for values that exceed pivot (via R ptr)
        while ((arr[left] <= pivot) && (left < right)){
          left++; // increment L pointer until exception occurs
        }
        arr[right] = arr[left];
        // swap and change direction
        currentDir = LEFT;
      }
    }
    arr[left] = pivot; // restore pivot
    // begin recursive sorts of smaller arrs
    quickSort(arr, low, left - 1); // sorts from base to L ptr-1
    quickSort(arr, right+1, high); // sorts top half from R ptr+1 to end
  }
}

void quickSort(int* arr, int size) {
  quickSorter(arr, 0, size-1);
}

int main() {
    int* arr = CreateRndArray(100, 0, 99);

    printArr(arr, 100);

    quickSort(arr, 100);

    printArr(arr, 100);
}