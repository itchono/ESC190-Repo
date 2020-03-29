#include "lab4.h"
#include <string.h>
#include <math.h>

long int numLines(char* fn) {
    FILE* file = fopen(fn, "r");

    long int lines = 0;

    char buffer[MAX_NAME_LEN*2 + BANK_ACC_LEN + PASSPORT_LEN + 27];

    while(fgets(buffer, MAX_NAME_LEN*2 + BANK_ACC_LEN + PASSPORT_LEN + 27, file)) {
        lines++;
    }

    fclose(file);
    return lines;
}

PersonalData** parse_data(char* fn){
    /*Return apointer  to PersonalData* array parsed  from the file with  filename fn. 
    The memory allocated for these pointers  should  be dynamically sized based  on  the  size of the file. 
    You may not make any assumptions  on the number of data entries. It can be very large.
     Hint: use a helper function  to  count  the number of lines as a long int*/


    long int entries = numLines(fn) - 1;

    PersonalData** personal_data = calloc(entries, sizeof(PersonalData*));

        INT_SIN SIN; // 9-digit number
        char gender; 
        char first_name[MAX_NAME_LEN]; 
        char last_name[MAX_NAME_LEN]; 
        char passport_num[PASSPORT_LEN]; 
        char bank_acc_num[BANK_ACC_LEN]; 
        int dob_year;
        int dob_month;
        int dob_day;

        FILE* file = fopen(fn, "r");//WHAT FILE TO PUT SINCE THEY GIVE US A COUPLE?

        char headers[1000];

        int LINE_LENGTH = MAX_NAME_LEN*2 + BANK_ACC_LEN + PASSPORT_LEN + 27;

        fgets(headers, LINE_LENGTH, file);

        int i = 0;

        // long int	char	string	string	string		string			int-int-int

        while(fscanf(file,"%ld\t%c\t%s\t%s\t%s\t%s\t%d-%d-%d\n",&SIN,&gender,first_name,last_name,passport_num,bank_acc_num,&dob_year,&dob_month, &dob_day)!= EOF){
            PersonalData* data = malloc(sizeof(PersonalData));//is that how we do the size of the file?

            data -> SIN = SIN;
            data -> gender = gender;
            strcpy(data -> first_name, first_name);
            strcpy(data -> last_name, last_name);

            strcpy(data->bank_acc_num, bank_acc_num);
            strcpy(data->passport_num, passport_num);

            data->dob_day = dob_day;
            data->dob_month = dob_month;
            data->dob_year = dob_year;

            personal_data[i] = data;
            i++;
        }//do i even need this? its linking differetn names...
        fclose(file);
        return personal_data;
}


void counter_intelligence(char* load, char* update, char* validate, char* outfile){
//Given authentic personal identities in the fileswith  filenamesloadand update, 
//verify the  authenticity  of  the  data in validateand  write each SINassociated  with  a fake identity  on a new  line in the file outfile.
//This function shouldcall parse_data
    FILE* loadF = fopen(load, "r");
    FILE* updateF = fopen(update, "r");
    FILE* validateF = fopen(validate, "r");
    FILE* outfileF = fopen(outfile, "w");

    long int num_entries_load = numLines(load)-1;
    long int num_entries_validate = numLines(validate)-1;
    long int num_entries_update = numLines(update)-1;

    HashTable* table = create_hash_table(ceil(log2(num_entries_load)), 0);

    PersonalData** datalist = parse_data(load);

    for (long int i = 0; i < num_entries_load; i++) {
        update_key(datalist[i], &table); // INSERTS entries into table for each entry that we have in the load file.
    }

    PersonalData** datalist2 = parse_data(update);

    for (long int i = 0; i < num_entries_update; i++) {
        update_key(datalist2[i], &table); // UPDATES entries into table for each entry that we have in the update file.
    }


    PersonalData** datalist3 = parse_data(validate);

    for (long int i = 0; i < num_entries_validate; i++) {

        PersonalData* val = datalist3[i];

        PersonalData* k = lookup_key(val->SIN, table);


        if (
            k == NULL ||
            val->gender != k->gender ||
            val->dob_day != k->dob_day ||
            val->dob_month != k-> dob_month ||
            val->dob_year != k->dob_year ||

            strcmp(val->first_name, k->first_name) ||
            strcmp(val->last_name, k->last_name) ||
            strcmp(val->bank_acc_num, k->bank_acc_num) ||
            strcmp(val->passport_num, k->passport_num)) 
            {
            fprintf(outfileF, "%ld\n", val->SIN);
        }
    }



    fclose(loadF);
    fclose(updateF);
    fclose(validateF);
    fclose(outfileF);
    delete_table(table);

    for (long int i = 0; i < num_entries_load; i++) {
        free(datalist[i]); // deletes all the personaldata that we loaded
    }

    for (long int i = 0; i < num_entries_update; i++) {
        free(datalist2[i]);
    }

    for (long int i = 0; i < num_entries_validate; i++) {
        free(datalist3[i]);
    }

    // ALSO, we need to free the personal data lists.
}
