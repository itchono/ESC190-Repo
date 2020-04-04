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

int numLines(char* fn) {
    FILE* f = fopen(fn, "r");

    long int linecount = 0;

    char buffer[11];

    while(fgets(buffer, 11, f) != NULL) {
        linecount++;
    }

    fclose(f);
    return linecount;
}

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
    // READY TO TEST

    FILE* fin = fopen(filename, "r");
    FILE* codonF = fopen("codons.txt", "r");

    int n = numLines("codons.txt");

    char** seqs = calloc(n, sizeof(char*));
    char* proteins = calloc(n, sizeof(char));

    int x = -1;

    do {
        x++;
        seqs[x] = calloc(7, sizeof(char)); // 6 bins + thingy

    } while(fscanf(fin, "%6c,%c", seqs[x], &proteins[x]) != EOF);
    // arrays ready to use


    char read[7]; // read buffer

    for (int i = 0; i < (checkPos-1); i++) {
        fscanf(fin, "%2c", read);
    }
    // skip this many positions

    // ** ASSUMING NUCLEOPOSITIONS START AT 1 TODO

    int nucleoStart = 1 + (checkPos-1);
    int aminoLength = 0;

    while(fscanf(fin, "%6c", read) != EOF) {

        for (int i = 0; i < n; i++) {
            if (!strcmp(read, seqs[i]) && proteins[i] == 'M') {
                proteinInfo[0] = nucleoStart;
                aminoLength++;
            }
            else if(!strcmp(read, seqs[i])){
                aminoLength++;
                continue;
            }
            else if(!strcmp(read, seqs[i]) && proteins[i] == '*'){
                aminoLength++;
                proteinInfo[1] = aminoLength;
                break;
            }
        }
        nucleoStart += 3; // keep moving
    }

    for (int i = 0; i < n; i++) {
        free(seqs[i]);
    }

    if (!aminoLength) proteinInfo = {0, 0}; // fallback

    for (int i = 0; i < n; i++) {
        free(seqs[i]);
    }
    free(proteins);
    free(seqs)

    fclose(fin);
    fclose(codonF);
}


int main() {

    encodeNuc("partialSLV.txt");
    decodeBin("bpartialSLV.txt");

    return 0;
}


