#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINES 10 // input file has max of 10 lines
#define LENGTH 100 // each line has max 100 char
#define TOTAL 1000 // max number of chars

char* func1(char* fn){
    // return a char* that contains the contents of fn
    FILE* f = fopen(fn, "r");

    char *contents=malloc(TOTAL*sizeof(char));
    contents[0] = '\0'; // REMEMBER to set to zero to start


    // complete the function
    char buffer[LENGTH];

    while(fgets(buffer, LENGTH, f) != NULL){
        strcat(contents, buffer);
    }

    fclose(f);

    return contents;
}

void func2(char* fn, char* buf){
    // copies content of fn to pre-buffered char[] buf

    FILE* f = fopen(fn, "r");

    buf[0] = '\0';

    // complete the function
    char buffer[LENGTH];

    while(fgets(buffer, LENGTH, f) != NULL){
        strcat(buf, buffer); // append to existing buffer
    }

    fclose(f);
}

char** func3(char* fn){
    // return a pointer to array of char* last names

    char** ret = calloc(LINES, sizeof(char*));

    FILE* f = fopen(fn, "r");

    // complete the function
    char buffer[LENGTH];

    int lineNumber = 0;

    while(fgets(buffer, LENGTH, f) != NULL){
        // sift buffer until we have our ideal place

        char* starter = buffer;
        char* replaceEnd = buffer+1;

        while(*replaceEnd != '\n' && *replaceEnd != '\0') {
            
            replaceEnd++;
        }
        *replaceEnd = '\0';

        while(*starter != ' ') {
            starter++;
        }
        starter++;

        ret[lineNumber] = malloc(LENGTH * sizeof(char));
        ret[lineNumber][0] = '\0';

        strcat(ret[lineNumber], starter);

        lineNumber ++;

    }
    fclose(f);

    // complete the function
    return ret;
}

char** func4(char* fn){
    // return a pointer to array of char* last names

    char** ret = calloc(LINES, sizeof(char*));

    FILE* f = fopen(fn, "r");

    // complete the function
    char buffer[LENGTH];

    int lineNumber = 0;

    while(fscanf(f, "%*s %s", buffer) != EOF){
        // %*s means discard a string
        // learn how fscanf works --> does NOT include a \n

        // sift buffer until we have our ideal place
        ret[lineNumber] = malloc(LENGTH * sizeof(char));
        ret[lineNumber][0] = '\0';

        strcat(ret[lineNumber], buffer);

        lineNumber ++;

    }
    fclose(f);

    // complete the function
    return ret;
}

int main()
{
    //Tester, no need to touch this.
    
    char* contents1 = func1("names.txt");
    printf("\nfunction1:\n");
    printf("%s\n", contents1);
    free(contents1);

    printf("\nfunction2:\n");
    char* contents2 = malloc(TOTAL*sizeof(char));
    func2("names.txt", contents2);
    printf("%s\n", contents2);
    free(contents2);

    printf("\nfunction3:\n");
    char** contents3 = func4("names.txt");
    for(int i=0; i<LINES; i++)
        if(contents3[i])
            printf("%s\n", contents3[i]);
    free(contents3);
    
    return 0;
}

