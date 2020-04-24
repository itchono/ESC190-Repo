#include "graph_funcs.h"

int main(void){
    Graph *graph = create_graph(NUM_VERTICES);
    Vertex *top_list;

    add_edge(graph, 0, 2, 5);

    add_edge(graph, 1, 4, 2);
    add_edge(graph, 1, 0, 5);

    add_edge(graph, 2, 5, 2);
    add_edge(graph, 2, 3, 8);

    add_edge(graph, 3, 1, 2);
    add_edge(graph, 3, 8, 8);

    add_edge(graph, 4, 8, 8);

    add_edge(graph, 5, 6, 8);

    add_edge(graph, 6, 3, 2);
    add_edge(graph, 6, 7, 9);

    add_edge(graph, 7, 9, 8);

    add_edge(graph, 8, 7, 3);
    
    print_graph(graph);

    #if TEST == 0 // Test DFS
        dfs(graph);
        print_times(graph);
    #elif TEST == 1 // Test Cycle Detection
        if(has_cycle(graph)){
            printf("Graph has a cycle\n");
        }else{
            printf("Graph has no cycle\n");
        }
    #elif TEST == 2 // Test Topological Sort
        delete_edge(graph, 1, 0);
        add_edge(graph, 0, 1, 5);
        top_list = topological_sort(graph);
        print_graph(graph);
        print_list(top_list);
        delete_list(top_list);
    #endif

    delete_graph(graph);

    return 0;
}