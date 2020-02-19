#include "lab2.h"
#include <math.h>

void print_tree(float arr[], int n) {
    // breadth first traversal
    int *queue = calloc(n, sizeof(int)); // dynamically sized queue
    // queue indices of array

    int numRows = 0;
    int tempSize = n;

    while (tempSize > 0) {
        numRows ++;
        tempSize /= 2;
        // shitty logarithm function
    }

    /*
    printf("%d",numRows);
    printf(" Rows.\nPrint Tree:\n");
    debug
    */

    queue[0] = 0; // enqueue root

    int queueSize = 1;
    int queueStart = 0;
    int queueEnd = 1;

    int rowNumber = 0;


    while (queueSize > 0) {
        int* level = calloc(n, sizeof(int)); // a sub-list of the current level
        int levelptr = 0; // indicate which level we are currently on

        /*
        printf("Size: ");
        printf("%d", queueSize);
        printf(" Start: ");
        printf("%d", queueStart);
        printf(" End: ");
        printf("%d", queueEnd);
        printf("\n");
        debug code
        */
        int qs = queueStart; // fixed pointers for sizing
        int qe = queueEnd;

        for (int x = qs; x < qe; x++) {
          // NOTE TO SELF: c will re-check boundary values if they get updated.

            int i = queue[x]; // index which we will be putting through arr to output.

            /*printf("%f", arr[i]);
            printf("\n");
            debug code
            */

            queueStart ++; // dequeue the current node we are on
            queueSize --;

            level[levelptr] = i;
            levelptr ++; // enqueue current node at a level

            if (get_left_value(arr, n, i) != -1) {
                queue[queueEnd] = 2*i+1;
                queueEnd ++; // enqueue
                queueSize ++;
            }
            if (get_right_value(arr, n, i) != -1) {
                queue[queueEnd] = 2*i+2;
                queueEnd ++; // enqueue
                queueSize ++;
            }
        }
        rowNumber ++;

        // PRINTING STUFF OUT
        // Stage 1: Pre-spacing
        for (int y = 0; y < 3*(numRows-rowNumber); y++)  {
          printf(" ");
        }


        // Stage 2: Values
        for (int x = 0; x < levelptr; x++) {
            printf("%g", arr[level[x]]);

            for (int y = 0; y < 4*(numRows-rowNumber + 1); y++) {
              printf(" ");
            }
        }

        free(level);
        printf("\n");

        
    }

}

float get_parent_value(float arr[], int n, int index) {
    // DONE
    // parent is (n-1)/2
    return (index > (n-1) || index <= 0) ? -1 : arr[(index-1)/2];
}

float get_left_value(float arr[], int n, int index) {
    // DONE
    // left is 2n+1
    return (2*index + 1 > (n-1) || index < 0) ? -1 : arr[index*2 + 1];
}

float get_right_value(float arr[], int n, int index) {
    // DONE
    // right is 2n+2
   
    return (2*index + 2 > (n-1) || index < 0) ? -1 : arr[index*2 + 2];
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
