#include "lab2.h"
#include "test.h"
#include <stdio.h>
/* Feel free to add things in to/take things out from the main function in your
 * debugging process! Remember that changes you make to this file will not be 
 * marked. */
int main () {
    float arr[7] = {90,8,7,6,5,4,3,2};
    //float arr[7] = {40, 20, 17, 16, 13, 15, 11};

    test_get_parent_value();
    test_get_left_value();
    test_get_right_value();
    test_is_max_heap();
    test_heapify();
    test_heapsort();
    test_find_most_common_element();

    print_tree(arr, 7);


    /*
    test_heapify();
    test_heapsort();
    test_find_most_common_element();
    */
    return 0;
}

