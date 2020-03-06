#include <stdio.h>
#include <stdlib.h>

struct LLNode {
    struct LLNode* prev;
    struct LLNode* next;
    double value;

};

struct LL {
    struct LLNode* head;
    struct LLNode* tail;
    int size;
};

void delete_node(struct LL* list,int i);
void insert_node(struct LL* list, int i, double value);
void delete_list(struct LL* list);
struct LL* init_list();