#include "graph_funcs.h"

int main(void){
    Graph *graph = create_graph(NUM_VERTICES);
    add_edge(graph, 0, 2, 5);
    add_edge(graph, 1, 4, 2);
    add_edge(graph, 1, 0, 5);

    add_edge(graph, 2,5,2);
    add_edge(graph, 2,3,8);
    add_edge(graph, 3,1,2);
    add_edge(graph, 3,8,8);
    add_edge(graph, 4,8,8);
    add_edge(graph, 5,6,8);
    add_edge(graph, 6,3,2);
    add_edge(graph, 6,7,9);
    add_edge(graph, 7,9,8);
    add_edge(graph, 8,7,3);
    
    print_graph(graph);

    dfs(graph);
    printTimes(graph);

    delete_edge(graph, 1, 0);
    add_edge(graph, 0, 1, 5);
    Vertex* list = topologicalSort(graph);
    print_list(list);
    print_graph(graph);
    delList(list);

    delete_edge(graph, 2, 5);

    add_node(graph);

    delete_graph(graph);
    printf("ok");

    return 0;
}