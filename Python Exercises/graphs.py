class Graph:
    def __init__(self, values, connections):
        self.values = values
        self.adjacency_mtx = connections
        self.values_to_indices = {}
        
        i = 0

        #mapping the node value to the adj matrix indices
        for node in self.values:
            self.values_to_indices[node] = i
            i += 1
            
    def DFS(self, start, end):
        #initializing the stack
        #top at index -1
        #bottom at index 0
        stack = []
        stack.append(start)

        #keep track of visited nodes
        visited = []
        
        #keep track of the path
        prev = [None]*len(self.values)
        node = None

        j = 1
        while (len(stack) > 0) and (node != end):
            print("Expansion #", j)
            node = stack.pop()
            print("Expanding node", node)

            if node in visited:
                print("Previously visited node. Skipping.")
                continue #skip this node
            
            #otherwise add all of its neighbors to the stack
            curr_ind = self.values_to_indices[node]
            for i in range(len(self.adjacency_mtx)):
                if self.adjacency_mtx[curr_ind][i] != 0:
                    #row of present node, all columns
                    stack.append(self.values[i])
                    if prev[i] == None:
                        prev[i] = node
            
            visited.append(node) #mark node as visited
            j += 1 # counter for which expansion we are on

            print("Stack:\t", stack)
            print("Visited:", visited)
            
        # tracing the path
        s = []
        if node == end:
           s.append(node)
           while node != start:
               node = prev[self.values_to_indices[node]]
               s.append(node)

        return list(reversed(s))

if __name__ == "__main__":
    vals = ['A', 'B', 'C', 'D']
    edges = [[0, 1, 0, 0], \
             [1, 0, 1, 1], \
             [0, 1, 0, 0], \
             [0, 1, 0, 0]]
    graph = Graph(vals, edges)

    input("Pause")

    print('---From A to B---')
    path = graph.DFS('A', 'B')
    print("Path is:", path, "\n")

    input("Pause")
    
    print('---From A to D---')
    path = graph.DFS('A', 'D')
    print("Path is:", path, "\n")


    vals2 = ['A', 'B', 'C', 'D', 'E']
    edges2 = [[0, 1, 0, 0, 0], \
              [1, 0, 1, 1, 0], \
              [0, 1, 0, 1, 0], \
              [0, 1, 1, 0, 1], \
              [0, 0, 0, 1, 0]]
    
    input("Pause")
    
    graph2 = Graph(vals2, edges2)
    print('---From A to E---')
    path = graph2.DFS('A', 'E')
    print("Path is:", path, "\n")


    
    vals3 = ['A', 'B', 'C', 'D', 'E']
    edges3 = [[0, 1, 0, 0, 0], \
              [1, 0, 1, 1, 0], \
              [0, 1, 0, 1, 0], \
              [0, 1, 1, 0, 0], \
              [0, 0, 0, 0, 0]]

    input("Pause")
    
    graph3 = Graph(vals3, edges3)
    print('---From A to E---')
    path = graph3.DFS('A', 'E')
    print("Path is:", path, "\n")
