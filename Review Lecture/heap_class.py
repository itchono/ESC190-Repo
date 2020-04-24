class MaxHeap:
    def __init__(self):
        '''
        Initialize an empty heap
        In this implementation, we will represent the heap as an array
        '''
        self.heap = []

    def size(self):
        '''
        Return the size of the heap
        '''
        return len(self.heap)

    def enqueue(self, element):
        '''
        Insert a new element such that the max heap property is satisfied
        After appending the new element, swap with the parent until the max heap property is satisfied
        '''
        self.heap.append(element)
        cur_index = self.size() - 1
        while cur_index > 0:
            parent_index = (cur_index - 1) // 2
            if self.heap[parent_index] < self.heap[cur_index]:
                self.heap[parent_index], self.heap[cur_index] = self.heap[cur_index], self.heap[parent_index]
                cur_index = parent_index
            else:
                return

    def dequeue(self):
        '''
        Extract the maximum element such that the max heap property is satisfied
        Swap the first and last element, then swap the new root with the maximum
        of its children until the max heap property is satisfied
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
                max_child = max(self.heap[left_index], self.heap[right_index])
                swap_index = left_index if max_child == self.heap[left_index] else right_index
            else:
                max_child = self.heap[left_index]
                swap_index = left_index
            if self.heap[cur_index] < max_child:
                self.heap[cur_index], self.heap[swap_index] = self.heap[swap_index], self.heap[cur_index]
                cur_index = swap_index
                left_index, right_index = 2*cur_index + 1, 2*cur_index + 2
            else:
                break
        return removed_element

    def change_priority(self, element, new_priority):
        '''
        Change the priority of element to new_priority
        '''
        self.heap[element] = new_priority
        last_index, parent_index, left_index, right_index = self.size() - 1, (element - 1) // 2, 2*element + 1, 2*element + 2
        if parent_index >= 0 and self.heap[parent_index] < self.heap[element]: # Check if we need to bubble up
            self.heap[parent_index], self.heap[element] = self.heap[element], self.heap[parent_index]
            curr_index = parent_index
            while curr_index > 0:
                parent_index = (curr_index - 1) // 2
                if self.heap[parent_index] < self.heap[curr_index]:
                    self.heap[parent_index], self.heap[curr_index] = self.heap[curr_index], self.heap[parent_index]
                    curr_index = parent_index
                else:
                    break
        else: # Check if we need to bubble down
            cur_index  = element
            while right_index <= last_index or left_index <= last_index:
                if right_index <= last_index:
                    max_child = max(self.heap[left_index], self.heap[right_index])
                    swap_index = left_index if max_child == self.heap[left_index] else right_index
                else:
                    max_child = self.heap[left_index]
                    swap_index = left_index
                if self.heap[cur_index] < max_child:
                    self.heap[cur_index], self.heap[swap_index] = self.heap[swap_index], self.heap[cur_index]
                    cur_index = swap_index
                    left_index, right_index = 2*cur_index + 1, 2*cur_index + 2
                else:
                    break

    def display(self):
        '''
        Print the current heap in level (breadth first) - order
        '''
        print(self.heap)

class MinHeap:
    def __init__(self):
        '''
        Initialize an empty heap
        In this implementation, we will represent the heap as an array
        '''
        self.heap = []

    def size(self):
        '''
        Return the size of the heap
        '''
        return len(self.heap)

    def enqueue(self, element):
        '''
        Insert a new element such that the min heap property is satisfied
        After appending the new element, swap with the parent until the min heap property is satisfied
        '''
        self.heap.append(element)
        cur_index = self.size() - 1
        while cur_index > 0:
            parent_index = (cur_index - 1) // 2
            if self.heap[parent_index] > self.heap[cur_index]:
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
            if self.heap[cur_index] > min_child:
                self.heap[cur_index], self.heap[swap_index] = self.heap[swap_index], self.heap[cur_index]
                cur_index = swap_index
                left_index, right_index = 2*cur_index + 1, 2*cur_index + 2
            else:
                break
        return removed_element

    def change_priority(self, element, new_priority):
        '''
        Change the priority of element to new_priority
        '''
        # Try implementing
        self.heap[element] = new_priority
        last_index, parent_index, left_index, right_index = self.size() - 1, (element - 1) // 2, 2*element + 1, 2*element + 2
        if parent_index >= 0 and self.heap[parent_index] > self.heap[element]: # Check if we need to bubble up
            self.heap[parent_index], self.heap[element] = self.heap[element], self.heap[parent_index]
            curr_index = parent_index
            while curr_index > 0:
                parent_index = (curr_index - 1) // 2
                if self.heap[parent_index] > self.heap[curr_index]:
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
                if self.heap[cur_index] > min_child:
                    self.heap[cur_index], self.heap[swap_index] = self.heap[swap_index], self.heap[cur_index]
                    cur_index = swap_index
                    left_index, right_index = 2*cur_index + 1, 2*cur_index + 2
                else:
                    break

    def display(self):
        '''
        Print the current heap in level (breadth first) - order
        '''
        print(self.heap)

if __name__ == '__main__':
    # Create maximum heap
    max_heap = MaxHeap()
    print('Testing adding to our max heap')

    # Add to the heap
    max_heap.enqueue(1)
    max_heap.display()

    max_heap.enqueue(2)
    max_heap.display()

    max_heap.enqueue(3)
    max_heap.display()

    max_heap.enqueue(4)
    max_heap.display()

    max_heap.enqueue(5)
    max_heap.display()

    max_heap.enqueue(6)
    max_heap.display()

    print('')

    # Remove from the heap
    print('Testing removing from our max heap')
    dequeued_element = max_heap.dequeue()
    print('Dequeued element is {}'.format(dequeued_element))
    max_heap.display()

    dequeued_element = max_heap.dequeue()
    print('Dequeued element is {}'.format(dequeued_element))
    max_heap.display()

    max_heap.change_priority(1, -1)
    print('Changed Heap')
    max_heap.display()


    # Create minimum heap
    min_heap = MinHeap()
    print('Testing adding to our min heap')

    # Add to the heap
    min_heap.enqueue(1)
    min_heap.display()

    min_heap.enqueue(2)
    min_heap.display()

    min_heap.enqueue(3)
    min_heap.display()

    min_heap.enqueue(4)
    min_heap.display()

    min_heap.enqueue(5)
    min_heap.display()

    min_heap.enqueue(6)
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

    min_heap.change_priority(1, 7)
    print('Changed Heap')
    min_heap.display()