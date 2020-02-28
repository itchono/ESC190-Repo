#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct stack* create_stack(){
	// Creates a stack dynamically and returns a pointer. Size will be zero and top will be null.

	struct stack *stk = malloc(sizeof(struct stack)); // initialize stack object
	// Pointer type = malloc, which returns a pointer [void, which is cast to stack]

	if (stk == NULL) return NULL; // failsafe

	stk->size = 0;
	stk->top = NULL;

	return stk;
}

void delete_stack(struct stack* s){
	// deletes a stack going from top to bottom.
	struct stack_entry *entry = s->top; // determine active entry to be wiped
	struct stack_entry *next; // next pointer

	while(entry != NULL) {
		next = entry->next; // set next accordingly
		free(entry); // delete entry
		entry = next; // next value
	}
	free(s); // finally, delete the stack
}

double pop(struct stack* s){
	// pops top element from stack

	// I: Failure cases
	if (s == NULL || s->size == 0 || s->top == NULL) {
		// empty or null stack --> return 0
		return 0;
	}

	// II: Otherwise, proceed with output
	float ret = s->top->value;
	struct stack_entry *next = s->top->next;
	// pre-initialization

	free(s->top); // clear entry
	s->top = next; // point to next
	s->size--; // update size


	return ret;
}

int push(struct stack* s, double e){
	// pushes element into stack

	// make the new entry
	struct stack_entry *newEntry = malloc(sizeof(struct stack_entry));

	// O: stack is null or no more memory.
	if (newEntry == NULL || s == NULL) return -1;

	newEntry->value = e; // else, we are OK

	// I: stack is empty vs II: exists other elements
	newEntry->next = (s->size == 0) ? NULL : s->top; // assign next pointer depending on empty/nonempty
	s->top = newEntry; // new element on top
	s->size++; // increment size
	
	return 0;
}
