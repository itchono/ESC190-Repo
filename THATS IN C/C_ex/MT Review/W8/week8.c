// Mingde Yin
// March 6, 2020

#include "week8.h"

void delete_node(struct LL* list,int i) {
    struct LLNode* next = list->head;
    struct LLNode* prev = NULL;

    if (i < list->size && i>= 0){

        for (int x = 0; next != NULL && x < list->size; x++) {
            // this type of loop goes though the linked list until reaching its desired position of i.


            if (x == i) {
                // now we have gone though i positions

                if (i != list->size-1) {
                    // if we're not at the last node, we can reassign pointers normally
                    next->next->prev = prev; // point next's prev to prev
                }
                else {
                    list->tail = prev; // change pointer of tail if at the end
                }

                if (i != 0) {
                    // if we're not at the first node, we can reassign poitners normally
                    prev->next = next->next;
                }
                else {
                    list->head = next->next; // change pointer of head if at the start
                }

                free(next); // destroy the memory
                next = NULL; // terminate
                list->size--; // shrink
            }
            else{
                // else, inch along
                prev = next;
                next = next->next;
            }
        }
    }

}
void insert_node(struct LL* list, int i, double value) {

    struct LLNode* boi = list->head;
    boi->prev = NULL;

    struct LLNode* newnode = malloc(sizeof(struct LLNode));
    newnode -> value = value;

    // CASE 1: Empty List
    if (list->size == 0) {
        newnode->next = NULL;
        newnode->prev = NULL;
        list->head = newnode;
        list->tail = newnode;
    }
    else {
        // CASE 2: Head
        if (i == 0) {
            newnode->next = list->head;
            newnode->prev = NULL;
            list->head = newnode;
        }
        else if (i == list->size-1) {
            newnode -> next = NULL;
            newnode -> prev = list->tail;
            list->tail = newnode;
        }

        else {
            for (int x = 0; x < i; x++) {
                struct LLNode* prevboi = boi;

                boi->next = boi->next->next;
                boi = boi->next;
                boi -> prev = prevboi;
            }

            boi->prev->next = newnode;
            newnode->prev = boi->prev;
            newnode->next = boi;
            boi->prev = newnode;

        }

    }

    list->size++;
 

}
void delete_list(struct LL* list) {
    // delete the entire list

    struct LLNode* next = list->head;
    struct LLNode* prev = NULL;
    // these variable names kinda suck

    for (int x = 0; next != NULL && x < list->size; x++) {
        // just delete everything
        prev = next;
        next = next->next;
        free(prev);
    }

    free(list); // DELETE ALL THAT STANDS IN OUR WAY MUHAHAHAHAH

}

void print_list(struct LL* list) {
    struct LLNode* next = list->head;

    printf("\nPrinting List of size %d:\n", list->size);

    for (int x = 0; next != NULL && x < list->size; x++) {

        printf("%g\n", next->value);

        next = next->next;
    }
}

struct LL* init_list() {
    struct LL* list = malloc(sizeof(struct LL));
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;

    return list;
}

int main() {
    struct LL* list = init_list();

    print_list(list);

    insert_node(list, 0,5);
    insert_node(list, 0,4);
    insert_node(list, 0,3);

    print_list(list);

    delete_node(list, list->size-1);
    print_list(list);

    return 0;
}

// hashy boi?

/*

(4) Consider the hash table with chaining presented in lecture. In preparation for lab 4, assume you are given a hash function and
a number of keys int n, number of buckets int b.

..How would you perform the following operations in C? If each of the following is a function, what are the types of
the input arguments and return values?

- create a new hash table with b buckets
args: int b
return: hash table struct pointer

create an array of buckets using calloc, from 0 to n

each bucket stores either an object or a int etc.

(apply hash to each n and store the data matched with n in bucket b

array[hash(K)] = (K);)


- insert a key into the associated bucket without a collision occuring
args: key K, hash table h

if array[hash(N)] != 0

then, for (int x = hash(K); x < n; x++) {
    if (array[x] == 0)
        array[x] = K
}

- insert a key into the associated bucket with a collision occuring, with linked-list chaining
args: key K, hash table h

if array[hash(N)] != 0
then, append element to linked list


- deleting the hash table (with no memory leaks or valgrind errors)

args: hash table h

free each element in calloc'd array

..Look up the "trivial hash function". Hash the following keys using the trivial hash function:
print([ord(i) for i in "DOG!!!"])

- "CATCAT"
676584676584
0x9d8796dce8

- "DOG!!!"
687971333333
0xa02e4974d5

- "LOVEESC190"
76798669698367495748
0x429cbaf31a1c01e44

- "CISCOOL"
67738367797976
0x3d9b9159aad8

(Hint: Use the ASCII table and part 1 of this exercise)


*/