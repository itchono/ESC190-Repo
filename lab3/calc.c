#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "calc.h"
#include "stack.h"

#define MAX_LENGTH 257 // max is 256 + 1 = 257 for \n

double compute_rpn(char* rpn){
	// main calculator

	struct stack *stk = create_stack();

	int i = 0; // index of char array

	char buffer[MAX_LENGTH]; // string buffer for parsing	

	buffer[0] = '\0'; // initialize properly

	while (rpn[i] != '\0') {
		// go until we see '\0' character denoting end of string

		// general algorithm:
		// 1st input will always be numeric --> we must cast to int etc.
		// STOP once we hit a space and prepare for next command

		if (rpn[i] == ' ') {
			// stop command for parsing number
			push(stk, atof(buffer)); // put number to top
			buffer[0] = '\0'; // reset buffer
		}

		else if ((rpn[i] >= 48 && rpn[i] <= 57) || rpn[i] == 46) {
			// check for numeric --> add to buffer for reading a number
			strcat(buffer, (rpn+i)); // add to buffer
		}

		else {
			// operators

			if (rpn[i] == '+' || rpn[i] == '-' || rpn[i] == '*'  || rpn[i] == '/'  || rpn[i] == '^' || rpn[i] == 'f') {
				// binary
				double o2 = pop(stk);
				double o1 = pop(stk); // pop the operands

				switch (rpn[i]) {
					case '+':
						push(stk, (o1+o2));
						break;
					case '-':
						push(stk, (o1-o2));
						break;
					case '*':
						push(stk, (o1*o2));
						break;
					case '/':
						push(stk, (o1/o2));
						break;
					case '^':
						push(stk, pow(o1, o2));
						break;
					case 'f':
						push(stk, o2);
						push(stk, o1);
						break;
				}
			}

			else if (rpn[i] == 's'  || rpn[i] == 'c' || rpn[i] == 't' || rpn[i] == 'e' || rpn[i] == 'i' || rpn[i] == 'm' || rpn[i] == 'r') {
				double o = pop(stk); // pop the single operand
				
				switch (rpn[i]) {
					case 's':
						push(stk, sin(o));
						break;
					case 'c':
						push(stk, cos(o));
						break;
					case 't':
						push(stk, tan(o));
						break;
					case 'e':
						push(stk, exp(o));
						break;
					case 'i':
						push(stk, 1/o);
						break;
					case 'm':
						push(stk, (-1)*(o));
						break;
					case 'r':
						push(stk, sqrt(o));
						break;
				}
			}
			if (rpn[i+1] != '\0') i++; // advance to next non-space character since a space will follow any operation
			// except in case that we hit end of string
		}
		i++; // parse next character
	}

	double v = pop(stk); // get final result
	// push numeric to stack if there was no space delimiter
	delete_stack(stk); // FREE stack
	return (v!=0) ? v : atof(buffer); // return top value
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

	fclose(f); // CLOSE FILE

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
	//free(expressions); // release memory? actually NO
	// ASSUME THAT TESTER SCRIPT WILL FREE THIS POINTER
}
