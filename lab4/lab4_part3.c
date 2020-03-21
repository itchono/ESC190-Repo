#include "lab4.h"

long int numLines(char* fn) {
    FILE* f = fopen(fn, "r");

    long int linecount = 0;

    char buffer[255];

    while(fgets(buffer, 255, f) != NULL) {
        linecount++;
    }

    fclose(f);
    return linecount;
}

PersonalData** parse_data(char* fn){
    // IPR

    long int linecount = numLines(fn);
    long int numEntries = linecount - 1;

    long int i = 0;

    PersonalData** data = calloc(numEntries, sizeof(PersonalData*));

    FILE* f = fopen(fn, "r");
    char buffer[255];

    fgets(buffer, 255, f); // flush line 1;

    while(fgets(buffer, 255, f) != NULL) {


        
    }
    fclose(f);

    
}


void counter_intelligence(char* load, char* update, char* validate, char* outfile){
}
