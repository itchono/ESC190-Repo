#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* next;
};

void newHead(struct Node** head) {
    struct Node* newNode = malloc(sizeof(struct Node));

    newNode -> val = 2;
    newNode -> next = NULL;

    struct Node* oldHead = *head;

    *head = newNode; //alter the dereference value of the pointer i.e. modify the single pointer

    free(oldHead);
}

int main() {
    struct Node* head = malloc(sizeof(struct Node));

    (head)->val = 3;
    (head)->next = NULL;

    newHead(&head); // THIS IS OK since we are passing the address of the pointer but we never modifying it


}