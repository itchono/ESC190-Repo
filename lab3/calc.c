#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"
#include "stack.h"

double compute_rpn(char* rpn){
	/*Your code goes here*/

	struct stack *stk = create_stack();

	double total = 0;

	int i = 0; // index of char array

	while (rpn[i] != '\0') {
		// general algorithm:
		// 1st input will always be numeric --> we must cast to int etc.
		// STOP once we hit a space and prepare for next command


		if (rpn[i] == ' ') {
			// stop command
		}

	}

	return total;

}

char* get_expressions(char* filename){
	/*Your code goes here*/
}

void process_expressions(char* expressions, char* filename){
	/*Your code goes here*/
}
