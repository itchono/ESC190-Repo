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
	
	HashTable* hash_table = malloc(sizeof(HashTable));
		hash_table -> mode = mode;
		hash_table -> num_buckets = (INT_HASH) pow(2, m);
		hash_table -> num_keys = 0;
		hash_table -> buckets = calloc(hash_table -> num_buckets, sizeof(Node*));//want size of node* because want size and number of elemnts in array
	return hash_table;//return a pointer to empty, fully initialized hash table;
}

void update_without_resize(PersonalData * data, HashTable *table) {
	/** data is just one data
	Insert/update the data corresponding to SIN of data.
	Update all book-keeping information.
	**/
/*Personaldata -> data
Node = <personal data *, node*>
replace personal dara with data*/
	//trivial_hash gives us the number
	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;
	//hash funcs is a pointer to a function to part 1

	INT_HASH b = (hash_funcs[table -> mode])(data -> SIN, table -> num_buckets);//(hash_funcs[table -> mode]) replaced by the fucntion of part 1 based on the mode
	//b is a specific bucket, trivial hash gives the bucket where we want data 
	
	//collison handling for each type, linked list (chaining)
	
	// collison handling pearson, linear by finding next empty index
	//don't forget to go back to begining if all full, want to reach the orginal index, p = 0 +i...., once reach the end, modulus by #buckets 
	
	//collision fibonacci, quadratic where jump by the starts place + p =0^2, p inc by 1
	//if next index out of bound, do the possible index % num_buckets, up until p = #buckets 

	if (lookup_key(data->SIN, table) == NULL) {

		// NEW KEY --> insert

		switch (table -> mode)
		{
		case 0: //chaining
			;//need this to declare a new variable in a switch statement
			
			// we want to push to a linked list
			Node* first = table->buckets[b];
			Node* newNode = malloc(sizeof(Node));

			newNode->next = first;
			newNode->value = data;

			table->buckets[b] = newNode;
			table->num_keys++;
			break;

		case 1: //linear probing
			;
			int p1 = 0;
			int index1 = b;

			while(p1 < table -> num_buckets && table->buckets[index1]){
				index1 = (b + p1) % table -> num_buckets;
				p1++;
			}

			Node* newNode1 = malloc(sizeof(Node));

			newNode1->next = NULL;
			newNode1->value = data;

			table->buckets[index1] = newNode1;
			table->num_keys++;

			break;
		
		case 2://quadratic probing
			;
			int p2 = 0;
			int index2 = b;

			while(p2 < table -> num_buckets && table->buckets[index2]){
				index2 = (b + (INT_HASH) pow(p2, 2) % table -> num_buckets);
				p2++;
			}

			Node* newNode2 = malloc(sizeof(Node));

			newNode2->next = NULL;
			newNode2->value = data;

			table->buckets[index2] = newNode2;
			table->num_keys++;
			
		}
	
	}
	
	
	
	else {
		// EXISTING KEY --> update
		// basically, we need to "look up the key first"
		switch (table -> mode)
		{
		case 0: //chaining
			;//need this to declare a new variable in a switch statement
			Node * bucket = table -> buckets[b];
			while (bucket != NULL){
				if(bucket -> value -> SIN == data->SIN){// check SIN of that bucket
					bucket -> value = data;}
				bucket = bucket -> next;
			}
			break;

		case 1: //linear probing
			;
			int p1 = 0;
			while(p1 < table -> num_buckets){
				int index = (b + p1) % table -> num_buckets;//bucket we are accessing
				if(table -> buckets[index] && table -> buckets[index] -> value -> SIN == data->SIN){
					table -> buckets[index] -> value = data;
				}
				p1++;
			}
			break;
		
		case 2://quadratic probing
			;
			int p2 = 0;
			while(p2 < table -> num_buckets){
				int index = (b + (INT_HASH) pow(p2, 2) % table -> num_buckets);//bucket we are accessing
				if(table -> buckets[index] && table -> buckets[index] -> value -> SIN == data->SIN){
					table -> buckets[index] -> value = data;
				}
				p2++;
			}
			break;
		}

	}
	
	
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


	//if new_load factor > max load factor need to update
	float new_load_factor = ((float)(*table) -> num_keys +1) /(*table) -> num_buckets;//load factor num_keys/num_buckets

	if(new_load_factor > MAX_LOAD_FACTOR && lookup_key(data -> SIN, *table) == NULL){
		*table = resize_table(*table);
	}

	update_without_resize(data, *table);

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
/* 3 cases:
	- point to one bucket which we delete so now point to NULL
	- have multiple buckets and delete a bucket in the midddle, want to point the one before deleted to the one after deleted
	- have first of many buckets deleted want to point to the new first one
*/

	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	INT_HASH b = (hash_funcs[table -> mode])(SIN, table -> num_buckets);
	switch (table -> mode){
	case 0: //chaining
		;
		Node* current_node = table -> buckets[b];
		Node* previous_node = NULL;

		/*

		Bucket: [A:Next = NULL]

		buckets[b] = A->next = NULL;
		*/

		while(current_node){
			if(current_node->value->SIN == SIN){

				if (previous_node) {
					// a previous node exists.
					previous_node->next = current_node->next;
				}
				else {
					// this is the first node, so we must re-point table->buckets[b]
					table -> buckets[b] = current_node->next;
				}

				free(current_node);
				
				table->num_keys--;
				return 1;
				
			}

			previous_node = current_node;
			current_node = current_node->next;
	
		}
		return 0;
		break;

	case 1: //linear probing
		;
		int p1 = 0;
		while(p1 < table -> num_buckets){
			int index = (b + p1) % table -> num_buckets;//bucket we are accessing
			if(table -> buckets[index] && table -> buckets[index] -> value -> SIN == SIN){
				free(table -> buckets[index]);
				table -> num_keys--;//when deleting a key, number of keys decreases
				return 1;
			}
			p1++;
		}
		return 0;
		break;
	
	case 2://quadratic probing
		;
		int p2 = 0;
		while(p2 < table -> num_buckets){
			int index = (b + (INT_HASH) pow(p2, 2) % table -> num_buckets);//bucket we are accessing
			if(table -> buckets[index] && table -> buckets[index] -> value -> SIN == SIN){
				free(table -> buckets[index]);
				table -> num_keys--;
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
	
	in dex 

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

	INT_HASH b = (hash_funcs[table -> mode])(SIN, table -> num_buckets);
	switch (table -> mode)
	{
	case 0: //chaining
		;//need this to declare a new variable in a switch statement
		Node * bucket = table -> buckets[b];
		while (bucket != NULL){
			if(bucket -> value -> SIN == SIN){// check SIN of that bucket
				return bucket -> value;}
			bucket = bucket -> next;
		}
		return NULL;
		break;

	case 1: //linear probing
		;
		int p1 = 0;
		while(p1 < table -> num_buckets){
			int index = (b + p1) % table -> num_buckets;//bucket we are accessing
			if(table -> buckets[index] && table -> buckets[index] -> value -> SIN == SIN){
				return table -> buckets[index] -> value;
			}
			p1++;
		}
		return NULL;
		break;
	
	case 2://quadratic probing
		;
		int p2 = 0;
		while(p2 < table -> num_buckets){
			int index = (b + (INT_HASH) pow(p2, 2) % table -> num_buckets);//bucket we are accessing
			if(table -> buckets[index] && table -> buckets[index] -> value -> SIN == SIN){
				return table -> buckets[index] -> value;
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

		while(bucket != NULL){

			Node* b0 = bucket->next; // temporary variable

			free(bucket);

			bucket = b0;

		}
		
	}
	free(table-> buckets);
	free(table);
}

HashTable *resize_table(HashTable *table){
	/**
	Return a pointer to a new table with size 2^m+1, where 
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
	int m = log2(2*table -> num_buckets);//to change to log base 2 
	
	HashTable* new_table = create_hash_table(m, table -> mode);
	for(INT_HASH b = 0; b < table->num_buckets; b++){ 
		Node * bucket = table->buckets[b];
		while (bucket != NULL){
			if (bucket->value == NULL);
			else update_without_resize(bucket -> value, new_table);
			bucket = bucket->next;
		}
	}
	delete_table(table);
	return new_table;
}
