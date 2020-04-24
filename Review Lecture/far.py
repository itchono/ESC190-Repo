from binary_trees_exercises_solns import AVL_Modified, Node
from heap_class import MaxHeap
from heap_exercises_solns import heap_sort_in_place

def lowest_ancestor_bst(root, n1, n2):
    if n1.data > n2.data:
        n1, n2 = n2, n1
    
    while root.data < n1.data or root.data > n2.data:
        while root.data < n1.data: # Both n1 and n2 are to the right of the root
            root = root.right
        while root.data > n2.data: # Both n1 and n2 are to the left of root
            root = root.left

    return root

def k_smallest_elements(arr, k):
    max_heap = MaxHeap()
    for a in arr:
        max_heap.enqueue(a)
        if max_heap.size() > k:
            max_heap.dequeue() # Get rid of the current maximum of the array
    
    heap_sort_in_place(max_heap.heap)
    return max_heap.heap

def dutch_national_flag(arr, pivot_index):
    pivot = arr[pivot_index]

    bottom, middle, top = 0, 0, len(arr)
    while middle < top:
        if arr[middle] < pivot:
            arr[bottom], arr[middle] = arr[middle], arr[bottom]
            middle, bottom = middle + 1, bottom + 1
        elif arr[middle] == pivot:
            middle += 1
        else:
            top -= 1
            arr[middle], arr[top] = arr[top], arr[middle]

def edit_distance_memoized(str1, str2):
    def distance_between_substrings(str1_last, str2_last):
        if cache[str1_last][str2_last] == -1: # Distance is not found yet
            if str1[str1_last - 1] == str2[str2_last - 1]: # Equal last characters
                cache[str1_last][str2_last] = distance_between_substrings(str1_last - 1, str2_last - 1)
            else:
                sub_distance = distance_between_substrings(str1_last - 1, str2_last - 1)
                insert_distance = distance_between_substrings(str1_last, str2_last - 1)
                delete_distance = distance_between_substrings(str1_last - 1, str2_last)
                cache[str1_last][str2_last] = 1 + min(sub_distance, insert_distance, delete_distance)

        return cache[str1_last][str2_last]

    length_1, length_2 = len(str1), len(str2)
    cache = [[-1 for _ in range(length_2 + 1)] for _ in range(length_1 + 1)]
    
    cache[0][0] = 0
    for i in range(1, length_1 + 1):
        cache[i][0] = i
    for i in range(1, length_2 + 1):
        cache[0][i] = i

    return distance_between_substrings(length_1, length_2), cache

if __name__ == '__main__':
    # Test LCA
    a = Node(50)
    b = Node(30)
    c = Node(70)
    d = Node(20)
    e = Node(60)
    f = Node(80)
    g = Node(25)
    h = Node(65)
    i = Node(90)

    tree = AVL_Modified(a)
    tree.avl_insert(b)
    tree.avl_insert(c)
    tree.avl_insert(e)
    tree.avl_insert(d)
    tree.avl_insert(f)
    tree.avl_insert(f)
    tree.avl_insert(g)
    tree.avl_insert(h)
    tree.avl_insert(i)

    print(tree)
    print(lowest_ancestor_bst(tree.root, i, h).data)

    # Test k smallest elements
    arr = [1, 5, 4, 7, 8, 4, 3, 2]
    k = 5
    print(k_smallest_elements(arr, k))

    # Test Dutch National Flag problem
    my_arr = [3, 2, 7, 3, 7, 2, 3, 1]
    dutch_national_flag(my_arr, 6)
    print(my_arr)

    # Test memoized edit distance
    str1, str2, = 'listen', 'silent'
    result = edit_distance_memoized(str1, str2)
    print('Edit distance: {}'.format(result[0]))

    for a in result[1]:
        print(a)