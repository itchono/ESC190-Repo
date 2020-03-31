#include "../utilities.h"
#include "../lab4.h"

/** 
open addressing hash table tests
**/

long int numLines3(char* fn) {
    FILE* f = fopen(fn, "r");

    long int linecount = 0;

    char buffer[255];

    while(fgets(buffer, 255, f) != NULL) {
        linecount++;
    }

    fclose(f);
    return linecount;
}


int test1(){
	/** linear probing test
	**/
	int pass = 1;
	printf("===== Test 1: adding keys to Pearson linear probing =====\n");
	PersonalData data1 = (PersonalData) {1, 'F', "Alice", "Li", "XXX", "YYY", 1986, 1, 1};
	PersonalData data2 = (PersonalData) {2, 'M', "Bob", "Kim", "XXX", "YYY", 1999, 5, 12};
	PersonalData data3 = (PersonalData) {9, 'F', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};
	HashTable* table = create_hash_table(3, LINEAR_PROBING);
	
	update_key(&data1, &table);
	update_key(&data2, &table);
	update_key(&data3, &table);

	if(table->buckets[0]->value->SIN != 9) pass = 0;
	if(table->buckets[6]->value->SIN != 1) pass = 0;
	if(table->buckets[7]->value->SIN != 2) pass = 0;
	
	print_buckets(table);
	delete_table(table);
	printf("========== End of Test ==========\n");
	return pass;
}	

int test2(){
	/** quadratic probing test
	**/
	int pass = 1;
	printf("===== Test 2: adding keys to Fibonacci quad probing =====\n");
	PersonalData data1 = (PersonalData) {2, 'F', "Alice", "Li", "XXX", "YYY", 1986, 1, 1};
	PersonalData data2 = (PersonalData) {7, 'M', "Bob", "Kim", "XXX", "YYY", 1999, 5, 12};
	PersonalData data3 = (PersonalData) {10, 'F', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};
	HashTable* table = create_hash_table(3, QUADRATIC_PROBING);
	update_key(&data1, &table);
	update_key(&data2, &table);
	update_key(&data3, &table);

	if(!table->buckets[1] || table->buckets[1]->value->SIN != 2) pass = 0;
	if(!table->buckets[2] || table->buckets[2]->value->SIN != 7) pass = 0;
	if(!table->buckets[5] || table->buckets[5]->value->SIN != 10) pass = 0;
	print_buckets(table);
	delete_table(table);
	printf("========== End of Test ==========\n");
	return pass;
}

int test3() {

	PersonalData data1 = (PersonalData) {2, 'F', "Alice", "Li", "XXX", "YYY", 1986, 1, 1};
	PersonalData data2 = (PersonalData) {7, 'M', "Bob", "Kim", "XXX", "YYY", 1999, 5, 12};
	PersonalData data3 = (PersonalData) {10, 'F', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20};

	HashTable* table = create_hash_table(1, CUCKOO);

	print_status(table);
	print_buckets(table);

	update_key(&data1, &table);
	print_status(table);
	print_buckets(table);
	update_key(&data2, &table);
	print_status(table);
	print_buckets(table);
	update_key(&data3, &table);
	print_status(table);
	print_buckets(table);

	delete_key(10, table);
	print_status(table);
	print_buckets(table);

	delete_table(table);

	return 0;


}

void test4() {
	printf("===== Test 4: simple parse data test =====\n");
	PersonalData** data = parse_data("test_data_LOAD.txt");

	long int numEntries = numLines3("test_data_LOAD.txt") - 1;

	HashTable* table = create_hash_table(1, CUCKOO);

	for (int i = 0; i < numEntries; i++) {
		print_status(table);
		print_buckets(table);
		update_key(data[i],&table);
	}

	print_status(table);
	print_buckets(table);

	delete_table(table);


	for (int i = 0; i < numEntries; i++) {
		free(data[i]);
	}

	free(data);
}


int main(){
	printf("Test cases for part 3 of lab\n");
	printf("PASSED: %d\n", test1());
	printf("PASSED: %d\n", test2());
	test3();
	test4();
	return 0;	
}
