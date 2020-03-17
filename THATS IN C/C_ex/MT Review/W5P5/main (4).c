#include <stdio.h>
#include "main.h"

int get_ascii_sum(char* s){
    int sum=0;

    // ALTERNATIVELY, we can advance the pointer!!

    int i = 0;
    while (s[i] != '\0') {
        sum += (int) s[i];
        i++;
    }

    return sum;
}

int main()
{
    char weekday[50];
    int ascii_sum;
    
    /* Input a day of the week e.g. "monday" */
    printf("Enter a day of the week e.g. monday: ");
    scanf(" %s", weekday);
    printf("Your input is: %s\n", weekday);
    ascii_sum = get_ascii_sum(weekday);
    printf("ascii sum: %d\n", ascii_sum);


    return 0;
}