from heap_class import MaxHeap

def heap_sort(heap_arr:MaxHeap):
    '''
    Given a heap implemented as an array, return a sorted list by using the heap sort algorithm
    '''
    out = []

    while heap_arr.size() > 0:
        out.append(heap_arr.dequeue())

    return out[-1::-1]

def heap_sort_in_place(heap_arr):
    '''
    Given a heap represented as an array, sort the array in place using the heap sort algorithm
    '''
    

    pass

def heapify(arr):
    '''
    Given a list arr, return a list in max heap order in O(n) time (i.e. level-order of a max heap)
    For example, the list [1,2,3,4,5] would return [5,4,3,1,2]
    '''
    return []

def merge_sorted_lists(sorted_lists):
    '''
    Given a list of sorted lists, return a single list that merges them in O(nlogk) time complexity
    where n is the total number of elements in the lists and k is the number of lists
    Hint: Use a min heap
    '''
    return []

def is_heap(arr):
    '''
    Given a list arr, check whether it represents a valid min heap
    '''
    return False