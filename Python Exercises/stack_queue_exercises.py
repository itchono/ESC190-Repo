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
    return False

def preorder_iterative(root):
    '''
    Given the root of a binary tree, complete preorder traversal without using recursion
    and return a list in this order
    '''
    return []

def postorder_iterative(root):
    '''
    Given the root of a binary tree, complete postorder traversal without using recursion
    and return a list in this order
    '''
    return []

def inorder_iterative(root):
    '''
    Given the root of a binary tree, complete inorder traversal without using recursion
    and return a list in this order
    '''
    return []

def reverse_string(text):
    '''
    Given a string text, return a reversed version of this string without using the reversed() function
    '''
    return ''

def postfix_evaluate(text):
    '''
    Given a string of digits and operations (+, -, *, /) in postfix order, calculate the result
    For example, the expression '12*6+' is equivalent to (1*2) + 6 = 8
    '''
    return 0

class StackWithMin(StackArray):
    def __init__(self):
        '''
        Augment the stack classes such that an addition method min() returns the minimum element in the stack
        '''
        super().__init__()
        # Add attributes here
    
    def min(self):
        '''
        Return the minimum element within the stack
        '''
        return None

# Queue exercises
def level_order(root):
    '''
    Given the root of a binary tree, return its level order traversal
    '''
    return []

def height(root):
    '''
    Given the root of a binary tree, return its height without using recursion
    '''
    return 0

def level_average(root):
    '''
    Given the root of a binary tree, return a list of averages of each level
    '''
    return []

def is_complete(root):
    '''
    Given the root of a binary tree, check if it is complete without using recursion
    '''
    return False

class QueueUsingStacks:
    '''
    Create a Queue class using two stacks
    '''