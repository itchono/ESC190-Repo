#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#include "stack.h"

void printStack(struct stack* s) {
	// prints a stack from top to bottom.

	struct stack_entry *entry = s->top; // determine active entry to be wiped
	struct stack_entry *next; // next pointer

	printf("Stack Located at %p; size %d:\n", s, s->size);

	while(entry != NULL) {
		next = entry->next; // set next accordingly
		printf("%g\n", entry->value);
		entry = next; // next value
	}
}

int main(int argc, char* argv[]){
	/*
	if(argc!=3){
		printf("Missing input and output file names. Usage:\n./rpn input output\n");
	}else{
		char* expr = get_expressions(argv[1]);
		process_expressions(expr, argv[2]);
		free(expr);
	}
	
	return 0;
	*/
	/*
	// stack testing
	struct stack *stk = create_stack();

	printStack(stk); // should be nothing

	push(stk, 2);
	push(stk, 4.01);
	push(stk, 6);

	printStack(stk); // should be 6, 4.01, 2

	printf("Pop!: %g\n", pop(stk));
	printf("Pop!: %g\n", pop(stk));
	printf("Pop!: %g\n", pop(stk));
	printf("Pop!: %g\n", pop(stk)); // Should be zero
	printStack(stk);
	*/
	
	printf("RPN RESULT: %g\n", compute_rpn("2 2 * i 1 + .25 + 1.5 *"));

	char* exprs = get_expressions("sample_in.txt");

	process_expressions(exprs, "testout.txt");


	free(exprs);


	return 0;
}


