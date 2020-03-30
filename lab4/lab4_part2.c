#include "lab4.h"
#include <math.h>
#define NUM_HASH_FUNCS 3

HashTable *create_hash_table(int m, int mode){
	// blank initializer
	// WORKS

    hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	HashTable* ht = malloc(sizeof(HashTable));

	ht->num_buckets = (int)pow(2,m);
	ht->mode = mode;
	ht->num_keys = 0;
	ht->buckets = calloc(ht->num_buckets, sizeof(Node*)); // fully initialized

	return ht;
}

void update_without_resize(PersonalData * data, HashTable *table) {
	// insert keys or update keys
	
	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	INT_HASH k;
	
	if(table->mode < 3) {
		k = (hash_funcs[table->mode])(data->SIN, table->num_buckets); // key to map to, based on mode
	}

	if (lookup_key(data->SIN, table) == NULL) {
		// create new entry

		INT_HASH i = 0;
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
			;
			// linear probe
			while (table->buckets[(k+i)%table->num_buckets] && i < table->num_buckets) {
				i++;
			}
			// now we have a bucket
			if (i < table->num_buckets) {
				table->buckets[(k+i)%table->num_buckets] = malloc(sizeof(Node));
				table->buckets[(k+i)%table->num_buckets]->next = NULL;
				table->buckets[(k+i)%table->num_buckets]->value = data; // new node
				table->num_keys++;
			} // else discard
			break;

		case 2:
			;
			while(table->buckets[(k+(int)pow(i,2))%table->num_buckets] && i < table->num_buckets) {
				i++;
			}
			// now we have a bucket
			if (i < table->num_buckets) {
				table->buckets[(k+(int)pow(i,2))%table->num_buckets] = malloc(sizeof(Node));
				table->buckets[(k+(int)pow(i,2))%table->num_buckets]->next = NULL;
				table->buckets[(k+(int)pow(i,2))%table->num_buckets]->value = data; // new node
				table->num_keys++;
			}
			break;

		case 3:
			// cuckoo insert
			;
			int stop = 0;

			while (i<3 && !stop) {
				k = (hash_funcs[i])(data->SIN, table->num_buckets);

				if (!table->buckets[k]) stop = 1;
				else i++;
			}

			if (i < 3 && stop) {
				// if we're able to find a spot
				table->buckets[k] = malloc(sizeof(Node));
				table->buckets[k]->next = NULL;
				table->buckets[k]->value = data; // new node
				table->num_keys++;
			}
			else {
				// else, take drastic measures

				PersonalData* kstar = table->buckets[k]->value;

				free(table->buckets[k]); // yeet current slot and fill it

				table->buckets[k] = malloc(sizeof(Node)); // insert ogkey
				table->buckets[k]->next = NULL;
				table->buckets[k]->value = data; // new node
				table->num_keys++;

				i = 0;
				stop = 0;

				while (i<3 && !stop) {
					k = (hash_funcs[i])(kstar->SIN, table->num_buckets);

					if (!table->buckets[k]) stop = 1;
					else i++;
				}

				if (i < 3 && stop) {
					// if we're able to find a spot
					table->buckets[k] = malloc(sizeof(Node));
					table->buckets[k]->next = NULL;
					table->buckets[k]->value = kstar; // new node
				}
				else {
					table->num_keys--;
				}

			}
			break;
		}

	}
	else {
		// update key in table
		INT_HASH i = 0;
		switch (table->mode)
		{
		case 0:
			;
			// linked list push
			Node* currNode = table->buckets[k];
			while (currNode) {
				if(currNode->value->SIN == data->SIN) {
					currNode->value = data;
				}
				currNode = currNode->next;
			}
			
			break;

		case 1:
			// linear probe
			;
			while (table->buckets[(k+i)%table->num_buckets] && i < table->num_buckets) {
				if (table->buckets[(k+i)%table->num_buckets]->value->SIN == data->SIN) {
					table->buckets[(k+i)%table->num_buckets]->value = data;
				}
				i++;
			}
			break;

		case 2:
			;
			while (table->buckets[(k+(int)pow(i,2))%table->num_buckets] && i < table->num_buckets) {
				if (table->buckets[(k+(int)pow(i,2))%table->num_buckets]->value->SIN == data->SIN) {
					table->buckets[(k+(int)pow(i,2))%table->num_buckets]->value = data;
				}
				i++;
			}
			break;

		case 3:
			// cuckoo
			// linear probe; in same manner
			;
			while (table->buckets[i] && i < table->num_buckets) {
				if (table->buckets[i]->value->SIN == data->SIN) {
					table->buckets[i]->value = data;
				}
				i++;
			}
			break;
		}
		

	}

}

void update_key(PersonalData * data, HashTable **table){
	// combine functions
	// WORKS
	if (((*table)->num_keys+1.0) / (*table)->num_buckets > MAX_LOAD_FACTOR && lookup_key(data->SIN, *table) == NULL) *table = resize_table(*table); // if load factor is unacceptable and yet we are adding a new key
	update_without_resize(data, *table);
}

int delete_key(INT_SIN SIN, HashTable *table){
	// WORKS

	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	// first confirm the key exists

	if (!lookup_key(SIN, table)) return 0;

	INT_HASH k;
	
	if(table->mode < 3) {
		k = (hash_funcs[table->mode])(SIN, table->num_buckets); // key to map to, based on mode
	} // key to map to, based on mode

	INT_HASH i = 0;
	switch (table->mode)
	{
	case 0:
		// linked list push
		;
		Node* currNode = table->buckets[k];
		Node* prev = NULL;
		while (currNode) {
			// LL mode
			if(currNode->value->SIN == SIN) {
				if(prev) prev->next = currNode->next;
				else table->buckets[k] = currNode->next;
				free(currNode);
				table->num_keys--;
				return 1;
			}
			prev = currNode;
			currNode = currNode->next;
		}
		return 0;
		break;

	case 1:
		// linear probe
		;
		while (table->buckets[(k+i)%table->num_buckets] && i < table->num_buckets) {
			if (table->buckets[(k+i)%table->num_buckets]->value->SIN == SIN) {
				free(table->buckets[(k+i)%table->num_buckets]);
				table->buckets[(k+i)%table->num_buckets] = NULL;
				table->num_keys--;
				return 1;
			}
			i++;
		}
		return 0;
		break;

	case 2:
		;

		while(table->buckets[(k+(int)pow(i,2))%table->num_buckets] && i < table->num_buckets) {
			if (table->buckets[(k+(int)pow(i,2))%table->num_buckets]->value->SIN == SIN) {
				free(table->buckets[(k+(int)pow(i,2))%table->num_buckets]);
				table->buckets[(k+(int)pow(i,2))%table->num_buckets] = NULL;
				return 1;
			}
			i++;
		}
		return 0;
		break;

	case 3:
		// linear probe
		;
		for (INT_HASH b = 0; b < table->num_buckets; b++){ 
			if(table->buckets[b] && table->buckets[b]->value->SIN == SIN){
				free(table->buckets[b]);
				table->buckets[b] = NULL;
				table->num_keys--;
				return 1;
			}
		}
		return 0;
		break;

	}
}

PersonalData* lookup_key(INT_SIN SIN, HashTable *table){
	// WORKS

	hash_funcs[0] = trivial_hash;
    hash_funcs[1] = pearson_hash;
    hash_funcs[2] = fibonacci_hash;

	INT_HASH k;
	
	if(table->mode < 3) {
		k = (hash_funcs[table->mode])(SIN, table->num_buckets); // key to map to, based on mode
	} // key to map to, based on mode
	
	INT_HASH i = 0;
	switch (table->mode)
	{
	case 0:
		;
		Node* currNode = table->buckets[k];
		while (currNode) {
			if(currNode->value->SIN == SIN) {
				return currNode->value;
			}
			currNode = currNode->next;
		}
		
		return NULL;
		break;

	case 1:
		
		;
		// linear probe

		while (i < table->num_buckets) {
			if (table->buckets[(k+i)%table->num_buckets] && table->buckets[(k+i)%table->num_buckets]->value->SIN == SIN) {
				return table->buckets[(k+i)%table->num_buckets]->value;
			}
			i++;
		}
		return NULL;
		break;

	case 2:
		;

		while(i < table->num_buckets) {
			if (table->buckets[(k+(int)pow(i,2))%table->num_buckets] && table->buckets[(k+(int)pow(i,2))%table->num_buckets]->value->SIN == SIN) {
				return table->buckets[(k+(int)pow(i,2))%table->num_buckets]->value;
			}
			i++;
		}
		return NULL;
		break;

	case 3:
		// cuckoo
		// use linear comb lookup
		for (INT_HASH b = 0; b < table->num_buckets; b++){ 
			if(table->buckets[b] && table->buckets[b]->value->SIN == SIN){
				return table->buckets[b]->value;
			}
		}
		return NULL;
		break;
	}
}

void delete_table(HashTable *table){
	// WORKS

	if (table->mode == 0) {
		// go to linked lists and PURGE
		for (INT_HASH x = 0; x < table->num_buckets; x++) {
			if (table->buckets[x]) {
				Node* currNode = table->buckets[x];
				while (currNode) {
					Node* n = currNode->next;
					free(currNode);
					currNode = n;
				}
			}
		}

	}
	else if (table->mode == 1 || table->mode == 2) {
		// DO NOT FREE THE VALUE POINTERS
		// search through every bucket and PURGE

		for (INT_HASH x = 0; x < table->num_buckets; x++) {
			if (table->buckets[x]) {
		
				free(table->buckets[x]); // get rid of the thing stored there
			}
			
		}
	}
	free(table->buckets); // delete the array of pointers to nodes
	free(table);



}

HashTable *resize_table(HashTable *table){
	// WORKS

	HashTable* t2 = create_hash_table(log2(table->num_buckets)+1, table->mode);

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
