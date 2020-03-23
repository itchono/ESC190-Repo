#include "../utilities.h"
#include "../lab4.h"

/**
Testing part 3 of the lab (data loading)
**/

long int numLines2(char* fn) {
    FILE* f = fopen(fn, "r");

    long int linecount = 0;

    char buffer[255];

    while(fgets(buffer, 255, f) != NULL) {
        linecount++;
    }

    fclose(f);
    return linecount;
}

void test1(){
	printf("===== Test 1: simple parse data test =====\n");
	PersonalData** data = parse_data("test_data_LOAD.txt");

	long int numEntries = numLines2("test_data_LOAD.txt") - 1;

	for (int i = 0; i < numEntries; i++) {
		free(data[i]);
	}

	free(data);
}

void test2(){
	printf("===== Test 2: counter_intelligence =====\n");
	char* load_fn = "test_data_LOAD.txt";
	char* update_fn = "test_data_UPDATE.txt";
	char* validate_fn = "test_data_VALIDATE.txt";
	char* spies_fn = "spies.txt";
	counter_intelligence(load_fn, update_fn, validate_fn, spies_fn);
}

void test3(){
	printf("===== Test 3: counter_intelligence full data =====\n");
	char* load_fn = "full_data_LOAD.txt";
	char* update_fn = "full_data_UPDATE.txt";
	char* validate_fn = "full_data_VALIDATE.txt";
	char* spies_fn = "full_spies.txt";
	counter_intelligence(load_fn, update_fn, validate_fn, spies_fn);
}


int main(){
	test1();
	test2();
	test3();
	return 0;	
}
