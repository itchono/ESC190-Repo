from heap_class import MinHeap, MaxHeap

def heap_sort(heap_arr):
    '''
    Given a heap implemented as an array, return a sorted list by using the heap sort algorithm
    '''
    result, max_heap = [], MaxHeap()
    max_heap.heap = heap_arr
    while heap_arr:
        result.insert(0, max_heap.dequeue())
    return result

def heap_sort_in_place(heap_arr):
    '''
    Given a heap represented as an array, sort the array in place using the heap sort algorithm
    '''
    # General approach is to split the array into a heap and a sorted array, starting off with the whole array as a heap
    # Then keep dequeuing from the heap partition and insert into the sorted partition
    size_heap = len(heap_arr)
    while size_heap: # Continue dequeuing heap until the heap partition is empty
        heap_arr[0], heap_arr[size_heap - 1] = heap_arr[size_heap - 1], heap_arr[0]
        size_heap -= 1
        curr_index, left_index, right_index, last_index = 0, 1, 2, size_heap - 1
        while right_index <= last_index or left_index <= last_index:
            if right_index <= last_index:
                max_child = max(heap_arr[left_index], heap_arr[right_index])
                swap_index = left_index if max_child == heap_arr[left_index] else right_index
            else:
                max_child = heap_arr[left_index]
                swap_index = left_index
            if heap_arr[curr_index] < max_child:
                heap_arr[curr_index], heap_arr[swap_index] = heap_arr[swap_index], heap_arr[curr_index]
                curr_index = swap_index
                left_index, right_index = 2*curr_index + 1, 2*curr_index + 2
            else:
                break

def heapify(arr):
    '''
    Given a list arr, return a list in max heap order in O(n) time (i.e. level-order of a max heap)
    For example, the list [1,2,3,4,5] would return [5,4,3,1,2]
    '''
    last_index = len(arr) - 1
    for curr_index in range(len(arr)//2 - 1, -1, -1):
        left_index, right_index = 2*curr_index + 1, 2*curr_index + 2
        while right_index <= last_index or left_index <= last_index:
            if right_index <= last_index:
                max_child = max(arr[left_index], arr[right_index])
                swap_index = left_index if max_child == arr[left_index] else right_index
            else:
                max_child = arr[left_index]
                swap_index = left_index
            if arr[curr_index] < max_child:
                arr[curr_index], arr[swap_index] = arr[swap_index], arr[curr_index]
                curr_index = swap_index
                left_index, right_index = 2*curr_index + 1, 2*curr_index + 2
            else:
                break

    return arr

def merge_sorted_lists(sorted_lists):
    '''
    Given a list of sorted lists, return a single list that merges them in O(nlogk) time complexity
    where n is the total number of elements in the lists and k is the number of lists
    Hint: Use a min heap
    '''

    # We create a new class called MinHeapTuple to help with this problem
    merged_list, min_heap, index, not_empty = [], MinHeapTuple(), 0, False
    for i in range(len(sorted_lists)): # Build a min heap of smallest entries in each list
        if sorted_lists[i]:
            not_empty = True
            min_heap.enqueue((sorted_lists[i].pop(0), i))
    if not_empty: 
        smallest, index = min_heap.dequeue()
        merged_list.append(smallest)

    while True: # Continue adding elements one at a time to the min heap and take out the minimum element
        if sorted_lists[index]: # Check if the last list we popped from has another element to enqueue to the heap
            min_heap.enqueue((sorted_lists[index].pop(0), index))
            smallest, index = min_heap.dequeue() 
        elif min_heap.size(): # No more entries in current list, so just take out the next minimum element from the heap
            smallest, index = min_heap.dequeue()
        else: # Min heap is empty, so we're done
            break
        merged_list.append(smallest)

    return merged_list

def is_heap(arr):
    '''
    Given a list arr, check whether it represents a valid min heap
    Here we allow weak inequalities
    '''
    size_arr = len(arr)
    max_i = size_arr//2 - 1
    for i in range(max_i + 1):
        if i < max_i:
            if arr[i] > arr[2*i + 1] or arr[i] > arr[2*i + 1]:
                return False
        elif 2*i + 2 < size_arr:
            if arr[i] > arr[2*i + 2]:
                return False
        else:
            if arr[i] > arr[2*i + 1]:
                return False

    return True

class MinHeapTuple(MinHeap):
    # This min heap uses tuple entries where the priority is the first element of the tuple
    def __init__(self):
        super().__init__()

    def enqueue(self, element):
        '''
        Insert a new element such that the min heap property is satisfied
        After appending the new element, swap with the parent until the min heap property is satisfied
        '''
        self.heap.append(element)
        cur_index = self.size() - 1
        while cur_index > 0:
            parent_index = (cur_index - 1) // 2
            if self.heap[parent_index][0] > self.heap[cur_index][0]:
                self.heap[parent_index], self.heap[cur_index] = self.heap[cur_index], self.heap[parent_index]
                cur_index = parent_index
            else:
                return

    def dequeue(self):
        '''
        Extract the minimum element such that the min heap property is satisfied
        Swap the first and last element, then swap the new root with the minimum
        of its children until the min heap property is satisfied
        '''
        if self.size() == 0:
            print('Heap is empty')
            return None
        elif self.size() == 1:
            return self.heap.pop()
        
        removed_element = self.heap[0]
        self.heap[0] = self.heap.pop()
        cur_index, left_index, right_index, last_index = 0, 1, 2, len(self.heap) - 1
        while right_index <= last_index or left_index <= last_index:
            if right_index <= last_index:
                min_child = min(self.heap[left_index], self.heap[right_index])
                swap_index = left_index if min_child == self.heap[left_index] else right_index
            else:
                min_child = self.heap[left_index]
                swap_index = left_index
            if self.heap[cur_index][0] > min_child[0]:
                self.heap[cur_index], self.heap[swap_index] = self.heap[swap_index], self.heap[cur_index]
                cur_index = swap_index
                left_index, right_index = 2*cur_index + 1, 2*cur_index + 2
            else:
                break
        return removed_element

    def change_priority(self, element, new_priority):
        '''
        Change the priority of element to new_priority (tuple version)
        '''
        self.heap[element] = new_priority
        last_index, parent_index, left_index, right_index = self.size() - 1, (element - 1) // 2, 2*element + 1, 2*element + 2
        if parent_index >= 0 and self.heap[parent_index][0] > self.heap[element][0]: # Check if we need to bubble up
            self.heap[parent_index], self.heap[element] = self.heap[element], self.heap[parent_index]
            curr_index = parent_index
            while curr_index > 0:
                parent_index = (curr_index - 1) // 2
                if self.heap[parent_index][0] > self.heap[curr_index][0]:
                    self.heap[parent_index], self.heap[curr_index] = self.heap[curr_index], self.heap[parent_index]
                    curr_index = parent_index
                else:
                    break
        else: # Check if we need to bubble down
            cur_index  = element
            while right_index <= last_index or left_index <= last_index:
                if right_index <= last_index:
                    min_child = min(self.heap[left_index], self.heap[right_index])
                    swap_index = left_index if min_child == self.heap[left_index] else right_index
                else:
                    min_child = self.heap[left_index]
                    swap_index = left_index
                if self.heap[cur_index][0] > min_child[0]:
                    self.heap[cur_index], self.heap[swap_index] = self.heap[swap_index], self.heap[cur_index]
                    cur_index = swap_index
                    left_index, right_index = 2*cur_index + 1, 2*cur_index + 2
                else:
                    break

if __name__ == '__main__':
    heap = [59, 42, 55, 37, 40, 7]
    print('Printing heap')
    print(heap)

    # Test heap_sort
    print('Testing heap sort')
    print('Sorted list:', heap_sort(heap))

    # Test heap_sort_in_place
    print('Testing heap sort in place')
    heap_sort_in_place(heap)
    print('Sorted list:', heap)
    
    # Test heapify
    arr = [1, 4, 5, 7, 8, 3]
    print('Original array:', arr)
    print('Heapified array:', heapify(arr))

    # Test merged_sorted_lists
    list1, list2, list3 = [1,5,7,9,10], [2, 5, 6, 8], [0, 4, 6, 7]
    print('Testing merged sorted lists')
    print('Sorted lists:', list1, list2, list3)
    print('Merged list:', merge_sorted_lists([list1, list2, list3]))

    # Testing is_heap
    arr = [7, 3, 5, 2, 1]
    print('Testing is_heap on', arr)
    print(is_heap(arr))
    arr = [1, 2, 5, 3, 7, 6]
    print('Testing is_heap on', arr)
    print(is_heap(arr))

    # Test MinHeapTuple 
    min_heap = MinHeapTuple()
    print('Testing adding to our min heap')

    # Add to the heap
    min_heap.enqueue((1, 0))
    min_heap.display()

    min_heap.enqueue((2, 0))
    min_heap.display()

    min_heap.enqueue((3, 0))
    min_heap.display()

    min_heap.enqueue((4, 0))
    min_heap.display()

    min_heap.enqueue((5, 0))
    min_heap.display()

    min_heap.enqueue((6, 0))
    min_heap.display()

    print('')

    # Remove from the heap
    print('Testing removing from our min heap')
    dequeued_element = min_heap.dequeue()
    print('Dequeued element is {}'.format(dequeued_element))
    min_heap.display()

    dequeued_element = min_heap.dequeue()
    print('Dequeued element is {}'.format(dequeued_element))
    min_heap.display()

    min_heap.change_priority(1, (7, 0))
    print('Changed Heap')
    min_heap.display()