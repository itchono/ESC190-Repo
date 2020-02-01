from lab1 import *
from lab1_utilities import *

if __name__ == "__main__":
    A = Installation("A", 5, (1, 1), True)
    B = Installation("B", 4, (1, 2), False)
    C = Installation("C", 3, (2, 2), False)
    D = Installation("D", 2, (2, 5), False)
    E = Installation("E", 2, (2, 4), True)
    installations = [A, B, C, D, E]

    print("Testing get_adjacency_mtx:")
    print(get_adjacency_mtx(installations))
    print("")

    print("Testing make_graph:")
    graph = make_graph(installations)
    print("graph.installations:")
    print(graph.installations)
    print("graph.adjacency_mtx:")
    print(graph.adjacency_mtx)
    print("graph.artwork_to_index:")
    print(graph.artwork_to_index)
    print("")

    print("Testing find_shortest_path:")
    print(find_shortest_path("A", "B", graph))
    print(find_shortest_path("C", "A", graph))
    print(find_shortest_path("D", "B", graph))
    print(find_shortest_path("A", "E", graph))
    print("")


    installations = get_installations_from_file('test_data.txt')
    for installation in installations:
        print(installation)

    graph = make_graph(installations)
    print(graph)

    M = [
        [0,7,4,0,3,0,0,0],
        [7,0,0,0,0,8,9,0],
        [4,0,0,0,4,0,3,0],
        [0,0,0,0,0,5,0,0],
        [3,0,4,0,0,0,0,0],
        [0,8,0,5,0,0,0,0],
        [0,9,3,0,0,0,0,0],
        [0,0,0,0,0,0,0,0]
    ]
    l = ["0", "1", "2", "3", "4", "5", "6", "7"]

    graph.installations = l
    graph.adjacency_mtx = M

    for i, artwork in enumerate(graph.installations):
            graph.artwork_to_index[artwork] = i

    installations = get_installations_from_file('public_artwork_data.txt')
    #installations = get_installations_from_file('test_data.txt')
    #graph = make_graph(installations)

    installation_A = "3"
    installation_B = "4"

    '''
    installation_A = 'GALAXY'
    installation_B = 'MIRAGE'
    '''

    '''
    installation_A = 'A'
    installation_B = 'D'
    '''
    distance, path = find_shortest_path(installation_A, installation_B, graph)

    print("The shortest path between {} and {} is {} along nodes:".format(installation_A,
                                                                          installation_B,
                                                                          str(distance)))
    for node in path:
        print(node)
