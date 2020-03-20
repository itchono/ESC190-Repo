#include "lab4.h"
#include <math.h>
#include <time.h>

INT_HASH trivial_hash(INT_SIN SIN, INT_HASH num_buckets) {
	/**
	   return the hash of SIN scaled to num_buckets
	   
	   Sample IO
	   printf(“%ld”, trivial_hash(10, 8)); 
	   
	   stdout:
	   2
	**/
	return SIN % num_buckets;
}


INT_HASH pearson_hash(INT_SIN SIN, INT_HASH num_buckets) {
	/**
	   return the hash of SIN scaled to num_buckets

	   Sample IO
	   printf(“%ld”, pearson_hash(10, 8)) 
	   
	   stdout:
	   7

	**/
	INT_HASH h = 0; // initialize

	while(SIN >= 1) {
		// do for all terms

		char leastsig = SIN % 10 + 48; // stored as an ASCII character of the actual DIGIT character

		h = PEARSON_LOOKUP[h ^ leastsig];

		SIN /= 10; // to next digits
	}

	return trivial_hash(h, num_buckets); // account for overflow
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
	69107783 // WHAT
	**/

	unsigned long int a = round((double)W/PHI); // this works
	return ((a * SIN % W)/((double)W/num_buckets)); // apply wizardry formula
}

