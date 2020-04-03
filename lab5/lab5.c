//include things here
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


/*

Fill in the following functions - follow the document for proper declaration and definition
1. encodeNuc
2. decodeBin
3. findProtein
4. proteinReport
5. isolateProtein
6. genMutant

Implement for 1% bonus!
7. checkMutant

*/

// 1
void encodeNuc(char *filename) {
    // WORKS

    char outName[256] = {'b', '\0'}; // add to string
    
    strcat(outName, filename);

    FILE* fin = fopen(filename, "r");
    FILE* fout = fopen(outName, "w");

    char seq = 0;

    while(fscanf(fin, "%c", &seq) != EOF) {
        switch (seq) {
            case 'A':
            fprintf(fout, "00");
            break;
            case 'C':
            fprintf(fout, "01");
            break;
            case 'G':
            fprintf(fout, "10");
            break;
            case 'T':
            fprintf(fout, "11");
            break;
        }
    }


    fclose(fout);
    fclose(fin);
}

// 2
void decodeBin(char *filename) {
    // WORKS

    char outName[256] = {'n', '\0'};
    strcat(outName, filename);

    FILE* fin = fopen(filename, "r");
    FILE* fout = fopen(outName, "w");

    char seq1 = 0;
    char seq2 = 0;
    char read[3];

    while(fscanf(fin, "%2c", &read) != EOF) {
        seq1 = read[0]-48;
        seq2 = read[1]-48;
        if (!seq1 && !seq2) fprintf(fout, "A");
        else if (!seq1 && seq2) fprintf(fout, "C");
        else if (seq1 && !seq2) fprintf(fout, "G");
        else if (seq1 && seq2) fprintf(fout, "T");
    }
    fclose(fout);
    fclose(fin);
}

// 3
void findProtein(char *filename, int checkPos, int proteinInfo[]) {
    // IPR

    if (0){

    }

    else {
        proteinInfo = {0, 0};
    }
}


int main() {

    encodeNuc("partialSLV.txt");
    decodeBin("bpartialSLV.txt");

    return 0;
}


