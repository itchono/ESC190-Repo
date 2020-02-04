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

    charStk = StackArray()
    lookup = {"{":"}", "(":")", "[":"]"}

    for e in text:
        if e in lookup.keys():
            charStk.push(e)

        elif e == lookup[charStk.top()]:
            if not charStk.pop():
                return False # if stack is empty i.e. we are doing too many close-brackets

    return charStk.size() == 0

def preorder_iterative(root):
    '''
    Given the root of a binary tree, complete preorder traversal without using recursion
    and return a list in this order
    '''

    stk = StackArray()

    stk.push(root)

    out = []

    while stk.size() > 0:
        n = stk.pop()
        out.append(n)
        # parents are put onto the output list first

        if n.right:
            stk.push(n.right)
        if n.left:
            stk.push(n.left)
        # left child will end up on top of stack for next processing

    return out

def postorder_iterative(root):
    '''
    Given the root of a binary tree, complete postorder traversal without using recursion
    and return a list in this order
    '''
    callStack = StackArray()
    stk = StackArray()

    callStack.push(root)
    n = root

    while callStack.size() > 0:
    
        n = callStack.pop()

        if n.left:
            callStack.push(n.left)
        if n.right:
            callStack.push(n.right)
            # process rightmost nodes first so that they are first to be put onto output stack, therefore lefts will be first overall

        stk.push(n)
    
    return stk.stack[-1::-1]
        

def inorder_iterative(root):
    '''
    Given the root of a binary tree, complete inorder traversal without using recursion
    and return a list in this order
    '''
    callStack = StackArray()

    n = root

    out = []

    while callStack.size() > 0:
        while n:
            callStack.push(n)
            n = n.left
            # go left until you can't go left anymore

        i = callStack.pop()
        # push node to output
        out.append(i)

        n = i.right # go to right child (could be None, in which case we just pop the parent node)
    return out


def reverse_string(text):
    '''
    Given a string text, return a reversed version of this string without using the reversed() function
    '''

    stk = StackArray()

    out = ""

    for e in text:
        stk.push(e)

    while stk.size() > 0:
        out += stk.pop()

    return out

def postfix_evaluate(text):
    '''
    Given a string of digits and operations (+, -, *, /) in postfix order, calculate the result
    For example, the expression '12*6+' is equivalent to (1*2) + 6 = 8
    '''

    stk = StackArray()

    total = 0

    for c in text:
        if c in {'+', '-', '*', '/'}:
            total = stk.pop()

            while stk.size() > 0:
                if c == '+':
                    total += stk.pop()
                elif c == '-':
                    total -= stk.pop()
                elif c == "*":
                    total *= stk.pop()

            stk.push(total)
        else:
            stk.push(int(c))

    return total

class StackWithMin(StackArray):
    def __init__(self):
        '''
        Augment the stack classes such that an addition method min() returns the minimum element in the stack
        '''
        super().__init__()
    
    def min(self):
        '''
        Return the minimum element within the stack
        '''
        return min(self.stack)

# Queue exercises
def level_order(root):
    '''
    Given the root of a binary tree, return its level order traversal
    '''

    q = QueueArray()

    q.enqueue(root)

    out = []

    while q.size() > 0:
        n = q.dequeue()

        out.append(n)

        if n.left:
            q.enqueue(n.left)
        if n.right:
            q.enqueue(n.right)

    return []

def height(root):
    '''
    Given the root of a binary tree, return its height without using recursion
    '''
    h = -1

    queue = [root]

    while queue != []:

        currLvl = queue[:]
        queue = []

        for n in currLvl:
            if n is not None:
                queue.append(n.left)
                queue.append(n.right)

        h += 1
    return h

def level_average(root):
    '''
    Given the root of a binary tree, return a list of averages of each level
    '''
    h = -1
    queue = [root]

    lvlavg = []

    while queue != []:

        currLvl = queue[:]
        queue = []

        s = 0
        for n in currLvl:
            if n is not None:
                s += int(n.data)
        h += 1

        lvlavg[h] = s/len(currLvl)

def is_complete(root):
    '''
    Given the root of a binary tree, check if it is complete without using recursion
    '''
    h = -1

    queue = [root]

    while queue != []:

        currLvl = queue[:]
        queue = []

        for n in currLvl:
            if n is not None:
                queue.append(n.left)
                queue.append(n.right)

        h += 1

    currh = -1

    queue = [root]

    while queue != []:

        currLvl = queue[:]
        queue = []

        for n in currLvl:
            if n is not None:
                if not(n.left and n.right) and currh < h:
                    return False

                queue.append(n.left)
                queue.append(n.right)

        currh += 1
    return True

class QueueUsingStacks:
    '''
    Create a Queue class using two stacks
    '''
    def __init__(self):
        self.stacks = [StackArray(), StackArray()]
        self.activeStack = 0

    def enqueue(self, n):
    
        while self.stacks[self.activeStack].size() > 0:
            self.stacks[1-self.activeStack].push(self.stacks[self.activeStack].pop())

        self.activeStack = 1-self.activeStack
        self.stacks[self.activeStack].push(n)

        while self.stacks[self.activeStack].size() > 0:
            self.stacks[1-self.activeStack].push(self.stacks[self.activeStack].pop())
        self.activeStack = 1-self.activeStack
        
    def dequeue(self, n):
        return self.stacks[self.activeStack].pop()
        
    # like a deck of cards

if __name__ == "__main__":
    print(check_parentheses("{d: [5, 3, 2], e: (1, (2, 2))}"))
    print(reverse_string("Apple"))
    print(postfix_evaluate("12*6+"))
    