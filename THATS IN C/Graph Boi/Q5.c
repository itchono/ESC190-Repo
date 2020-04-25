#include <stdio.h>
#include <stdlib.h>

#define UNVISITED 0
#define VISITED 1
#define FINISHED 2

#define NUM_VERTICES 11

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

Vertex* topList = NULL; // list to be used for topological sort.

// FROM CLASS
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
// FROM CLASS
Vertex *create_node(int identity, int weight){
    Vertex *new_node = malloc(sizeof(Vertex));
    new_node->id = identity;
    new_node->weight = weight;
    new_node->next = NULL;

    return new_node;
}
// FROM CLASS
void add_node(Graph *graph){
    graph->num_vertices++;
    graph->adjacency_lists = realloc(graph->adjacency_lists, graph->num_vertices * sizeof(Vertex *));
    graph->adjacency_lists[graph->num_vertices - 1] = NULL;
    graph->vertices = realloc(graph->vertices, graph->num_vertices * sizeof(VertexInfo));
}
// FROM CLASS
void add_edge(Graph *graph, int source_id, int destination_id, int weight){
    Vertex *new_node = create_node(destination_id, weight);
    new_node->next = graph->adjacency_lists[source_id];
    graph->adjacency_lists[source_id] = new_node;
}
// FROM CLASS
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
// FROM CLASS
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
// FROM CLASS
void print_list(Vertex *top_list){
    Vertex *temp_node = top_list;
    while(temp_node){
        printf("%d", temp_node->id);
        temp_node = temp_node->next;
        if (temp_node) printf(" -> ");
    }
    printf("\n");
}
// FROM CLASS
void print_graph(Graph *graph){
    printf("Adjacency Lists\n");
    for(int id = 0; id < graph->num_vertices; id++){
        printf("Vertex %d: ", id);
        print_list(graph->adjacency_lists[id]);
    }
    printf("\n");
}

// Topological sort
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


// topological sort
Vertex* topologicalSort(Graph* graph) {
    dfs(graph);
    return topList;
}

Vertex* reversedList(Vertex* list) {
    // reverses a linked list, recursively.
    if (!list||!list->next) return list;

    Vertex* reversed = reversedList(list->next);
    list->next->next = list; // go 2 spaces ahead and circle back
    list->next = NULL;

    return reversed;
}

void delList(Vertex* list) {
    Vertex* temp = list;
    while (temp) {
        Vertex* next = temp->next;
        free(temp);
        temp = next;
    }
}

Vertex* schedulerSort(Graph* graph) {
    // This solves part C
    return reversedList(topologicalSort(graph));
}

// PART D
void numPathsRecursive(Graph* graph, int id, int target, int* paths) {
    // DFS-ish type algorithm
    if (id == target) {
        // if we are on the actual node, nice we're done
        (*paths)++;
    }
    else {
        Vertex* curr = graph->adjacency_lists[id]; // the starting point in our LL.
        while (curr) {
            // explore every other adjacent node in the LL
            numPathsRecursive(graph, curr->id, target, paths);
            curr = curr->next;
        }
    }
}

int numPaths(Graph* graph, int startFile, int endFile) {
    // calls the recursive function
    int paths = 0;
    numPathsRecursive(graph, endFile, startFile, &paths);

    return paths;
}

int main(void){
    // Question 5.1 B-D
    Graph *graph = create_graph(NUM_VERTICES);
    
    add_edge(graph, 10, 9, 1);
    add_edge(graph, 10, 6, 1);

    add_edge(graph, 9, 1, 1);
    add_edge(graph, 9, 7, 1);
    add_edge(graph, 9, 8, 1);

    add_edge(graph, 8, 6, 1);
    add_edge(graph, 7, 3, 1);
    add_edge(graph, 6, 4, 1);
    add_edge(graph, 6,5,1);
    add_edge(graph, 6,7,1);

    add_edge(graph, 5,2,1);
    add_edge(graph, 5,3,1);

    add_edge(graph, 4,2,1);
    add_edge(graph, 4,5,1);

    add_edge(graph, 3,1,1);
    add_edge(graph, 3,2,1);

    add_edge(graph, 2,0,1);
    add_edge(graph, 1,0,1);

    printf("GRAPH:\n");
    print_graph(graph);
    

    Vertex* list = schedulerSort(graph);
    printf("Schedule:\n");
    print_list(list);

    printf("%d", numPaths(graph, 0, 3));

    delList(list);
    return 0;
}