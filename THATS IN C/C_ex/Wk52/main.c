#include <stdio.h>

int main(void){
	char c;
	int ascii;

	printf("Enter ASCII code 0 - 127:\n");
	scanf("%d",&ascii);
	printf("The ascii code is %c\n", ascii);
	
	printf("Enter a character:\n");
	scanf(" %c", &c);
	printf("The character is %d\n", c);

	return 0;
}