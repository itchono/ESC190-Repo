#include "lab4.h"
#include <math.h>
#define NUM_HASH_FUNCS 3

HashTable *create_hash_table(int m, int mode){

	// READY TO TEST
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

	HashTable* ht = malloc(sizeof(HashTable));

	ht->num_buckets = (int)pow(2,m);
	ht->mode = mode;
	ht->num_keys = 0;
	ht->buckets = calloc(ht->num_buckets, sizeof(Node*)); // fully initialized

}

void update_without_resize(PersonalData * data, HashTable *table) {


	// READY TO TEST
	/**
	Insert/update the data corresponding to SIN of data.
	Update all book-keeping information.
	**/

	// assume size is OK
	
	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	INT_HASH k = (hash_funcs[table->mode])(data->SIN, table->num_buckets); // key to map to, based on mode

	if (lookup_key(data->SIN, table) == NULL) {
		// create new entry
		if(table->buckets[k]) {
			switch (table->mode)
			{
			case 0:
				// linked list push
				;
				Node* oldhead = table->buckets[k];
				table->buckets[k] = malloc(sizeof(Node));
				table->buckets[k]->next = oldhead;
				table->buckets[k]->value = data; // new node
				table->num_keys++;
				break;

			case 1:
				// linear probe
				while (table->buckets[k]) {
					k++;
				}
				// now we have a bucket

				table->buckets[k] = malloc(sizeof(Node));
				table->buckets[k]->next = NULL;
				table->buckets[k]->value = data; // new node
				table->num_keys++;
				break;

			case 2:
				;
				int i = 1;

				while(table->buckets[k]) {
					k += (int) pow(i, 2);
					i++;
				}
				// now we have a bucket
				table->buckets[k] = malloc(sizeof(Node));
				table->buckets[k]->next = NULL;
				table->buckets[k]->value = data; // new node
				table->num_keys++;
				break;

			case 3:
				// cuckoo
				while (table->buckets[k]) {
					k++;
				}
				// now we have a bucket

				table->buckets[k] = malloc(sizeof(Node));
				table->buckets[k]->next = NULL;
				table->buckets[k]->value = data; // new node
				table->num_keys++;
				break;
			
			default:
				break;
			}

		} else{
			// if it's a new table
			table->buckets[k] = malloc(sizeof(Node));
			table->buckets[k]->next = NULL;
			table->buckets[k]->value = data; // new node
			table->num_keys++;
		}
	}
	else {
		// update key in table
		switch (table->mode)
		{
		case 0:
			;
			// linked list push
			Node* currNode = table->buckets[k];
			if (currNode) {
				while (currNode->next) {
					if(currNode->value->SIN == data->SIN) {
						PersonalData* v = currNode->value;
						currNode->value = data;
						free(v);
					}
					currNode = currNode->next;
				}
			}
			break;

		case 1:
			// linear probe
			while (table->buckets[k]) {
				if (table->buckets[k]->value->SIN == data->SIN) {
					PersonalData* v = table->buckets[k]->value;
					table->buckets[k]->value = data;
					free(v);
				}
				k++;
			}
			break;

		case 2:
			;
			int i = 1;

			while(table->buckets[k]) {
				if (table->buckets[k]->value->SIN == data->SIN) {
					PersonalData* v = table->buckets[k]->value;
					table->buckets[k]->value = data;
					free(v);
				}
				k += (int) pow(i, 2);
				i++;
			}
			break;

		case 3:
			// cuckoo
			break;
		
		default:
			break;
		}

	}

}

void update_key(PersonalData * data, HashTable **table){

	// IPR
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

	if (((*table)->num_keys+1.0) / (*table)->num_buckets > MAX_LOAD_FACTOR && lookup_key(data->SIN, *table) == NULL) {
		// if load factor is unacceptable and yet we are adding a new key
		*table = resize_table(*table);
	}
	
	update_without_resize(data, *table);
}

int delete_key(INT_SIN SIN, HashTable *table){

	// READY TO TEST
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

	// first confirm the key exists

	if (!lookup_key(SIN, table)) return 0;

	INT_HASH k = (hash_funcs[table->mode])(SIN, table->num_buckets); // key to map to, based on mode

	switch (table->mode)
	{
	case 0:
		// linked list push
		;
		Node* currNode = table->buckets[k];
		Node* prev = NULL;
		while (currNode->next) {
			// LL mode
			if(currNode->value->SIN == SIN) {
				if(prev) prev->next = currNode->next;
				free(currNode->value);
				free(currNode);
				table->num_keys--;
				return 1;
			}
			prev = currNode;
			currNode = currNode->next;
		}

		if (!currNode->next && currNode){
			// just the node exists
			free(table->buckets[k]->value);
			free(table->buckets[k]);
			table->buckets[k] = NULL;
			table->num_keys--;
			return 1;
		}
		return 0;
		break;

	case 1:
		// linear probe
		while (table->buckets[k]) {
			if (table->buckets[k]->value->SIN == SIN) {
				free(table->buckets[k]->value);
				free(table->buckets[k]);
				table->buckets[k] = NULL;
				table->num_keys--;
				return 1;
			}
			k++;
		}
		return 0;
		break;

	case 2:
		;
		int i = 1;

		while(table->buckets[k]) {
			if (table->buckets[k]->value->SIN == SIN) {
				free(table->buckets[k]->value);
				free(table->buckets[k]);
				table->buckets[k] = NULL;
				return 1;
			}
			k += (int) pow(i, 2);
			i++;
		}
		return 0;
		break;

	case 3:
		// cuckoo
		break;
	
	default:
		break;
	}

	
}

PersonalData* lookup_key(INT_SIN SIN, HashTable *table){

	// READY TO TEST
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

	INT_HASH k = (hash_funcs[table->mode])(SIN, table->num_buckets); // key to map to, based on mode

	switch (table->mode)
	{
	case 0:
		;
		Node* currNode = table->buckets[k];
		if (currNode) {
			do {
				if(currNode->value->SIN == SIN) {
					return currNode->value;
				}
				currNode = currNode->next;
			} while (currNode);
		}
		
		return NULL;
		break;

	case 1:
		// linear probe
		while (table->buckets[k]) {
			if (table->buckets[k]->value->SIN == SIN) {
				return table->buckets[k]->value;
			}
			k++;
		}
		return NULL;
		break;

	case 2:
		;
		int i = 1;

		while(table->buckets[k]) {
			if (table->buckets[k]->value->SIN == SIN) {
				return table->buckets[k]->value;
			}
			k += (int) pow(i, 2);
			i++;
		}
		return NULL;
		break;

	case 3:
		// cuckoo
		break;
	
	default:
		break;
	}
}

void delete_table(HashTable *table){

	// READY TO TEST
	/**
	Delete the table and ensure no memory leaks. Do NOT free memory that you 
	did not allocate.

	Sample IO
	HashTable * table = create_hash_table(1, CLOSED_ADDRESSING);
	delete_table(table);
	**/

	if (table->mode == 0) {
		// go to linked lists and PURGE
		for (int x = 0; x < table->num_buckets; x++) {
			if (table->buckets[x]) {
				Node* currNode = table->buckets[x];
				while (currNode->next) {
					Node* n = currNode->next;
					free(currNode->value);
					free(currNode);
					currNode = n;
				}
			}
		}

	}
	else if (table->mode == 1 || table->mode == 2) {
		// search through every bucket and PURGE

		for (int x = 0; x < table->num_buckets; x++) {
			if (table->buckets[x]) {
				free(table->buckets[x]->value); // get rid of the data in the node
				free(table->buckets[x]); // get rid of the thing stored there
			}
			
		}
	}
	free(table->buckets); // delete the array of pointers to nodes
	free(table);



}

HashTable *resize_table(HashTable *table){
	/**
	Return a pointer to a new table with size m+1, where 
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

	INT_HASH n2 = table->num_buckets * 2;

	HashTable* t2 = create_hash_table(log2(n2), table->mode);

	for (INT_HASH b = 0; b < table->num_buckets; b++){ 
		// similar to utilities code
		Node * bucket = table->buckets[b];

		while (bucket != NULL){
			if (bucket->value != NULL) {
				update_without_resize(bucket->value, t2);
			}
			bucket = bucket->next;
		}
	}

	delete_table(table);

	return t2;
	
}
