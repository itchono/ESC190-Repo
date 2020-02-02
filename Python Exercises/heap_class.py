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

        I.E. BUBBLE UPWARDS
        '''
        self.heap.append(element)
        cur_index = self.size() - 1
        while cur_index > 0:
            parent_index = (cur_index - 1) // 2
            if self.heap[parent_index] < self.heap[cur_index]:
                self.heap[parent_index], self.heap[cur_index] = self.heap[cur_index], self.heap[parent_index]
                cur_index = parent_index
            else:
                break

    def dequeue(self):
        '''
        Extract the maximum element such that the max heap property is satisfied
        Swap the first and last element, then swap the new root with the maximum
        of its children until the max heap property is satisfied
        '''
        if self.size() == 0:
            print('Heap is empty')
            return None
        
        removed_element = self.heap[0]
        self.heap[0] = self.heap.pop() # swap with last element
        last_index = len(self.heap) - 1
        cur_index = 0
        left_index, right_index = 1, 2
        while right_index <= last_index or left_index <= last_index:

            # find maximum child
            if right_index <= last_index:
                max_child = max(self.heap[left_index], self.heap[right_index])
                swap_index = left_index if max_child == self.heap[left_index] else right_index
            else:
                max_child = self.heap[left_index]
                swap_index = left_index
            if self.heap[cur_index] < max_child:
                self.heap[cur_index], self.heap[swap_index] = self.heap[swap_index], self.heap[cur_index]
                cur_index = swap_index
                left_index = 2*cur_index + 1
                right_index = 2*cur_index + 2
            else:
                break
        return removed_element

    def change_priority(self, element, new_priority):
        '''
        Change the priority of element to new_priority
        '''
        i = self.heap.index(element)
        self.heap[i] = new_priority

        cLeft = 2*i + 1
        cRight = 2*i + 2

        last = len(self.heap) - 1

        parent = (i-1)//2

        if self.heap[i] > self.heap[parent]:
            while i > 0 and self.heap[i] > self.heap[parent]:
                self.heap[i], self.heap[parent] = self.heap[parent], self.heap[i]
                i = parent
                parent = (i-1)//2
        
        elif self.heap[i] < self.heap[cLeft] or self.heap[i] < self.heap[cRight]:
            while cLeft <= last or cRight <= last:
                # find maximum child
                if cRight <= last:
                    swap_index = cLeft if self.heap[cLeft] > self.heap[cRight] else cRight
                else:
                    swap_index = cLeft
                if self.heap[i] < self.heap[swap_index]:
                    self.heap[i], self.heap[swap_index] = self.heap[swap_index], self.heap[i]
                    i = swap_index
                    cLeft = 2*i + 1
                    cRight = 2*i + 2
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
       pass

    def dequeue(self):
        '''
        Extract the minimum element such that the min heap property is satisfied
        Swap the first and last element, then swap the new root with the minimum
        of its children until the min heap property is satisfied
        '''
        pass

    def change_priority(self, element, new_priority):
        '''
        Change the priority of element to new_priority
        '''
        # Try implementing
        pass

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

    print("Change Prio test")
    max_heap.change_priority(6, 0)
    max_heap.display()

    # Remove from the heap
    print('Testing removing from our max heap')
    dequeued_element = max_heap.dequeue()
    print('Dequeued element is {}'.format(dequeued_element))
    max_heap.display()

    dequeued_element = max_heap.dequeue()
    print('Dequeued element is {}'.format(dequeued_element))
    max_heap.display()

    