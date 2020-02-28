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

	char strBuffer[] = "";

	while (rpn[i] != '\0') {
		// go until we see '\0' character

		// general algorithm:
		// 1st input will always be numeric --> we must cast to int etc.
		// STOP once we hit a space and prepare for next command


		if (rpn[i] == ' ') {
			// stop command

			// if numeric, push
			double num = atof(strBuffer);
			push(stk, num); // put number to top
			strBuffer[0] = '\0'; // reset string
		}

		else if (rpn[i] >= 48 && rpn[i] <= 57) {
			// check for numeric // TBD FIGURE OUT MORE
			strcat(strBuffer, &rpn[i]); // append to buffer
		}

		else if (rpn[i] == '+') {
			// begin operation
			total = 0;
			while(stk->size != 0) {
				total += pop(stk);
			}

			push(stk, total); // put into stack

			i++; // advance to next non-space character
		}
		i++;
	}

	return total;

}

char* get_expressions(char* filename){
	char output[] = "asdf";

	FILE *input_stream=fopen(filename,"r");

	char file_line[MAX_LENGTH];

	while (fgets(file_line, sizeof(file_line), input_stream) != NULL) {
		strcat(output, file_line);
		strcat(output, "\n");
	}
	fclose(input_stream);

	printf("%s", output);
	//TBD

	return output;
}

void process_expressions(char* expressions, char* filename){
	// TBD
}
