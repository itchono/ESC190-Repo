#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTICES 10

typedef struct Node{
    int id;
    int weight;
    struct Node *next;
}Vertex;

typedef struct NodeInfo{
    int colour;
    struct NodeInfo *parent;
    int discovery_time;
    int finishing_time;
}VertexInfo;

typedef struct{
    Vertex **adjacency_lists;
    VertexInfo *vertices;
    int num_vertices;
}Graph;



Graph *create_graph(int num_vertices);
Vertex *create_node(int identity, int weight);
void add_node(Graph *graph);
void add_edge(Graph *graph, int source_id, int destination_id, int weight);
void delete_edge(Graph *graph, int source_id, int destination_id);
void delete_graph(Graph *graph);
void print_list(Vertex *top_list);
void print_graph(Graph *graph);
void dfs(Graph* graph);
void printTimes(Graph* graph);
Vertex* topologicalSort(Graph* graph);
void delList(Vertex* list);