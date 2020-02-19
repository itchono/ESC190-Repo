#include "lab2.h"
#include <math.h>

void heapifyHelper(float arr[], int n, int i);

void print_tree(float arr[], int n) {
    // breadth first traversal
    int *queue = calloc(n, sizeof(int)); // dynamically sized queue
    // queue indices of array

    int numRows = log2(n)+1;

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

        int numSpaces = exp2(numRows-rowNumber+1)-2; // baseline spaces assuming NO width of members. so, we must add those on.

        // do a left-traversal to check spacing
        int j = level[0]; // pointer for this traversal


        while(2*j + 1 <= (n-1) && j >= 0) {
          numSpaces += ((int) (log10(arr[j]))+1); // get the number of spaces the character takes up

          j = 2*j + 1;
        }
        numSpaces --; // round down for conservation

        for (int y = 0; y < numSpaces; y++) {
          // print the actual spaces
          printf(" ");
        }

        // Stage 2: Values and interstitial spaces
        for (int x = 0; x < levelptr; x++) {
            printf("%g", arr[level[x]]);

            if (rowNumber != 0) { // TBD: CHECK if I need to print the rest of the interstitial spaces

              int numSpaces = exp2(2+(numRows-rowNumber)); // baseline spaces assuming NO width of members. so, we must add those on.

              float L = get_left_value(arr, n, level[x]);
              float R = get_right_value(arr, n, level[x]);

              // complex space determination
              if (L != -1) {
                numSpaces += log10(L)+1;
              }
              else if (R != -1) {
                numSpaces += log10(R)+1;
              }
              else if (L!= -1 && R != -1) {
                numSpaces += (log10(L)+1 + log10(R)+1)/2;
              }

              for (int y = 0; y < numSpaces; y++) {
                printf(" ");
              }
            } 
        }

        free(level); // clear memory
        printf("\n"); // nextline
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
  // DONE
    int *queue = calloc(n, sizeof(int)); // dynamically sized queue
    // queue indices of array

    int numRows = log2(n)+1;

    queue[0] = 0; // enqueue root

    int queueSize = 1;
    int queueStart = 0;
    int queueEnd = 1;

    while (queueSize > 0) {
        int* level = calloc(n, sizeof(int)); // a sub-list of the current level
        int levelptr = 0; // indicate which level we are currently on

        int qs = queueStart; // fixed pointers for sizing
        int qe = queueEnd;

        for (int x = qs; x < qe; x++) {

            int i = queue[x]; // index which we will be putting through arr to output.

            queueStart ++; // dequeue the current node we are on
            queueSize --;

            level[levelptr] = i;
            levelptr ++; // enqueue current node at a level

            if (get_left_value(arr, n, i) != -1) {
                queue[queueEnd] = 2*i+1;

                if (get_left_value(arr, n, i) > arr[i]) {
                  return 0; // check for delinquent child
                }
                queueEnd ++; // enqueue
                queueSize ++;
            }
            if (get_right_value(arr, n, i) != -1) {
                queue[queueEnd] = 2*i+2;

                if (get_right_value(arr, n, i) > arr[i]) {
                  return 0; // check for delinquent child
                }
                queueEnd ++; // enqueue
                queueSize ++;
            }
        }
    }

    return 1;
}

void heapify(float arr[], int n) {
  // DONE

  for (int x = n/2-1; x >= 0; x--) {
    heapifyHelper(arr, n, x);
  }
    
}

void heapifyHelper(float arr[], int n, int i) {
  // borrowed from python exercises

  int max = i;
    int L = 2*i + 1;
    int R = 2*i + 2;
  
    // find the maiimum value of the children
    if (L < n && arr[L] > arr[max]) {
        max = L; 
    }
  
    if (R < n && arr[R] > arr[max]) {
        max = R;
    }
  
    // bring max to root
    if (max != i) { 
        float temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
  
        heapifyHelper(arr, n, max); // call same function recursively
    } 
}

void heapsort(float arr[], int n) {
  // DONE
  // builds upon heapify stuff
    
    // heapify array
    heapify(arr, n);

    // use the idea of sorted and unsorted partitions

    for (int x = n-1; x>=0; x--) {

      float temp = arr[x];
      arr[x] = arr[0];
      arr[0] = temp;

      // dequeue root (max) to the end

      heapify(arr, x); // heapify an array of remaining size
    }
}

float find_most_common_element(float arr[], int n) {
    // DONE
    // can use a sorted list to speed things up

    heapsort(arr, n);

    int repetitionMax = 0;
    int repeats = 0;
    float mode = -1;

    if (n == 1) {
      return arr[0];
    }
    else {
      for (int x = 1; x < n; x ++) {
        if (arr[x] == arr[x-1]) {
          repeats ++;
        }
        else {
          // "Combo" has been broken; collect data
          if (repeats > repetitionMax) {
            mode = arr[x-1];
            repetitionMax = repeats;
          }

          repeats = 0; // reset repeats for next one
        }
      }
    }

    return mode;


}
