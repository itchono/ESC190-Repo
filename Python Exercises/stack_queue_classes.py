class StackArray:
    def __init__(self):
        '''
        Initialize an empty stack
        In this implementation, the end of the array is the top of the stack
        '''
        self.stack = []
    
    def size(self):
        '''
        Return the size of the stack
        '''
        return len(self.stack)

    def is_empty(self):
        '''
        Returns a boolean signifying whether the stack is empty
        '''
        if self.size() == 0:
            return True
        return False
    
    def push(self, element):
        '''
        Push an element onto the stack (right of the array)
        '''
        self.stack.append(element)
    
    def pop(self):
        '''
        Pop an element from the stack and return it. Report underflow if stack is empty
        '''
        if self.is_empty():
            print('Stack underflow')
            return None
        return self.stack.pop()

    def top(self):
        '''
        Return the top element of the stack
        '''
        if self.is_empty():
            return None
        return self.stack[-1]

    def display(self):
        '''
        Print the contents of the stack where the top is at the right
        '''
        print(self.stack)

class QueueArray:
    def __init__(self):
        '''
        Initialize an empty queue
        In this implementation, the beginning of the array is the head of the queue
        and the end of the array is the tail of the queue
        '''
        self.queue = []

    def size(self):
        '''
        Return the size of the queue
        '''
        return len(self.queue)

    def is_empty(self):
        '''
        Returns a boolean signifying whether the stack is empty
        '''
        if self.size() == 0:
            return True
        return False
    
    def enqueue(self, element):
        self.queue.append(element)
    
    def dequeue(self):
        if self.is_empty():
            print('Queue underflow')
            return None
        return self.queue.pop(0)

    def head(self):
        '''
        Return the head of the queue
        '''
        if self.is_empty():
            return None
        return self.queue[0]

    def tail(self):
        '''
        Return the tail of the queue
        '''
        if self.is_empty():
            return None
        return self.queue[-1]
    
    def display(self):
        '''
        Print the contents of the queue where the head is at the left and the tail is at the right
        '''
        print(self.queue)

class LinkedListNode:
    def __init__(self, data=0, next=None, prev=None):
        self.data = data
        self.next = next

    def __repr__(self):
        node = self
        first = True
        result = ''
        while node:
            if first:
                first = False
            else:
                result += ' --> '
            result += str(node.data)
            node = node.next

        return result

    def __str__(self):
        return self.__repr__()

class StackLinkedList:
    def __init__(self):
        '''
        Initialize an empty stack
        In this implementation, the head of the linked list is the top of the stack
        '''
        self.top_node = None

    def size(self):
        '''
        Return the size of the stack
        '''
        cur_node = self.top_node
        count = 0
        while cur_node:
            count += 1
            cur_node = cur_node.next
        return count
    
    def is_empty(self):
        '''
        Return a boolean signifying whether the stack is empty
        '''
        if self.size() == 0:
            return True
        return False

    def push(self, element):
        '''
        Push a new element onto the stack's top
        '''
        if not self.top_node:
            self.top_node = LinkedListNode(element)
        else: # Update the linked list to have a new top
            new_top_node = LinkedListNode(element)
            new_top_node.next = self.top_node
            self.top_node = new_top_node

    def pop(self):
        '''
        Pop an element from the stack's top
        '''
        if self.is_empty():
            return None
        # Update the linked list to have a new top and return the old one
        removed_node = self.top_node
        self.top_node = self.top_node.next
        return removed_node.data

    def top(self):
        '''
        Return the top element from the stack
        '''
        if self.is_empty():
            print('Stack underflow')
            return None
        return self.top_node.data
    
    def display(self):
        '''
        Print the contents of the stack where the top is at the left
        '''
        print(self.top_node)

class QueueLinkedList:
    def __init__(self):
        '''
        Initialize an empty queue
        In this implementation, the head of the linked list is the head of the queue
        and the tail of the linked list is the tail of the queue
        '''
        self.head_node = None
        self.tail_node = None
    
    def size(self):
        '''
        Return the size of the queue
        '''
        cur_node = self.head_node
        count = 0
        while cur_node:
            count += 1
            cur_node = cur_node.next
        return count

    def is_empty(self):
        '''
        Return a boolean signifying whether the stack is empty
        '''
        if self.size() == 0:
            return True
        return False

    def enqueue(self, element):
        '''
        Enqueue an element to the queue's tail
        '''
        new_node = LinkedListNode(element)
        if self.head_node == None:
            self.head_node = new_node
            self.tail_node = new_node
        else: # Update the linked list to have a new tail
            self.tail_node.next = new_node
            self.tail_node = new_node

    def dequeue(self):
        '''
        Dequeue an element from the queue's head
        '''
        if self.is_empty():
            print('Queue underflow')
            return None
        # Update the linked list to have a new head and return the old one
        removed_node = self.head_node
        self.head_node = self.head_node.next
        if not self.head_node: # If we remove the last element, then the tail needs to be updated to None
            self.tail_node = None
        return removed_node.data

    def head(self):
        '''
        Return the head of the queue
        '''
        if self.is_empty():
            print('Queue underflow')
            return None
        return self.head_node.data

    def tail(self):
        '''
        Return the tail of the queue
        '''
        if self.is_empty():
            print('Queue underflow')
            return None
        return self.tail_node.data

    def display(self):
        '''
        Print the contents of the queue where the head is at the left and the tail is at the right
        '''
        print(self.head_node)

if __name__ == '__main__':
    # Create stack array
    stack_array = StackArray()
    print('Testing our stack array')

    # Push elements to stack array
    stack_array.push(10)
    stack_array.push(13)
    stack_array.push(15)
    stack_array.display()

    # Pop element from stack array
    popped_element = stack_array.pop()
    print('Popped element is {}'.format(popped_element))
    stack_array.display()

    # Test other methods
    print('Is stack empty: {}'.format(stack_array.is_empty()))
    print('Top of the stack: {}'.format(stack_array.top()))

    print('')

    # Create queue array
    queue_array = QueueArray()
    print('Testing our queue array')

    # Enqueue elements to queue array
    queue_array.enqueue(10)
    queue_array.enqueue(13)
    queue_array.enqueue(15)
    queue_array.display()

    # Dequeue element from queue array
    dequeued_element = queue_array.dequeue()
    print('Dequeued element is {}'.format(dequeued_element))
    queue_array.display()

    # Test other methods
    print('Is queue empty: {}'.format(queue_array.is_empty()))
    print('Head of the queue: {}'.format(queue_array.head()))
    print('Tail of the queue: {}'.format(queue_array.tail()))

    print('')

    # Create stack linked list
    stack_linked_list = StackLinkedList()
    print('Testing our stack linked list')

    # Push elements to stack linked list
    stack_linked_list.push(10)
    stack_linked_list.push(13)
    stack_linked_list.push(15)
    stack_linked_list.display()

    # Pop element from stack linked list
    popped_element = stack_linked_list.pop()
    print('Popped element is {}'.format(popped_element))
    stack_linked_list.display()

    # Test other methods
    print('Is stack empty: {}'.format(stack_linked_list.is_empty()))
    print('Top of the stack: {}'.format(stack_linked_list.top()))

    print('')

    # Create queue linked list
    queue_linked_list = QueueLinkedList()
    print('Testing our queue linked list')

    # Enqueue elements to queue linked list
    queue_linked_list.enqueue(10)
    queue_linked_list.enqueue(13)
    queue_linked_list.enqueue(15)
    queue_linked_list.display()

    # Dequeue element from queue linked list
    dequeued_element = queue_linked_list.dequeue()
    print('Dequeued element is {}'.format(dequeued_element))
    queue_linked_list.display()

    # Test other methods
    print('Is queue empty: {}'.format(queue_linked_list.is_empty()))
    print('Head of the queue: {}'.format(queue_linked_list.head()))
    print('Tail of the queue: {}'.format(queue_linked_list.tail()))