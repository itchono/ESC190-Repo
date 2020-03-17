#include <stdio.h>

int main(void){
	char c;
	int ascii;

	printf("Enter ASCII code 0 - 127:\n");
	scanf("%d", &ascii);
	printf("The ascii code %d is the character %c\n", ascii, ascii);
	
	printf("Enter a character:\n");
	scanf(" %c", &c); // sometimes we need an interruptor character, when scanning char
	printf("The character is %c and has ASCII code %d\n", c, c);

	return 0;
}