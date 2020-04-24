import collections

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

                result += '{}'.format(node.data)
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