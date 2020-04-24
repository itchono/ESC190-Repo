#include "graph_funcs.h"

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

void dfs(Graph *graph){
    time = 0;

    for(int id = 0; id < graph->num_vertices; id++){
        graph->vertices[id].colour = WHITE;
        graph->vertices[id].parent = NULL;

        #if DEBUG == 1
            printf("Colouring vertex %d white\n", id);
        #endif
    }
    #if DEBUG == 1
        printf("\n");
    #endif

    for(int id = 0; id < graph->num_vertices; id++){
        if(graph->vertices[id].colour == WHITE){
            explore(graph, id);
        }
    }
}

void explore(Graph *graph, int source_id){
    time += 1;
    graph->vertices[source_id].discovery_time = time;
    graph->vertices[source_id].colour = GREEN;

    #if DEBUG == 1
        printf("Colouring vertex %d green\n", source_id);
    #endif

    Vertex *temp_node = graph->adjacency_lists[source_id];
    while(temp_node){
        if(graph->vertices[temp_node->id].colour == WHITE){ // Detected a tree edge
            graph->vertices[temp_node->id].parent = &(graph->vertices[source_id]);
            explore(graph, temp_node->id);
        }else if(graph->vertices[temp_node->id].colour == GREEN){ // Detected a back edge
            cycle = 1;
        }
        temp_node = temp_node->next;
    }

    #if TEST == 2 // Topological sort activated
        top_insert(&topological_list, source_id);
    #endif

    graph->vertices[source_id].colour = BLACK;
    time += 1;
    graph->vertices[source_id].finishing_time = time;

    #if DEBUG == 1
        printf("Colouring vertex %d black\n", source_id);
    #endif
}

void print_times(Graph *graph){
    printf("Discovery and finishing times:\n");
    for(int id = 0; id < graph->num_vertices; id++){
        printf("Vertex %d: (%d, %d)\n", id, graph->vertices[id].discovery_time, graph->vertices[id].finishing_time);
    }
}

int has_cycle(Graph *graph){
    dfs(graph);
    return cycle;
}

void top_insert(Vertex **top_list, int next_id){
    #if DEBUG == 1
        printf("Inserting node %d\n", next_id);
    #endif
    Vertex *new_vertex = malloc(sizeof(Vertex));
    new_vertex->id = next_id;
    new_vertex->next = *top_list;
    *top_list = new_vertex;
}

Vertex *topological_sort(Graph *graph){
    dfs(graph);
    return topological_list;
}

void delete_list(Vertex *top_list){
    Vertex *temp_head;
    while(top_list){
        temp_head = top_list;
        top_list = temp_head->next;
        free(temp_head);
    }
}