#include "lab4.h"
#include <string.h>
#include <math.h>

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
    // READY TO TEST
    long int numEntries = numLines(fn) - 1;

    // Done
    PersonalData** data = calloc(numEntries, sizeof(PersonalData*));

    FILE* fin = fopen(fn, "r");

    int MAX_LINE_LENGTH = MAX_NAME_LEN*2 + BANK_ACC_LEN + PASSPORT_LEN + 9 + 10 + 1 + 5 + 1 + 1;
    // name (1st and last) + bank# + passport# + SIN + dob + gender + 5 tabs + name space + \0

    char buffer[MAX_LINE_LENGTH + 1]; // line buffer

    fgets(buffer, MAX_LINE_LENGTH + 1, fin); // purge first line by force reading --> advance to next position

    long int i = 0; // index of employee

    while(fgets(buffer, MAX_LINE_LENGTH + 1, fin) != NULL) {
        data[i] = malloc(sizeof(struct PersonalData)); // object

        // Twist the edges of spacetime to use strtok
        data[i] -> SIN = atoi(strtok(buffer, "\t"));
        data[i] -> gender = (strtok(NULL, "\t"))[0];

        strcpy(data[i]->first_name, strtok(NULL, "\t"));
        strcpy(data[i]->last_name, strtok(NULL, "\t"));
        
        strcpy(data[i]->passport_num, strtok(NULL, "\t"));
        strcpy(data[i]->bank_acc_num, strtok(NULL, "\t"));

        data[i]->dob_year = atoi(strtok(NULL, "-"));
        data[i]->dob_month = atoi(strtok(NULL, "-"));
        data[i]->dob_day = atoi(strtok(NULL, "-"));


        i++;
    }

    fclose(fin);

    return data;
}


void counter_intelligence(char* load, char* update, char* validate, char* outfile){

    long int numLoad = numLines(load) - 1;

    PersonalData** loadP = parse_data(load);

    HashTable* table = create_hash_table(ceil(log2(numLoad)), 0); // use trivial hash to easy

    for (long int i = 0; i < numLoad; i++) {
        update_key(loadP[i], &table);
    }


    long int numUpdate = numLines(update) - 1;

    PersonalData** updP = parse_data(update);

    for (long int i = 0; i < numUpdate; i++) {
        update_key(updP[i], &table);
    }
    // real people

    long int numVal = numLines(validate) - 1;

    PersonalData** valP = parse_data(validate);
    // check fakes

    FILE* fout = fopen(outfile, "w");

    for (long int i = 0; i < numVal; i++) {
        PersonalData* check = lookup_key(valP[i]->SIN, table);

        // check all fields
        if (check == NULL || 
        strcmp(check->first_name, valP[i]->first_name) || 
        strcmp(check->last_name, valP[i]->last_name) || 
        strcmp(check->bank_acc_num, valP[i]->bank_acc_num) || 
        strcmp(check->passport_num, valP[i]->passport_num) ||
        (check->gender - valP[i]->gender) ||
        (check->dob_year - valP[i]->dob_year) ||
        (check->dob_month - valP[i]->dob_month) ||
        (check->dob_day - valP[i]->dob_day)) fprintf(fout, "%ld\n", valP[i]->SIN);

    }
    fclose(fout);

    delete_table(table);

    for (long int i = 0; i < numLoad; i++) {
        free(loadP[i]);
    }
    free(loadP);
    for (long int i = 0; i < numUpdate; i++) {
        free(updP[i]);
    }
    free(updP);
    for (long int i = 0; i < numVal; i++) {
        free(valP[i]);
    }
    free(valP);

}
