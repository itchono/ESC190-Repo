#include "lab4.h"
#include <math.h>

INT_HASH trivial_hash(INT_SIN SIN, INT_HASH num_buckets) {
	/**
	   return the hash of SIN scaled to num_buckets
	   
	   Sample IO
	   printf(“%ld”, trivial_hash(10, 8)); 
	   
	   stdout:
	   2
	**/
}


INT_HASH pearson_hash(INT_SIN SIN, INT_HASH num_buckets) {
	/**
	   return the hash of SIN scaled to num_buckets

	   Sample IO
	   printf(“%ld”, pearson_hash(10, 8)) 
	   
	   stdout:
	   7

	**/

}


INT_HASH fibonacci_hash(INT_SIN SIN, INT_HASH num_buckets) {
	/**
	return the hash of SIN scaled to num_buckets

	Sample IO
	printf(“%ld”, fibonacci_hash(10, 8)) 
	printf(“%ld”, fibonacci_hash(999999999, 8)) 
	printf(“%ld”, fibonacci_hash(999999999, W)) 

	stdout:
	1
	0
	69107783
	**/
 
}

