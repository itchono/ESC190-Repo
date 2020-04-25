#include <stdio.h>
#include <stdlib.h>
// circular queue

#define MAX 2

// struct
struct circQueue {
    // instead of doing poiners, we just track indices
    int tail;
    int head;
    int capacity;
    int size;

    int* arr;

};

// Creates a queue of a given size
struct circQueue* createQueue(int size) {
    struct circQueue* q = malloc(sizeof(struct circQueue));
    q->head = 0;
    q->tail = 0;
    q->capacity = size;
    q->size = 0;
    q->arr = calloc(size, sizeof(int)); //calloc, to make everything empty

    return q;
}

// dequeues and returns an element
int dequeue(struct circQueue* q) {
    if (q->size == 0) {
        printf("Queue underflow\n");
        return 0;
    }
    else {
        // simple return logic
        int ret = q->arr[q->head];
        q->arr[q->head] = 0;
        q->size--;
        if (q->size == 0) {
            q->head = 0;
            q->tail = 0; // reset to zero-size configuration
        }
        else q->head = (q->head+1) % q->capacity; // push head
        return ret;
    }
}

// enqueues an element, resizing if needed
void enqueue(struct circQueue** queue, int val) {
    // requires double pointer in case we need new queue

    struct circQueue* q = *queue; // makes it easier to work with
    if (q->head == q->tail && q->size > 0) {
        
        // MAKE NEW QUEUE
        struct circQueue* q2 = createQueue(q->capacity * 2);
        while (q->size > 0) enqueue(&q2, dequeue(q)); 
        deleteQueue(q); // clean up memory
        *queue = q2;
        q = *queue;
    }

    // standard insert
    // insert element
    q->arr[q->tail] = val;
    q->tail = (q->tail+1) % q->capacity; // push tail
    q->size++;
}

// frees all memory used by queue
void deleteQueue(struct circQueue* q) {
    // free all memory
    free(q->arr);
    free(q);
}

void printQueue(struct circQueue* q) {
    int p = 0;

    while (p < q->size) {
        printf("%d  ", q->arr[(p+q->head) % q->capacity]);
        p++;
    }
    printf("\n");
}

int main() {
    // Example code: Enqueues 5, 6, 7 into a queue of capacity 2 (which doubles), dequeues, then deletes queue.
    struct circQueue* q = createQueue(MAX);
    enqueue(&q, 5);
    enqueue(&q, 6);
    enqueue(&q, 7);
    printQueue(q);
    printf("DQ: %d\n", dequeue(q));
    printQueue(q);
    deleteQueue(q);
}