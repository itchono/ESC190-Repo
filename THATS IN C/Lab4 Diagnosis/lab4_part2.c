#include "lab4.h"
#include <math.h>
#define NUM_HASH_FUNCS 3

HashTable *create_hash_table(int m, int mode){
/**
    create a new hash table of size 2^m and return the pointer to the newly created table.
    Fully initialize the state of the table.

    Sample IO
    HashTable* table0 = create_hash_table(1, CLOSED_ADDRESSING);
    print_status(table0);
	
	HashTable* table1 = create_hash_table(1, LINEAR_PROBING); 
	print_status(table1); 
	
	HashTable* table2 = create_hash_table(1, CUCKOO); 
	print_status(table2); 

    Stdout:
    Table capacity:    		2 
    Table load:        		0 
    Table load factor: 		0.00
	Mode:			   		closed
	
	Table capacity:         2 
	Table load:             0 
	Table load factor:      0.00 
	Mode:                   linear

	Table capacity:         2 
	Table load:        		0 
	Table load factor:      0.00 
	Mode:                   cuckoo 	

**/
    hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	/*typedef struct entries{
    int key_number = k;
    int bucket_number = b;} entries;*///use what is given
	
	HashTable* hash_table = malloc(sizeof(HashTable)); // good
		hash_table -> mode = mode;
		hash_table -> num_buckets = pow(2, m); // evalates 2 to the power of m, NOT 2 XOR m

		hash_table->num_keys = 0;

		hash_table->buckets = calloc(hash_table->num_buckets, sizeof(Node*));



	for(int i=0; i <= num_buckets; i++){
		buckets -> node* -> node;
	}


	// good
	return hash_table//return a pointer to empty, fully initialized hash table;
}

void update_without_resize(PersonalData * data, HashTable *table) {
	/**
	Insert/update the data corresponding to SIN of data.
	Update all book-keeping information.
	**/

	// table[SIN] --> NODE

	// Chaining  0

	// Linear probing  1

	// Quadratic Probing  2

	// mode 

	// Cuckoo Hashing

	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	// mode = 0;

	INT_HASH b = (hash_funcs[table->mode])(data->SIN, table->buckets);

	// 201

	// Someone's already there!

	/*

	F: 20010920 --> 201

	F {
		Temporary Room In Mind of where I might be
	}
	
	20011016 --> NULL

	20010920 --> ME

	Room 201: [PERSON:20010101]Door[ME:20010920]Door[]

	*/

	/*

	Linear Probing

	20010920

	--> 002 = i

	p = 0

	5

	001: []  (p = 4) + i --> 001
	002: [P] (p = 0) + i --> 002
	003: [P] (p = 1) + i --> 003
	004: [P] (p = 2) + i --> 004
	005: [P] (p = 3) + i --> %(number of buckets)

	*/

	/*

	20010920

	002

	002: [P] i=2 + p=0^2

	003: [P] i=2 + p=1^2

	006: [P] i=2 + p=2^2

	p = (number of rooms)

	for (int p = 0; p < table->num_buckets; p++)

	011: [ME]

	018 <- ???

	018 % (15) --> 


	*/



	table->buckets[b] -> value = data;

}

void update_key(PersonalData * data, HashTable **table){
	/** 
	Using update_without_resize and resize_table,
	update the hash table while ensuring the final table's 
	load factor does not exceed MAX_LOAD_FACTOR.
	
	Note that this function updates the pointer to the table with the
	return of resize_table and deletes the original table.
	
	Sample IO
	HashTable * table1 = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data_a = {0, 'F', "Alice","Smith","XXX", "YYY", 1995, 12, 12};
	PersonalData data_b = {1, 'M', "Bob","Xu","XXX", "YYY", 1994, 12, 12};
	PersonalData data_c = {10, 'M', "Jeremy","Voyager","XXX", "YYY", 1994, 19, 12};
	update_key(&data_a, table1);
	update_key(&data_b, table1);
	update_key(&data_c, table1);
	print_buckets(table1);
	
	PersonalData data1 = {2, 'F', "Alice", "Li", "XXX", "YYY", 1986, 1, 1}; 
	PersonalData data2 = {7, 'M', "Bob", "Kim", "XXX", "YYY", 1999, 5, 12}; 
	PersonalData data3 = {10, 'F', "Eve", "Pooh", "XXX", "YYY", 1993, 4, 20}; 
	HashTable* table2 = create_hash_table(3, LINEAR_PROBING); 
	update_key(&data1, table2); 
	update_key(&data2, table2); 
	update_key(&data3, table2); 
	print_buckets(table2);

	Stdout:
	Bucket 0:    SIN: 000000000     
	Bucket 1:    SIN: 000000001
	Bucket 2:    SIN: 000000010     
	Bucket 3:     
	Bucket 4:     
	Bucket 5:     
	Bucket 6:     
	Bucket 7:   
	
	Bucket   0:     
	Bucket   1:     SIN:    2 
	Bucket   2:     SIN:    7 
	Bucket   3:     
	Bucket   4:      
	Bucket   5:     SIN:    10 
	Bucket   6:     
	Bucket   7:     
	**/
	
	
	// if the new LF > MAX_LF

	// then we need to resize


	float new_LF = (float)(*table)->num_keys+1/(*table)->num_buckets;

	// ONLY IF WE are adding key

	// 1: update only

	// 2: add key
	

	

}

int delete_key(INT_SIN SIN, HashTable *table){
/**
	Delete key value, return 1 if successful,
	0 if key not in table - update book-keeping information.
	Ensure no memory leaks. Do not free memory that you did not allocate.

	Sample IO
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data_a = {0, 'F', "Alice","Smith","XXX", "YYY", 1995, 12, 12};
	update_key(&data_a, table);
	delete_key(0, table);
	print_status(table);
	print_buckets(table);

	Stdout:
	Table capacity:    2 	
	Table load:        0 
	Table load factor: 0.00 
	Bucket 0: 
	Bucket 1: 
	Bucket 2:       
	Bucket 3:     
	Bucket 4:     
	Bucket 5:     
	Bucket 6:     
	Bucket 7:  
	
**/
	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	// mode = 0;

	INT_HASH b = (hash_funcs[table->mode])(data->SIN, table->buckets);

	switch(table->mode) {
		case 0:
		// chaining
		;
		Node * bucket = table->buckets[b];
		while (bucket != NULL){
			if (bucket->value->SIN == SIN) {
				return bucket->value;
			}
			bucket = bucket->next;
		}

		return 0;
		break;

		case 1:
		// linear
		;
		int p1 = 0;
		while (p1 < table->num_buckets) {
			int index = (b + p1) % table->num_buckets; // which bucket we're accessing

			if(table->buckets[index] && table->buckets[index]->value->SIN == SIN ){
				free(table->buckets[index]);
				table->num_keys--;
				return 1;
			}

			p1++;
		}
		return 0;
		break;

		case 2:
		// quad
		int p2 = 0;
		while (p2 < table->num_buckets) {
			int index = (b + pow(p2,2)) % table->num_buckets; // which bucket we're accessing

			if(table->buckets[index] && table->buckets[index]->value->SIN == SIN ){
				free(table->buckets[index]);
				table->num_keys--;
				return 1;
			}

			p2++;
		}
		return 0;

		break;
	}
}

PersonalData* lookup_key(INT_SIN SIN, HashTable *table){
	/** 
	return pointer to the PersonalData struct associated with SIN.
	return NULL if the SIN is not in table.
	
	Sample IO
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	PersonalData data = {8, 'F', "Alice","Xu", "AB12345", "99999-999-999999999999", 1960, 31, 12};
	update_key(&data, table);
	print_personal_data(lookup_key(data.SIN, table));

	Stdout:
	SIN:        		8 
	Gender:     		F 
	Name:        		Xu, Alice 
	Passport #:    		AB12345 
	Bank account #:		99999-999-999999999999 
	Date of birth:		12-31-1960 
	**/
	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	// mode = 0;

	INT_HASH b = (hash_funcs[table->mode])(data->SIN, table->buckets);

	switch(table->mode) {
		case 0:
		// chaining
		;
		Node * bucket = table->buckets[b];
		while (bucket != NULL){
			if (bucket->value->SIN == SIN) {
				return bucket->value;
			}
			bucket = bucket->next;
		}

		return NULL;
		break;

		case 1:
		// linear
		;
		int p1 = 0;
		while (p1 < table->num_buckets) {
			int index = (b + p1) % table->num_buckets; // which bucket we're accessing

			if(table->buckets[index] && table->buckets[index]->value->SIN == SIN ){
				return table->buckets[index]->value;
			}

			p1++;
		}
		return NULL;
		break;

		case 2:
		// quad
		int p2 = 0;
		while (p2 < table->num_buckets) {
			int index = (b + pow(p2,2)) % table->num_buckets; // which bucket we're accessing

			if(table->buckets[index] && table->buckets[index]->value->SIN == SIN ){
				return table->buckets[index]->value;
			}

			p2++;
		}
		return NULL;

		break;
	}
}

void delete_table(HashTable *table){
	/**
	Delete the table and ensure no memory leaks. Do NOT free memory that you 
	did not allocate.

	Sample IO
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	delete_table(table);
	**/
	for (INT_HASH b = 0; b < table->num_buckets; b++){ 
		Node * bucket = table->buckets[b];
		while (bucket != NULL){
			free(bucket);
			bucket = bucket->next;
		}
	}

	free(table->buckets);
	free(table);
}

HashTable *resize_table(HashTable *table){
	/**
	Return a pointer to a new table with size 2^(m+1), where 
	the original table "table" has size 2^m.
	Delete the original table, ensure no memory leaks. 
	Update all book-keeping information.

	SampleIO
	HashTable * table = create_hash_table(2, CLOSED_ADDRESSING);
	table = resize_table(table);
	print_status(table);

	Stdout:
	Table capacity:    8 
	Table load:        0 
	Table load factor: 0.00 
	**/
	
	int m = log2(2*table->num_buckets);

	HashTable* newTable = create_hash_table(m, table->mode);

	for (INT_HASH b = 0; b < table->num_buckets; b++){ 
		Node * bucket = table->buckets[b];
		while (bucket != NULL){
			if (bucket->value == NULL);
			else update_without_resize(bucket->value, newTable);
			bucket = bucket->next;
		}
	}

	delete_table(table);
	return newTable;
}
