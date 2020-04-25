#include <stdlib.h>
#include <stdio.h>

#define NUMSTORES 100
#define NUMGELATOS 10
// assumed

// PART A
// Implemented using dynamic arrays
struct Gelato {
    char* flavour;
    int popularityNum;
    int quantity;
};

struct AlgosStore {
    char* managerName;
    int numStaff;
    struct Gelato gelatos[NUMGELATOS];
};

struct AlgosGelatos {
    char* ceoName;
    struct AlgosStore stores[2*NUMSTORES];
    // PART D: modified to be 2* the number of stores
};

// PART B
struct AlgosGelatos algo; // assume this actually has stuff in it

void PartB() {
    for (int i = 0; i < NUMSTORES; i++) {
        struct AlgosStore store = algo.stores[i];

        printf("STORE NUMBER %d:\n", i);
        printf("Name of manager: %s\n", store.managerName);
        printf("Number of staff: %d\n", store.numStaff);
        printf("GELATOS:\n");
        for (int g = 0; g < NUMGELATOS; g++) {
            printf("\tFlavour: %s\tPopularity: %d\tQuanitity:%d\n", store.gelatos[g].flavour, store.gelatos[g].popularityNum, store.gelatos[g].quantity);
        }

    }
}

void PartC(struct AlgosGelatos* alg, struct Gelato gelatoArr[NUMGELATOS]) {
    // Therefore, the distributor gives quantity/NUMSTORES to each store.

    for (int i = 0; i < NUMSTORES; i++) {
        for (int g = 0; g < NUMGELATOS; g++) {
            alg->stores[i].gelatos[g].quantity += gelatoArr[g].quantity/NUMSTORES;
            // we don't update the other gelato array.
        }
    }
}
