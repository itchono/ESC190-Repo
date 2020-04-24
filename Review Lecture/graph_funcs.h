#include <stdio.h>
#include <stdlib.h>

#define NUM_VERTICES 10
#define WHITE 0
#define GREEN 1
#define BLACK 2
#define DEBUG 0
#define TEST 2

int time;
int cycle;

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

Vertex *topological_list;

Graph *create_graph(int num_vertices);
Vertex *create_node(int identity, int weight);
void add_node(Graph *graph);
void add_edge(Graph *graph, int source_id, int destination_id, int weight);
void delete_edge(Graph *graph, int source_id, int destination_id);
void delete_graph(Graph *graph);
void print_list(Vertex *top_list);
void print_graph(Graph *graph);
void dfs(Graph *graph);
void explore(Graph *graph, int source_id);
void print_times(Graph *graph);
int has_cycle(Graph *graph);
void top_insert(Vertex **top_list, int next_id);
Vertex *topological_sort(Graph *graph);
void delete_list(Vertex *top_list);