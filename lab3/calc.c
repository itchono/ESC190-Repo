#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"
#include "stack.h"

#define MAX_LENGTH 255

double compute_rpn(char* rpn){
	/*Your code goes here*/

	struct stack *stk = create_stack();

	double total = 0;

	int i = 0; // index of char array

	char buffer[MAX_LENGTH];

	buffer[0] = '\0'; // initialize properly

	while (rpn[i] != '\0') {
		// go until we see '\0' character

		// general algorithm:
		// 1st input will always be numeric --> we must cast to int etc.
		// STOP once we hit a space and prepare for next command


		if (rpn[i] == ' ') {
			// stop command for parsing number

			// if numeric, push
			double num = atof(buffer);
			push(stk, num); // put number to top
			buffer[0] = '\0'; // reset buffer
		}

		else if (rpn[i] >= 48 && rpn[i] <= 57) {
			// check for numeric --> add to buffer for reading a number
			strcat(buffer, (rpn+i)); // add to buffer
		}

		else {
			// operator

			total = (stk->size == 0) ? 0 : pop(stk); // FIX ME

			switch (rpn[i]) {
				case '+':
					// begin operation

					while(stk->size != 0) {
						total += pop(stk);
					}

					push(stk, total); // put into stack
					

					break;
				
				case '-':
					
					while(stk->size != 0) {
						total -= pop(stk);
					}

					push(stk, total);

					break;

			
			}
			i++; // advance to next non-space character since a space will follow any operation
			
		}

		i++;
	}

	return total;

}

char* get_expressions(char* filename){
	// reads file in --> string out
	// WORKS

	int numLines = 0;

	char buffer[MAX_LENGTH]; // buffer

	FILE *f = fopen(filename, "r");

	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		numLines++; // count the number of lines
	}

	char *output = calloc(MAX_LENGTH*numLines, sizeof(char));

	FILE *input_stream = fopen(filename,"r");

	while (fgets(buffer, sizeof(buffer), input_stream) != NULL) {
		strcat(output, buffer); // \n is automatically added
	}
	fclose(input_stream);

	return output; // Note: this must be closed properly
}

void process_expressions(char* expressions, char* filename){
	// puts files out with completed math.

	FILE*output_stream = fopen(filename,"w");

	int i = 0; // position reading the char
	
	char buffer[MAX_LENGTH]; // buffer

	buffer[0] = '\0'; // initialize properly

	while (expressions[i] != '\0') {

		if (expressions[i] == '\n') {
			//printf("INPUT: %s\n", buffer);
			// once we hit a \n, flush buffer and compute rpn
			fprintf(output_stream, "%g\n", compute_rpn(buffer));

			buffer[0] = '\0'; // reset buffer

		}
		else {
			// janky solution to make it stop reading 10000 strings
			char temp = expressions[i+1];
			expressions[i+1] = '\0';

			strcat(buffer, (expressions+i));

			expressions[i+1] = temp;
		}
		i++;
	}

	fclose(output_stream);

	free(expressions); // release memory? // TBD
}
