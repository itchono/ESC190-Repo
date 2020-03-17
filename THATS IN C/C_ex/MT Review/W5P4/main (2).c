#include <stdio.h>

int main()
{
    char weekday[50];
    int ascii_sum = 0;
    
    /* Input a day of the week e.g. "monday" */
    printf("Enter a day of the week e.g. monday: ");
    scanf(" %s", weekday);
    printf("Your input is: %s\n", weekday);

    int i = 0;
    while (weekday[i] != '\0') {
        ascii_sum += (int) weekday[i];
        i++;
    }
    
    printf("ascii sum: %d\n", ascii_sum);

    // not strict, since addition is associative
    // so Saturdya works

    switch (ascii_sum) {
        case 877:
            printf("It's a weekend.\n");
            break;
        case 660:
            printf("It's a weekend.\n");
            break;
        default:
            printf("It's a weekday.\n")
            break;
    }

    return 0;
}