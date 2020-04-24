#include "graph_funcs.h"
#include "lab2.h"

#define UNVISITED 0
#define VISITED 1
#define FINISHED 2

int cycle;
Vertex* topList = NULL;

Graph *create_graph(int num_vertices){
    Graph *graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->adjacency_lists = malloc(num_vertices * sizeof(Vertex *));
    graph->vertices = malloc(num_vertices * sizeof(VertexInfo));

    for(int i = 0; i < num_vertices; i++){
        graph->adjacency_lists[i] = NULL;
    }

    return graph;
}

Vertex *create_node(int identity, int weight){
    Vertex *new_node = malloc(sizeof(Vertex));
    new_node->id = identity;
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}

void add_node(Graph *graph){
    graph->num_vertices++;
    graph->adjacency_lists = realloc(graph->adjacency_lists, graph->num_vertices * sizeof(Vertex *));
    graph->adjacency_lists[graph->num_vertices - 1] = NULL;
    graph->vertices = realloc(graph->vertices, graph->num_vertices * sizeof(VertexInfo));
}

void add_edge(Graph *graph, int source_id, int destination_id, int weight){
    Vertex *new_node = create_node(destination_id, weight);
    new_node->next = graph->adjacency_lists[source_id];
    graph->adjacency_lists[source_id] = new_node;
}

void delete_edge(Graph *graph, int source_id, int destination_id){
    Vertex *curr_node, *prev_node = NULL;
    for(curr_node = graph->adjacency_lists[source_id];
        curr_node != NULL && curr_node->id != destination_id;
        prev_node = curr_node, curr_node = curr_node->next);

    if(!curr_node){ // Destination node does not exist
        return;
    }
    if(!prev_node){ // Destination node is the head of the linked list
        graph->adjacency_lists[source_id] = graph->adjacency_lists[source_id]->next;
    }else{ // Destination node is somewhere else in the linked list
        prev_node->next = curr_node->next;
    }

    free(curr_node);
}

void delete_graph(Graph *graph){
    Vertex *temp_head;
    for(int i = 0; i < graph->num_vertices; i++){ // Iterate through each vertex
        while(graph->adjacency_lists[i]){
            temp_head = graph->adjacency_lists[i];
            graph->adjacency_lists[i] = temp_head->next;
            free(temp_head);
        }
    }
    free(graph->adjacency_lists);
    free(graph->vertices);
    free(graph);
}

void print_list(Vertex *top_list){
    Vertex *temp_node = top_list;
    while(temp_node){
        printf("%d -> ", temp_node->id);
        temp_node = temp_node->next;
    }
    printf("NULL\n");
}

void print_graph(Graph *graph){
    printf("Adjacency Lists\n");
    for(int id = 0; id < graph->num_vertices; id++){
        printf("Vertex %d ", id);
        print_list(graph->adjacency_lists[id]);
    }
    printf("\n");
}

// Topological
void topologicalInsert(Vertex** list, int id) {
    Vertex* newVTX = malloc(sizeof(Vertex));
    newVTX->id = id;
    newVTX->next = list[0]; // head of list

    // repoint head of list to this vertex

    (*list) = newVTX;
}


// DFS
void explore(int id, int* t, Graph* graph) {
    VertexInfo* vtx = graph->vertices + id;

    (*t)++;

    // Discover vtx
    vtx->discovery_time = *t;
    vtx->colour = VISITED; // from pseudo: set to green

    // Scan neighbours
    Vertex* curr = graph->adjacency_lists[id]; // the starting point in our LL.

    while (curr) {
        if (graph->vertices[curr->id].colour == UNVISITED) {
            // tree edge
            graph->vertices[curr->id].parent = graph->vertices+id;
            explore(curr->id, t, graph);
        }

        else if(graph->vertices[curr->id].colour == VISITED) {
            // back edge
            // cycle detected!
            cycle = 1;
        }

        else if(graph->vertices[curr->id].colour == VISITED) {
            // forward edge
        }
        curr = curr->next;
    }
    
    // Finish vtx
    vtx->colour = FINISHED;
    (*t)++;
    vtx->finishing_time = (*t);

    // put into topological list 
    topologicalInsert(&topList, id);
}

// DFS
void dfs(Graph* graph) {
    cycle = 0;
    int t = 0;

    // init portion
    for (int i = 0; i < graph->num_vertices; i++) {
        graph->vertices[i].colour = UNVISITED; // from pseudo: set to white
        graph->vertices[i].parent = NULL; // blank out parent in DFS rn
    }

    for (int i = 0; i < graph->num_vertices; i++) {
        if (graph->vertices[i].colour == UNVISITED) {
            explore(i, &t, graph);
        }
    }


}
void printTimes(Graph* graph) {
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("V: %d\nDiscovered: %d\n Finished: %d\n", i, graph->vertices[i].discovery_time, graph->vertices[i].finishing_time);
    }
}

int hasCycle(Graph* graph) {
    dfs(graph);
    return cycle;
}

// topological sort



Vertex* topologicalSort(Graph* graph) {
    dfs(graph);
    return topList;
}

void delList(Vertex* list) {
    
    Vertex* temp = list;
    while (temp) {
        Vertex* next = temp->next;
        free(temp);
        temp = next;
    }

}