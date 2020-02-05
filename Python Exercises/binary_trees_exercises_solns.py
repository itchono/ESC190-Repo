from avl_trees_tester import *

def is_bst(root):
    '''
    Given the root of a binary tree, check whether it is a binary search tree
    '''
    def bst_property_satisifed(node, lower_bound=float('-inf'), upper_bound = float('inf')):
        '''
        Returns True if the BST property is satisfied in the current node
        '''
        if not node:
            return True
        elif not lower_bound <= node.data <= upper_bound:
            return False
        return bst_property_satisifed(node.left, lower_bound, node.data) and bst_property_satisifed(node.right, node.data, upper_bound)
    return bst_property_satisifed(root)

def is_k_balanced(root, k):
    '''
    Given the root of a binary tree, check whether it is k balanced, i.e. the 
    height difference between its left and right subtrees is at most k
    '''
    def balanced_status(node):
        '''
        Return a 2-tuple signifying the balanced status and height of node
        '''
        if not node: # Base case where node is a leaf
            return True, -1

        left_child_status = balanced_status(node.left)
        if not left_child_status[0]:
            return False, 0
        
        right_child_status = balanced_status(node.right)
        if not right_child_status[0]:
            return False, 0

        balanced = abs(left_child_status[1]- right_child_status[1] <= k) # Check whether current node is k balanced
        height = max(left_child_status[1], right_child_status[1]) + 1 # Increment height of current node
        return balanced, height
    return bool(balanced_status(root)[0])

def lowest_ancestor(root, n1, n2):
    '''
    Given the root of a binary tree and two nodes n1 and n2, return the lowest
    common ancestor of n1 and n2
    '''
    depth_1, depth_2, node = -1, -1, n1
    while node: # Get depth of n1
        depth_1, node = depth_1 + 1, node.parent
    
    node = n2
    while node:
        depth_2, node = depth_2 + 1, node.parent

    depth_difference = depth_1 - depth_2
    if depth_difference >= 0:
        lowest_node, other_node = n1, n2
    else:
        lowest_node, other_node, depth_difference = n2, n1, -depth_difference

    for _ in range(depth_difference): # Ensure we start at the same level
        lowest_node = lowest_node.parent
    
    while lowest_node is not other_node: # Move both nodes up in tandem to get lowest ancestor
        lowest_node, other_node = lowest_node.parent, other_node.parent
    
    return lowest_node

def k_min_elements(root, k):
    '''
    Given the root of a binary search tree, find the k smallest keys in sorted order
    '''
    curr_index, result = [0], [] # Keep track of a global variable so we exit out early after reaching the kth element
    def limited_inorder(node):
        if node and curr_index[0] < k:
            limited_inorder(node.left)
            if curr_index[0] < k:
                result.append(node.data)
            curr_index[0] += 1
            limited_inorder(node.right)
        return result
    return limited_inorder(root)

def is_complete(root):
    '''
    Given the root of a binary tree, check whether it is complete
    '''
    def complete_status(node):
        '''
        Return a 3-tuple signifying the complete status, height and perfect status
        '''
        if not node:
            return True, -1, True
        left_child_status = complete_status(node.left)
        right_child_status = complete_status(node.right)

        # Parent cannot be complete if one of its children is not complete
        if not left_child_status[0] or not right_child_status[0]:
            return False, -1, False
        
        # If current node has two complete subtrees, the following cases signify the node is complete
        # Case 1: Left subtree is perfect and right subtree has same height as left subtree
        if left_child_status[2] and left_child_status[1] == right_child_status[1]:
            return True, left_child_status[1] + 1, right_child_status[2]
        # Case 2: Right subtree is perfect and left subtree has depth one larger
        if right_child_status[2] and left_child_status[1] - right_child_status[1] == 1:
            return True, left_child_status[1] + 1, False
        
        return False, -1, False
    return complete_status(root)[0]

class Node:
    def __init__(self, data=None, left=None, right=None, parent=None, bf=0, k=1):
        self.data = data
        self.left = left
        self.right = right
        self.parent = parent
        self.bf = bf

class AVL_Modified:
    '''
    Create an AVL Tree class that implements the functions from the tester as methods but allow 
    balance factors up to an arbitrary value of k
    '''

    def __init__(self, root=None, k=1):
        self.root = root
        self.k = k

    def __repr__(self):
        return str(self.binary_tree_to_string())

    def __str__(self):
        return self.__repr__()

    def binary_tree_to_string(self):
        result = ''
        q = collections.deque()
        first = True
        null_nodes_pending = 0

        result += '['
        q.append(self.root)

        while q:
            node = q.popleft()
            if node:
                if first:
                    first = False
                else:
                    result += ', '

                while null_nodes_pending:
                    result += 'null, '
                    null_nodes_pending -= 1

                result += '"{}"|{}'.format(node.data, node.bf)
                q.append(node.left)
                q.append(node.right)
            else:
                null_nodes_pending += 1

        result += ']'
        return result

    def search(self, key):
        root = self.root
        while root and not root.data == key:
            if key < root.data:
                root = root.left
            else:
                root = root.right
        return root

    def maximum(self):
        root = self.root
        while root.right:
            root = root.right
        return root

    def minimum(self):
        root = self.root
        while root.left:
            root = root.left
        return root

    def predecessor(self, n):
        if n.left:
            return n.left.maximum()
        while n and n == n.parent.left:
            n = n.parent
        return n.parent

    def successor(self, n):
        if n.right:
            return n.right.minimum()
        while n and n == n.parent.right:
            n = n.parent
        return n.parent

    def insert(self, n):
        curr_node = self.root
        if not self.root:
            self.root = n

        update = True
        while curr_node:
            if n.data < curr_node.data:
                if curr_node.left:
                    curr_node = curr_node.left
                else:
                    curr_node.left = n
                    n.parent = curr_node
                    break
            elif n.data > curr_node.data:
                if curr_node.right:
                    curr_node = curr_node.right
                else:
                    curr_node.right = n
                    n.parent = curr_node
                    break
            else:
                update = False
                break

        return update

    def delete(self, n):
        def replace(root, n1, n2):
            if not n1.parent:
                root = n2
            elif n1 == n1.parent.left:
                n1.parent.left = n2
            else:
                n1.parent.right = n2
            if n2:
                n2.parent = n1.parent
            return root

        def minimum_node(n):
            while n.left:
                n = n.left
            return n
        
        if not n.left:
            self.root = replace(self.root, n, n.right)
        elif not n.right:
            self.root = replace(self.root, n, n.left)
        else:
            m = minimum_node(n.right)
            if m.parent is not n:
                self.root = replace(self.root, m, m.right)
                m.right, m.right.parent = n.right, m
            self.root = replace(self.root, n, m)
            m.left = n.left
            m.left.parent = m

    def right_rotate(self, n):
        z = n.left
        n.left = z.right
        if z.right:
            z.right.parent = n
        z.parent = n.parent

        if not n.parent:
            self.root = z
        elif n is n.parent.left:
            n.parent.left = z
        else:
            n.parent.right = z
        z.right = n
        n.parent = z

        # Update balance factors for relevant nodes
        n.bf = n.bf + 1 - min(0, z.bf)
        z.bf = z.bf + 1 + max(0, n.bf)

    def left_rotate(self, n):
        z = n.right
        n.right = z.left
        if z.left:
            z.left.parent = n
        z.parent = n.parent

        if not n.parent:
            self.root = z
        elif n is n.parent.left:
            n.parent.left = z
        else:
            n.parent.right = z
        z.left = n
        n.parent = z

        # Update balance factors for relevant nodes
        n.bf = n.bf - 1 - max(0, z.bf)
        z.bf = z.bf - 1 + min(0, n.bf)

    def update_bf_insert(self, n):
        # Update the balance factors and possibly re-balance
        if n.bf < -self.k or n.bf > self.k:
            self.rebalance(n)
        else:
            if n.parent:
                if n.parent.left is n:
                    n.parent.bf -= 1
                else:
                    n.parent.bf += 1
                if not n.parent.bf == 0:
                    self.update_bf_insert(n.parent)

    def rebalance(self, n):
        if n.bf > 0:
            if n.right and n.right.bf >= 0:
                self.left_rotate(n)
            else:
                self.right_rotate(n.right)
                self.left_rotate(n)
        else:
            if n.left and n.left.bf <= 0:
                self.right_rotate(n)
            else:
                self.left_rotate(n.left)
                self.right_rotate(n)

    def avl_insert(self, n):
        if self.insert(n):
            self.update_bf_insert(n)

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

    # Print the tree
    print('Printing the tree. Note balance factors are not valid since we use this as a BST, not an AVL tree')
    print(tree)

    # Test is_bst
    print('Testing is_bst')
    print(is_bst(tree))

    # Test k_balanced
    k = 1
    print('Testing is_k_balanced with k =', k)
    print(is_k_balanced(tree, k))

    # Test k_min_elements
    k = 5
    print('Testing k_min_elements with k =', k)
    print(k_min_elements(tree, k))

    # print(tree)
    print('Testing is_complete')
    print(is_complete(tree))

    # Test AVL Modified
    k_factor = 2

    a = Node(14)
    b = Node(12)
    c = Node(27)
    d = Node(9)
    e = Node(13)
    f = Node(15)
    g = Node(5)
    h = Node(10)
    i = Node(19)
    j = Node(29)
    k = Node(12.5)
    l = Node(13.5)
    m = Node(14.5)

    # Test AVL insert
    a = Node(14)
    b = Node(12)
    c = Node(27)
    d = Node(9)
    e = Node(13)
    f = Node(15)
    g = Node(5)
    h = Node(10)
    i = Node(19)
    j = Node(18)
    k = Node(12.5)
    l = Node(13.5)
    m = Node(14.5)

    tree = AVL_Modified(a, k_factor)
    # print(tree)

    tree.avl_insert(b)
    # print(tree)

    tree.avl_insert(c)
    # print(tree)

    tree.avl_insert(e)
    # print(tree)

    tree.avl_insert(d)
    # print(tree)

    tree.avl_insert(f)
    # print(tree)

    tree.avl_insert(f)
    # print(tree)

    tree.avl_insert(g)
    # print(tree)

    tree.avl_insert(h)
    print(tree)

    tree.avl_insert(i)
    print(tree)

    tree.avl_insert(j)
    print(tree)