#include <stdio.h>

int main(void){
	float money;

	printf("How much money do you have in your pocket?\n");
	scanf("%f", &money);

	if (money >= 1000) {
		money -= 1000;
		printf("You can buy a road bike!\n");
	}

	if (money >= 200) {
		money -= 200;
		printf("You can buy a plane ticket!\n");
	}

	if (money >= 100) {
		money -= 100;
		printf("You can buy a second hand bike!\n");
	}

	if (money >= 50) {
		money -= 50;
		printf("You can buy a vacuum cleaner!\n");
	}

	if (money >= 20) {
		money -= 20;
		printf("You can buy a thrift store jacket!\n");
	}

	if (money >= 5) {
		money -= 5;
		printf("You can buy a subway!\n");
	}

	if (money >= 2) {
		money -= 2;
		printf("You can buy a  cup of coffee!\n");
	}

	if (money >= 0.1) {
		money -= 0.1;
		printf("You can buy a paperclip!\n");
	}
	

	printf("You have $%.2f dollars left.\n", money);
	return 0;
}