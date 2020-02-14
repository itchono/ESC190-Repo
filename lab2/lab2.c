#include "lab2.h"

void print_tree(float arr[], int n) {
    /* Your code goes here */
}

float get_parent_value(float arr[], int n, int index) {
    // parent is (n-1)/2
    return (index > (n-1) || index == 0) ? -1 : arr[(index-1)/2];
}

float get_left_value(float arr[], int n, int index) {
    // left is 2n+1
    return (2*index + 1 > (n-1)) ? -1 : arr[index*2 + 1];
}

float get_right_value(float arr[], int n, int index) {
    // right is 2n+2
   
    return (2*index + 2 > (n-1)) ? -1 : arr[index*2 + 2];
}

int is_max_heap(float arr[], int n) {
    /* Your code goes here */
}

void heapify(float arr[], int n) {
    /* Your code goes here */
}

void heapsort(float arr[], int n) {
    /* Your code goes here */
}

float find_most_common_element(float arr[], int n) {
    // use depth first traversal
    
}
