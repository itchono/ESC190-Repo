from lab1_utilities import *


def get_installations_from_file(file_name):
    '''
    Parses data into Installation objects and returns as list
    '''

    output = []

    with open(file_name, "r") as f:
        lines = f.readlines() # gets lines prepped and removes the top one
        lines.pop(0)

        for l in lines:
            fields = l.strip("\n").split("\t")

            output.append(Installation(
                name=fields[0], 
                ward = int(fields[2]), 
                position = (float(fields[7]), float(fields[8])), 
                indoor=(fields[15]=="INDOORS")))
            # process the things - str, int, (float, float), bool

    return output # type list of installations


def euclidean_distance(position1, position2):
    '''
    returns sqrt((y2-y1)^2 + (x2-x1)^2)
    uses lazy version of sqrt without needing to import anything
    '''
    return ((position2[1]-position1[1])**2 + (position2[0]-position1[0])**2)**(1/2) # DONE


def get_adjacency_mtx(installations):
    '''
    Create adjacency matrix from installations data
    '''
    M = [[0] * len(installations) for i in range(len(installations))] # prefill matrix

    for x in range(0, len(installations)):

        for y in range(0, len(installations)):
            if abs(installations[y].ward-installations[x].ward) <= 1 and y != x:
                M[x][y] = euclidean_distance(installations[x].position, installations[y].position) * (1.5 if (installations[x].indoor or installations[y].indoor) else 1.0)
            
    return M

def make_graph(installations):
    '''
    Combine adjacency matrix and collections list into graph object
    '''
    # uses previous functions and string names
    return Graph([j.name for j in installations], get_adjacency_mtx(installations))


def find_shortest_path(installation_A, installation_B, graph):
    '''
    Djikstra's Algorithm implemented on this
    '''
    # A and B given by names

    lookup = graph.artwork_to_index

    backlook = {v: k for k, v in lookup.items()}
    
    num_nodes = len(graph.adjacency_mtx)

    visited = set()
    unvisited = set(range(num_nodes))
    # initialize set of visited and unvisited nodes

    adj = graph.adjacency_mtx
    distances = [float("inf") for i in range(num_nodes)] # initialize all distances to infinity

    curr = lookup[installation_A] # convert name to index
    distances[curr]= 0 # set distance to itself as zero

    prev = [-1 for i in range(num_nodes)] # set all returns to null

    min_node = -1 # pointer for next node
    
    while unvisited and curr in unvisited:
        visited.add(curr)
        unvisited.remove(curr) # update presence

        for v in unvisited:
            if adj[curr][v] != 0 and distances[curr] + adj[curr][v] < distances[v]:
                distances[v] = distances[curr] + adj[curr][v] # update shortest paths for all
                prev[v] = curr # map the breadcrumb trail to the shortest
                
        min_dist = float("inf") # reset min dist

        for v in unvisited:
            if distances[v] < min_dist:
                min_dist = distances[v]
                min_node = v # identify min node, to be used next
        
        curr = min_node # select next out of all possible unvisited nodes

    # Trace the path
    c = lookup[installation_B]
    path = [c]
    while prev[c] != -1:
        c = prev[c]
        path.append(c)
    # puts path in backwards, so we must reverse it
    path.reverse()

    path = [backlook[i] for i in path] # convert to names

    # output time
    if prev[lookup[installation_B]] == -1:
        # in this case there was no path to this node
        return(None, []) # fail case return
    else:
        return(distances[lookup[installation_B]], path)


    
