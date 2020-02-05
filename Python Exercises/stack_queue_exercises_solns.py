from stack_queue_classes import *
from avl_trees_tester import *

# Stack Exercises
def check_parentheses(text):
    '''
    Given a string text, check that all of its parentheses characters are matched in correct order,
    i.e. every left parenthesis is matched by its corresponding right parenthesis
    For example, the strings "[1, 2]", "[tup[1](7)]", and "{d: [5, 3, 2], e: (1, (2, 2))}" are correct,
    but the strings "[(3, 4])" "[[(1, 2]), 4, 3]]", and "{d: (1, 2)}}"
    Return a boolean signifying whether the parentheses are ordered correct
    '''
    stack, parentheses = StackArray(), {')': '(', ']': '[', '}': '{'}
    for c in text:
        if c in parentheses.values():
            stack.push(c)
        elif c in parentheses:
            if stack.is_empty() or not parentheses[c] == stack.pop():
                return False
    return True

def preorder_iterative(root):
    '''
    Given the root of a binary tree, complete preorder traversal without using recursion
    and return a list in this order
    '''
    stack, result = StackArray(), []
    if root:
        stack.push(root)
    while not stack.is_empty():
        curr_node = stack.pop()
        result.append(curr_node.data)
        if curr_node.right:
            stack.push(curr_node.right)
        if curr_node.left:
            stack.push(curr_node.left)
    return result

def postorder_iterative(root):
    '''
    Given the root of a binary tree, complete postorder traversal without using recursion
    and return a list in this order
    '''
    stack, result, prev_node = StackArray(), [], None
    if root:
        stack.push(root)
    while not stack.is_empty():
        curr_node = stack.top()
        if curr_node.left and not prev_node is curr_node.left and not prev_node is curr_node.right :
            stack.push(curr_node.left)
        elif curr_node.right and not prev_node is curr_node.right:
            stack.push(curr_node.right)
        else:
            result.append(stack.pop().data)
        prev_node = curr_node
    return result

def inorder_iterative(root):
    '''
    Given the root of a binary tree, complete inorder traversal without using recursion
    and return a list in this order
    '''
    stack, result, prev_node = StackArray(), [], None
    if root:
        stack.push(root)
    while not stack.is_empty():
        curr_node = stack.top()
        if prev_node is curr_node.left or not prev_node is curr_node.right and not curr_node.left and curr_node.right:
            result.append(curr_node.data)
        if curr_node.left and not prev_node is curr_node.left and not prev_node is curr_node.right:
            stack.push(curr_node.left)
        elif curr_node.right and not prev_node is curr_node.right:
            stack.push(curr_node.right)
        elif prev_node is curr_node.right or not curr_node.right and curr_node.left:
            stack.pop()
        else:
            result.append(stack.pop().data)
        prev_node = curr_node
    return result

def inorder_iterative_alternate(root):
    stack, result, curr_node = StackArray(), [], root
    while True:
        if curr_node:
            stack.push(curr_node)
            curr_node = curr_node.left
        elif not stack.is_empty():
            curr_node = stack.pop()
            result.append(curr_node.data)
            curr_node = curr_node.right
        else:
            break
    return result

def reverse_string(text):
    '''
    Given a string text, return a reversed version of this string without using the reversed() function
    '''
    stack, result = StackArray(), ''
    for c in text:
        stack.push(c)
    while not stack.is_empty():
        result += stack.pop()
    return result

def postfix_evaluate(text):
    '''
    Given a string of digits and operations (+, -, *, /) in postfix order, calculate the result
    For example, the expression '12*6+' is equivalent to (1*2) + 6 = 8
    '''
    stack = StackArray()
    for c in text:
        stack.push(c)
        if c in ['+', '-', '*', '/']:
            op = stack.pop()
            num1, num2 = int(stack.pop()), int(stack.pop())
            if op == '+':
                next_num = num1 + num2
            elif op == '-':
                next_num = num2 - num1
            elif op == '*':
                next_num = num1 * num2
            else:
                next_num = num2 / num1
            stack.push(next_num)
    return stack.pop()

class StackWithMin(StackArray):
    def __init__(self):
        '''
        Augment the stack class such that an additional method min() returns the minimum element in the stack
        In this implementation, for each element we store a 2-tuple, where the first element is the data and 
        the second element is the minimum of all elements below the stack including itself
        '''
        super().__init__()
    
    def push(self, element):
        '''
        Push an element onto the stack while keeping track of the current min (right of the array)
        '''
        self.stack.append((element, element if self.is_empty() else min(element, self.min())))

    def pop(self):
        return self.stack.pop()[0]

    def min(self):
        '''
        Return the minimum element within the stack
        '''
        return self.stack[-1][-1] if not self.is_empty() else None

    def top(self):
        '''
        Return the top element of the stack
        '''
        return self.stack[-1][0] if not self.is_empty() else None

# Queue exercises
def level_order(root):
    '''
    Given the root of a binary tree, return its level order traversal
    '''
    queue, result = QueueArray(), []
    if root:
        queue.enqueue(root)
    while not queue.is_empty():
        curr_node = queue.dequeue()
        result.append(curr_node.data)
        if curr_node.left:
            queue.enqueue(curr_node.left)
        if curr_node.right:
            queue.enqueue(curr_node.right)
        
    return result

def height(root):
    '''
    Given the root of a binary tree, return its height without using recursion
    '''
    queue, height = QueueArray(), -1
    if root:
        queue.enqueue(root)
    while not queue.is_empty():
        curr_size = queue.size()
        while curr_size:
            curr_node = queue.dequeue()
            if curr_node.left:
                queue.enqueue(curr_node.left)
            if curr_node.right:
                queue.enqueue(curr_node.right)
            curr_size -= 1
        height += 1
    return height

def level_average(root):
    '''
    Given the root of a binary tree, return a list of averages of each level
    '''
    queue, result = QueueArray(), []
    if root:
        queue.enqueue(root)
    while not queue.is_empty():
        curr_size, full_size, curr_sum = queue.size(), queue.size(), 0
        while curr_size:
            curr_node = queue.dequeue()
            curr_sum += curr_node.data
            if curr_node.left:
                queue.enqueue(curr_node.left)
            if curr_node.right:
                queue.enqueue(curr_node.right)
            curr_size -= 1
        result.append(float(curr_sum) / full_size)
    return result

def is_complete(root):
    '''
    Given the root of a binary tree, check if it is complete without using recursion
    Do a level-order traversal. If your current node has a child while the previous node
    does not, we cannot not have a complete tree. So keep track of whether a node has two
    children
    '''
    queue, has_two_children = QueueArray(), True
    if root:
        queue.enqueue(root)
    while not queue.is_empty():
        curr_node = queue.dequeue()
        if curr_node.left:
            if not has_two_children:
                return False
            queue.enqueue(curr_node.left)
            has_two_children = True
        else:
            has_two_children = False
        if curr_node.right:
            if not has_two_children:
                return False
            queue.enqueue(curr_node.right)
        else:
            has_two_children = False
    return True

class QueueUsingStacks:
    '''
    Create a Queue class using two stacks
    '''
    def __init__(self):
        self.enq_stack = StackArray()
        self.deq_stack = StackArray()

    def size(self):
        return self.enq_stack.size() + self.deq_stack.size()

    def is_empty(self):
        return self.enq_stack.is_empty() and self.deq_stack.is_empty()
    
    def enqueue(self, element):
        self.enq_stack.push(element)
    
    def dequeue(self):
        if self.deq_stack.is_empty():
            while not self.enq_stack.is_empty():
                self.deq_stack.push(self.enq_stack.pop())
        return self.deq_stack.pop()

    def head(self):
        if self.is_empty():
            return None
        elif not self.deq_stack.is_empty():
            return self.deq_stack.top()
        else:
            return self.enq_stack.stack[-1]

    def tail(self):
        if self.is_empty():
            return None
        elif not self.enq_stack.is_empty():
            return self.enq_stack.top()
        else:
            return self.deq_stack.stack[-1]
    
    def display(self):
        deq_list, enq_list = [], []
        if not self.deq_stack.is_empty():
            deq_list = self.deq_stack.stack[::-1]
        if not self.enq_stack.is_empty():
            enq_list = self.enq_stack.stack
        print(deq_list + enq_list)

if __name__ == '__main__':
    a = AVLTreeNode(14)
    b = AVLTreeNode(12)
    c = AVLTreeNode(27)
    d = AVLTreeNode(9)
    e = AVLTreeNode(13)
    f = AVLTreeNode(15)
    g = AVLTreeNode(5)
    h = AVLTreeNode(10)
    i = AVLTreeNode(19)
    j = AVLTreeNode(29)
    k = AVLTreeNode(12.5)
    l = AVLTreeNode(13.5)
    m = AVLTreeNode(14.5)

    tree = insert(a, b)
    tree = insert(tree, c)
    tree = insert(tree, e)
    tree = insert(tree, d)
    tree = insert(tree, f)
    tree = insert(tree, f)
    tree = insert(tree, g)
    tree = insert(tree, h)
    tree = insert(tree, i)
    tree = insert(tree, j)
    tree = insert(tree, k)
    tree = insert(tree, l)
    tree = insert(tree, m)

    print('Printing the tree. Note balance factors are not valid since we use this as a BST, not an AVL tree')
    print(tree)

    print('Testing preorder_iterative')
    print(preorder_iterative(tree))

    print('Testing postorder_iterative')
    print(postorder_iterative(tree))

    print('Testing inorder_iterative')
    print(inorder_iterative(tree))

    text = 'abcdef'
    print('Testing reverse_string on the string', text)
    print(reverse_string(text))

    text = '12*6+'
    print('Testing postfix evaluation on the characters', text)
    print(postfix_evaluate(text))

    text = '{d: (1, 2)}}'
    print('Testing check_parentheses on the text', text)
    print(check_parentheses(text))

    # Test StackMinArray
    stack_array = StackWithMin()
    print('Testing StackWithMin')

    # Push elements to stack array
    stack_array.push(10)
    stack_array.push(13)
    stack_array.push(15)
    stack_array.display()
    print('Minimum element:', stack_array.min())

    # Test level order
    print('Testing level_order on the tree above')
    print(level_order(tree))

    # Test height
    print('Testing height of the tree above')
    print(height(tree))
    
    # Test average
    print('Testing level_average on the tree above')
    print(level_average(tree))

    # Test is_complete
    print('Testing is_complete on the tree above')
    print(is_complete(tree))

    # Test QueueUsingStacks
    print('Testing QueueUsingStacks')
    queue = QueueUsingStacks()
    print('Enqueuing 2')
    queue.enqueue(2)
    queue.display()
    print('Enqueuing 1')
    queue.enqueue(1)
    queue.display()
    print('Enqueuing 22')
    queue.enqueue(22)
    queue.display()
    print('Enqueuing 25')
    queue.enqueue(25)
    queue.display()
    print('Dequeuing:', queue.dequeue())
    queue.display()
