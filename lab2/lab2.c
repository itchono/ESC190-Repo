#include "lab2.h"

void print_tree(float arr[], int n) {
    // breadth first traversal
    int *queue = calloc(n, sizeof(float)); // dynamically sized queue
    // queue indices of array

    int numRows = 0;
    int tempSize = n;

    while (tempSize > 0) {
        numRows ++;
        tempSize /= 2;
    }

    queue[0] = 0; // enqueue root

    int queueSize = 1;
    int queueStart = 0;
    int queueEnd = 1;

    int rowNumber = 0;

    while (queueSize > 0) {
        float* level = calloc(n, sizeof(float));
        int levelptr = 0;

        for (int x = queueStart; x < queueEnd; x++) {

            level[levelptr] = arr[queue[x]];
            levelptr ++; // enqueue current node at a level
            
            int i = queue[x];
            queueStart ++; // dequeue all the nodes here.
            queueSize --;

            if ((int)get_left_value(arr, n, i) != -1) {
                queue[queueEnd] = 2*i+1;
                queueEnd ++; // enqueue
                queueSize ++;
            }
            if ((int)get_right_value(arr, n, i) != -1) {
                queue[queueEnd] = 2*i+2;
                queueEnd ++; // enqueue
                queueSize ++;
            }
        }

        for (int x = 0; x <= levelptr; x++) {
            printf("%d", level[x]);
            printf("\n");
        }

        
    }

    printf("%d",numRows);

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
