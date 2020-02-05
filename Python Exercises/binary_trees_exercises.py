# MODIFIED BY MINGDE YIN

from avl_trees_tester import *
import random

def is_bst(root):
    '''
    Given the root of a binary tree, check whether it is a binary search tree
    '''
    # use a level-order traversal to check all depths - does not need recursion
    queue = [root]

    while queue != []:

        n = queue.pop(0)

        if n is not None:
            if not(n.left.data <= n.data or n.left is None) or not(n.right.data > n.data or n.right is None):
                return False
            # sweep the nodes

            queue.append(n.left)
            queue.append(n.right)
        
    return True

def is_k_balanced(root, k):
    '''
    Given the root of a binary tree, check whether it is k balanced, i.e. the 
    height difference between its left and right subtrees is at most k
    '''
    # use a level-order traversal to check all depths - does not need recursion
    queue = [root]

    while queue != []:

        n = queue.pop(0)

        if n is not None:
            if abs(n.bf) > 1:
                return False
            # sweep the nodes

            queue.append(n.left)
            queue.append(n.right)
        
    return True

def lowest_ancestor(root, n1, n2):
    '''
    Given the root of a binary tree and two nodes n1 and n2, return the lowest
    common ancestor of n1 and n2
    '''
    lasc = root

    queue = [root]

    while queue != []:

        n = queue.pop(0)

        if n is not None:
            if search(n.left, n1.data) is not None and search(n.left, n2.data) is not None:
                lasc = n.left
            elif search(n.right, n1.data) is not None and search(n.right, n2.data) is not None:
                lasc = n.right

    return lasc

def k_min_elements(root, k):
    '''
    Given the root of a binary search tree, find the k smallest keys in sorted order
    '''
    return inorder(root)[:k]

def is_complete(root):
    '''
    Given the root of a binary tree, check whether it is complete
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


class AVL_Modified:
    '''
    Create an AVL Tree class that implements the functions from the tester as methods but allow 
    balance factors up to an arbitrary value of k
    '''
    pass
    # see main



if __name__ == '__main__':
    # Test BS Tree

    nums = []
    
    MAX = 10


    for i in range(0, MAX):
        nums.append(random.randint(0, 100))

    print(nums)

    rt = AVLTreeNode(nums[0])

    tree = avl_insert(rt, AVLTreeNode(nums[1]))

    for i in range(2, MAX):
        tree = avl_insert(tree, AVLTreeNode(nums[i]))

    print(tree)
 
    # tree = right_rotate(tree, a)

    # Test BS Tree Traversals
    print("Testing preorder traversal")
    print(preorder(tree))
    print(inorder(tree))