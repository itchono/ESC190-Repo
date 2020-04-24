#include "lab2.h"
#include <math.h>
#include <stdlib.h>

void heapifyHelper(float arr[], int n, int i);

void print_tree(float arr[], int n) {
    // PRINT TREE !!!!!
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

        int bonusSpcL = 0;
        int bonusSpcR = 0;

        // HERE BE DRAGONS

        // Determine left and right spacings, averaging if needed

        if (get_left_value(arr, n, level[0])!= -1) {
          // do a Level order traversal on the left for spacing
          int *q = calloc(n, sizeof(int)); // queue

          q[0] = 2*level[0]+1; // pointer for this traversal start

          int qSize = 1;
          int qStart = 0;
          int qEnd = 1;
          int rNumber = rowNumber+1;

          while (qSize > 0) {
              int* lvl = calloc(n, sizeof(int)); // a sub-list of the current level
              int lvlptr = 0; // indicate which level we are currently on

              int qs2 = qStart; // fixed pointers for sizing
              int qe2 = qEnd;

              for (int x = qs2; x < qe2; x++) {

                  int i = q[x]; // index which we will be putting through arr to output.

                  if (get_left_value(arr, n, i) == -1 || get_right_value(arr, n, i) == -1) {
                        // read only on the last line
                        bonusSpcL += ((int) (log10(arr[i]))+1); // get the number of spaces the character takes up
                  }

                  qStart ++; // dequeue the current node we are on
                  qSize --;

                  lvl[lvlptr] = i;
                  lvlptr ++; // enqueue current node at a level

                  if (get_left_value(arr, n, i) != -1) {
                      q[qEnd] = 2*i+1;
                      qEnd ++; // enqueue
                      qSize ++;
                  }
                  if (get_right_value(arr, n, i) != -1) {
                      q[qEnd] = 2*i+2;
                      qEnd ++; // enqueue
                      qSize ++;
                  }
              }
              rNumber ++;
          }
          free(q);
        }
        if (get_right_value(arr, n, level[0])!= -1) {
          // do a Level order traversal on the right for spacing
          int *q = calloc(n, sizeof(int)); // queue

          q[0] = 2*level[0]+2; // pointer for this traversal start

          int qSize = 1;
          int qStart = 0;
          int qEnd = 1;
          int rNumber = rowNumber+1;

          while (qSize > 0) {
              int* lvl = calloc(n, sizeof(int)); // a sub-list of the current level
              int lvlptr = 0; // indicate which level we are currently on

              int qs2 = qStart; // fixed pointers for sizing
              int qe2 = qEnd;

              for (int x = qs2; x < qe2; x++) {

                  int i = q[x]; // index which we will be putting through arr to output.

                  if (get_left_value(arr, n, i) == -1 || get_right_value(arr, n, i) == -1) {
                        // read only on the "last" line
                        bonusSpcR += ((int) (log10(arr[i]))+1); // get the number of spaces the character takes up
                  }

                  qStart ++; // dequeue the current node we are on
                  qSize --;

                  lvl[lvlptr] = i;
                  lvlptr ++; // enqueue current node at a level

                  if (get_left_value(arr, n, i) != -1) {
                      q[qEnd] = 2*i+1;
                      qEnd ++; // enqueue
                      qSize ++;
                  }
                  if (get_right_value(arr, n, i) != -1) {
                      q[qEnd] = 2*i+2;
                      qEnd ++; // enqueue
                      qSize ++;
                  }
              }
              rNumber ++;
          }
          free(q);
        }
        if (get_right_value(arr, n, level[0])!= -1 && get_left_value(arr, n, level[0])!= -1) {
           // take average
           int diff = bonusSpcR-bonusSpcL;
           numSpaces += (bonusSpcL + bonusSpcR)/2 -1;
        }
        else {
          numSpaces += (bonusSpcL + bonusSpcR - 1);
          // round down for conservation
        }  

        for (int y = 0; y < numSpaces; y++) {
          // print the actual spaces
          printf(" ");
        }

        // Stage 2: Values and interstitial spaces
        for (int x = 0; x < levelptr; x++) {
            printf("%g", arr[level[x]]);
              int numSpaces = exp2(2+(numRows-rowNumber)); // baseline spaces assuming NO width of members. so, we must add those on.

               // do a level order traversal on the RIGHT of the current node and the left of the next node
               // Here be dragons again
               if (rowNumber-1 != 0 && rowNumber != numRows) {

                 // Right traversal
                 if (get_right_value(arr, n, level[x])!= -1) {
                   int *q = calloc(n, sizeof(int)); // queue

                  q[0] = 2*level[x]+2; // pointer for this traversal start

                  int qSize = 1;
                  int qStart = 0;
                  int qEnd = 1;
                  int rNumber = rowNumber+1;

                  while (qSize > 0) {
                      int* lvl = calloc(n, sizeof(int)); // a sub-list of the current level
                      int lvlptr = 0; // indicate which level we are currently on

                      int qs2 = qStart; // fixed pointers for sizing
                      int qe2 = qEnd;

                      for (int x = qs2; x < qe2; x++) {

                          int i = q[x]; // index which we will be putting through arr to output.

                          // add spaces depending on RIGHT of current node and LEFT of next node in the level

                          if (get_left_value(arr, n, i) == -1 || get_right_value(arr, n, i) == -1) {
                                // read only on the last line
                                numSpaces += ((int) (log10(arr[i]))+1); // get the number of spaces the character takes up
                          }

                          qStart ++; // dequeue the current node we are on
                          qSize --;

                          lvl[lvlptr] = i;
                          lvlptr ++; // enqueue current node at a level

                          if (get_left_value(arr, n, i) != -1) {
                              q[qEnd] = 2*i+1;
                              qEnd ++; // enqueue
                              qSize ++;
                          }
                          if (get_right_value(arr, n, i) != -1) {
                              q[qEnd] = 2*i+2;
                              qEnd ++; // enqueue
                              qSize ++;
                          }
                      }
                      rNumber ++;
                  }
                  free(q);

                  numSpaces -= (int)(log10(arr[level[x]])); // round down for conservation
               }
                // Left traversal
                 if (get_left_value(arr, n, level[x+1])!= -1) {
                   int *q = calloc(n, sizeof(int)); // queue

                  q[0] = 2*level[x+1]+1; // pointer for this traversal start

                  int qSize = 1;
                  int qStart = 0;
                  int qEnd = 1;
                  int rNumber = rowNumber+1;

                  while (qSize > 0) {
                      int* lvl = calloc(n, sizeof(int)); // a sub-list of the current level
                      int lvlptr = 0; // indicate which level we are currently on

                      int qs2 = qStart; // fixed pointers for sizing
                      int qe2 = qEnd;

                      for (int x = qs2; x < qe2; x++) {

                          int i = q[x]; // index which we will be putting through arr to output.

                          // add spaces depending on RIGHT of current node and LEFT of next node in the level

                          if (get_left_value(arr, n, i) == -1 || get_right_value(arr, n, i) == -1) {
                                // read only on the last line
                                numSpaces += ((int) (log10(arr[i]))+1); // get the number of spaces the character takes up
                          }

                          qStart ++; // dequeue the current node we are on
                          qSize --;

                          lvl[lvlptr] = i;
                          lvlptr ++; // enqueue current node at a level

                          if (get_left_value(arr, n, i) != -1) {
                              q[qEnd] = 2*i+1;
                              qEnd ++; // enqueue
                              qSize ++;
                          }
                          if (get_right_value(arr, n, i) != -1) {
                              q[qEnd] = 2*i+2;
                              qEnd ++; // enqueue
                              qSize ++;
                          }
                      }
                      rNumber ++;
                  }
                  free(q);

                  numSpaces -= (int)(log10(arr[level[x]])); // round down for conservation
               }

              }

              for (int y = 0; y < numSpaces; y++) {
                printf(" ");
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
