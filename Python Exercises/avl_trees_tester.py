import collections

class AVLTreeNode:
    def __init__(self, data=None, left=None, right=None, parent=None, bf=0):
        self.data = data
        self.left = left
        self.right = right
        self.parent = parent
        self.bf = bf

    def __repr__(self):
        return str(avl_to_string(self))

    def __str__(self):
        return self.__repr__()
    
def avl_to_string(tree):
    '''
    Prints an AVL tree's keys and balance factors in level order, signifying empty children by null
    '''
    result = ''
    q = collections.deque()
    first = True
    null_nodes_pending = 0

    result += '['
    q.append(tree)

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

def preorder(root):
    '''
    Returns parents first
    '''
    result = []
    if root:
        result.append(root.data)
        result += preorder(root.left)
        result += preorder(root.right)
    
    return result

def inorder(root):
    # Try implementing
    '''
    Returns in-order list for BST
    '''
    result = []
    if root: # i.e. if root is not None
        result += inorder(root.left)
        result.append(root.data)
        result += inorder(root.right)

    return result

def postorder(root):
    # Try implementing
    '''
    Returns Leaves first.
    '''
    result = []
    if root: # i.e. if root is not None
        result += inorder(root.left)
        result += inorder(root.right)
        result.append(root.data)

    return result

def search(root, key):
    while root and not root.data == key:
        if key < root.data:
            root = root.left
        else:
            root = root.right
    return root

def search_recursive(root, key):
    # Try implementing
    if root and not root.data == key:
        if key < root.data:
            return search(root.left, key)
        elif key > root.data:
            return search(root.right, key)
    return root # if data is equal OR if node not found (None)

def maximum(root):
    while root.right:
        root = root.right
    return root

def minimum(root):
    while root.left: # while exists
        root = root.left
    return root

def predecessor(n):
    if n.left:
        return maximum(n.left)
    while n and n == n.parent.left:
        # if node exists and this node is the parent node's left child
        n = n.parent
    return n.parent

def successor(n):
    # Try implementing (similar to predecessor)
    if n.right:
        # if right child exists, find min of that one
        return minimum(n.right)
    while n and n == n.parent.right:
        # smallest ancestor of node whose left subtree contains n
        n = n.parent
    # once this stops working, that means we are switching from going less than to going greater ==> return the node's parent
    return n.parent

def insert(root, n):
    if root == None:
        root = n
    elif n.data < root.data:
        root.left = insert(root.left, n)
        root.left.parent = root
    elif n.data > root.data:
        root.right = insert(root.right, n)
        root.right.parent = root
    else:
        n.left, n.right = root.left, root.right
        if n.left:
            n.left.parent = n
        if n.right:
            n.right.parent = n
        root = n
    return root

def insert_iterative(root, n):
    # Try iterative version
    if root == None:
        root = n
    else:
        nd = root
        while nd.left or nd.right:
            if n.data < nd.data:
                nd = nd.left
            elif n.data > nd.data:
                nd = nd.right
    
        if n.data < nd.data:
            nd.left = n
            nd.left.parent = nd
        elif n.data > nd.data:
            nd.right = n
            nd.right.parent = nd        

    return root

def delete(root, n):
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
    
    if not n.left:
        root = replace(root, n, n.right)
    elif not n.right:
        root = replace(root, n, n.left)
    else:
        m = minimum(n.right)
        if m.parent is not n:
            root = replace(root, m, m.right)
            m.right, m.right.parent = n.right, m
        root = replace(root, n, m)
        m.left = n.left
        m.left.parent = m
    return root

def right_rotate(root, n):
    z = n.left
    n.left = z.right
    if z.right:
        z.right.parent = z
    z.parent = n.parent

    if not n.parent:
        root = z
    elif n is n.parent.left:
        n.parent.left = z
    else:
        n.parent.right = z
    z.right = n
    n.parent = z

    # Update balance factors for relevant nodes
    n.bf = n.bf + 1 - min(0, z.bf)
    z.bf = z.bf + 1 + max(0, n.bf)

    return root

def left_rotate(root, n):
    z = n.right
    n.right = z.left

    if z.left:
        z.left.parent = z
    z.parent = n.parent

    if not n.parent:
        root = z
    elif n is n.parent.right:
        n.parent.right = z
    else:
        n.parent.left = z
    
    # Update balance factors for relevant nodes
    n.bf = n.bf + 1 - min(0, z.bf)
    z.bf = z.bf + 1 + max(0, n.bf)
    
    return root

def update_bf_insert(root, n):
    # Update the balance factors and possibly re-balance
    if n.bf < -1 or n.bf > 1:
        root = rebalance(root, n)
    else:
        if n.parent:
            if n.parent.left is n:
                n.parent.bf -= 1
            else:
                n.parent.bf += 1
            if not n.parent.bf == 0:
                root = update_bf_insert(root, n.parent)
    return root

def rebalance(root, n):
    if n.bf > 0:
        if n.right and n.right.bf >= 0:
            root = left_rotate(root, n)
        else:
            root = right_rotate(root, n.right)
            root = left_rotate(root, n)
    else:
        if n.left and n.left.bf <= 0:
            root = right_rotate(root, n)
        else:
            root = left_rotate(root, n.left)
            root = right_rotate(root, n)

    return root

def avl_insert(root, n):
    root = insert(root, n)
    root = update_bf_insert(root, n)
    return root

if __name__ == '__main__':
    # Test BS Tree
    print("Testing BS tree")
    a = AVLTreeNode(14)
    b = AVLTreeNode(12)
    c = AVLTreeNode(27)
    d = AVLTreeNode(9)
    e = AVLTreeNode(13)
    f = AVLTreeNode(15)
    g = AVLTreeNode(5)
    h = AVLTreeNode(10)
    i = AVLTreeNode(19)

    tree = avl_insert(a, b)
    tree = avl_insert(tree, c)
    tree = avl_insert(tree, e)
    tree = avl_insert(tree, d)
    tree = avl_insert(tree, f)
    tree = avl_insert(tree, f)
    tree = avl_insert(tree, g)
    tree = avl_insert(tree, h)
    tree = avl_insert(tree, i)
    print(tree)
 
    # tree = right_rotate(tree, a)

    # Test BS Tree Traversals
    print("Testing preorder traversal")
    print(preorder(tree))
    print(inorder(tree))