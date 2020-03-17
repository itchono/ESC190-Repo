#include "lab4.h"

long int numLines(char* fn) {
    FILE* f = fopen(fn, "r");

    long int linecount = 0;

    char buffer[255];

    while(fgets(buffer, 255, f) != NULL) {
        linecount++;
    }
    return linecount;
}

PersonalData** parse_data(char* fn){
    long int linecount = numLines(fn);

    
}


void counter_intelligence(char* load, char* update, char* validate, char* outfile){
}
