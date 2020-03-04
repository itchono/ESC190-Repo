#include <stdio.h>
#include <stdlib.h>


struct banana {
    int length;

};

struct banana* gimmeBanana() {
    struct banana* b = malloc(sizeof(struct banana));


    struct banana bOBJ;

    bOBJ.length = 123;

    (*b).length = 123;

    b->length = 123;

    

    return b;

}


int main() {

    printf("%d",gimmeBanana()->length);
    
    return 0;
}