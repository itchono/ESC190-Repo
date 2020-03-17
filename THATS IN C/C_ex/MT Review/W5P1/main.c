#include <stdio.h>

int main(void){
	int num;
	float total_cost;
	char item_name[256];


	printf("What did you buy?\n");
	scanf("%s", item_name);
	
	printf("How many did you buy?\n");
	scanf("%d", &num); // scanf puts to a pointer

	printf("How much was the total?\n");
	scanf("%f", &total_cost);

	printf("I bought %d %s(s) for $%g each!", num, item_name, total_cost/num);

	printf("%d", (1 || 0 && 0)); // && evaluates before || --> returns 1 || 1 = 1

	printf("%d", ((1 || 0) && 0)); // but we can force using brackets --> return 0

	return 0;
}