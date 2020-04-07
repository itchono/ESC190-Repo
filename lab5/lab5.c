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
    // At least partial working

    FILE* fin = fopen(filename, "r");
    FILE* codonF = fopen("codons.txt", "r");

    int n = numLines("codons.txt");

    char** seqs = calloc(n, sizeof(char*));
    char* proteins = calloc(n, sizeof(char));

    int x = -1;

    do {
        x++;
        seqs[x] = calloc(7, sizeof(char)); // 6 bins + terminator
        seqs[x][6] = '\0'; // string array

    } while(fscanf(codonF, "%6c,%c\n", seqs[x], &(proteins[x])) != EOF);
    // arrays ready to use

    char read[7]; // read buffer

    for (int i = 0; i < (checkPos-1) && fscanf(fin, "%2c", read) != EOF; i++);
    // skip this many positions OK

    // ** ASSUMING NUCLEOPOSITIONS START AT 1 I think OK

    int nucleoStart = 1 + (checkPos-1);
    int aminoLength = 0;
    int start = 0;
    int end = 0;

    while(fscanf(fin, "%6c", read) != EOF && !end) {
        read[6] = '\0';

        for (int i = 0; i < n; i++) {

            if (!strcmp(read, seqs[i]) && proteins[i] == 'M') {
                proteinInfo[0] = nucleoStart;
                start = 1;
                aminoLength++;
            }
            else if(!strcmp(read, seqs[i]) && proteins[i] == '*' && start && !end){
                aminoLength++;
                end = 1;
                proteinInfo[1] = aminoLength;
                break;
            }
            else if(!strcmp(read, seqs[i]) && start){
                aminoLength++;
                continue;
            }
            
        }
        nucleoStart += 3; // keep moving
    }

    for (int i = 0; i < n; i++) {
        free(seqs[i]);
    }

    if (!aminoLength || !end) {
        // also, catch loose ends
        proteinInfo[0] = 0; // fallback
        proteinInfo[1] = 0;
    }

    free(proteins);
    free(seqs);

    fclose(fin);
    fclose(codonF);
}

// 4
void proteinReport(char* filename) {
    // FIX
    char outName[256] = {'r', '\0'};
    strcat(outName, filename);

    FILE* fin = fopen(filename, "r");
    FILE* fout = fopen(outName, "w");

    // determine active reading frame
    int s1[2], s2[2], s3[2];
    int p1 = 1, p2 = 2, p3 = 3;

    findProtein(filename, p1, s1);
    findProtein(filename, p2, s2);
    findProtein(filename, p3, s3);

    // Take the minmum of all three

    int s[2];

    if (s1[0] && (s1[0] <= s2[0] || !s2[0]) && (s1[0] <= s3[0] || !s3[0])) {s[0] = s1[0]; s[1] = s1[1];}
    else if(s2[0] && (s2[0] <= s1[0] || !s1[0]) && (s2[0] <= s3[0] || !s3[0])) {s[0] = s2[0]; s[1] = s2[1];}
    else if (s3[0] && (s3[0] <= s1[0] || !s1[0]) && (s3[0] <= s2[0] || !s2[0])) {s[0] = s3[0]; s[1] = s3[1];}


    if (!s[0]) {
        
        fprintf(fout, "0, 0\n");
    }
    else {
        while(s[0]) {

            fprintf(fout, "%d,%d\n", s[0], s[1]);

            p1 = s[0] + 3*s[1] + 1;
            p2 = s[0] + 3*s[1] + 2;
            p3 = s[0] + 3*s[1] + 3;

            findProtein(filename, p1, s1);
            findProtein(filename, p2, s2);
            findProtein(filename, p3, s3);

            // Take the minmum of all three
            if (s1[0] && (s1[0] <= s2[0] || !s2[0]) && (s1[0] <= s3[0] || !s3[0])) {s[0] = s1[0]; s[1] = s1[1];}
            else if(s2[0] && (s2[0] <= s1[0] || !s1[0]) && (s2[0] <= s3[0] || !s3[0])) {s[0] = s2[0]; s[1] = s2[1];}
            else if (s3[0] && (s3[0] <= s1[0] || !s1[0]) && (s3[0] <= s2[0] || !s2[0])) {s[0] = s3[0]; s[1] = s3[1];}
            else {s[0] = 0;s[1] = 0;}
        }
    }
    fclose(fin);
    fclose(fout);
}

// 5
void isolateProtein(char *filename, int proteinInfo[]) {
    // WORKS
    char outName[256] = {'p', '\0'};
    strcat(outName, filename);
    FILE* fout = fopen(outName, "w");

    if (proteinInfo[0] == 0 && proteinInfo[1] == 0) {
        ; // nothing
    }
    else {
        // READY TO TEST
        // At least partial working

        FILE* fin = fopen(filename, "r");
        FILE* codonF = fopen("codons.txt", "r");

        int n = numLines("codons.txt");

        char** seqs = calloc(n, sizeof(char*));
        char* proteins = calloc(n, sizeof(char));

        int x = -1;

        do {
            x++;
            seqs[x] = calloc(7, sizeof(char)); // 6 bins + terminator
            seqs[x][6] = '\0'; // string array

        } while(fscanf(codonF, "%6c,%c\n", seqs[x], &(proteins[x])) != EOF);
        // arrays ready to use

        char read[7]; // read buffer

        for (int i = 0; i < (proteinInfo[0]-1) && fscanf(fin, "%2c", read) != EOF; i++);
        // skip this many positions OK

        // ** ASSUMING NUCLEOPOSITIONS START AT 1 I think OK

        int write = 0;

        while(fscanf(fin, "%6c", read) != EOF && write < proteinInfo[1]) {
            read[6] = '\0';

            for (int i = 0; i < n; i++) {

               if(!strcmp(read, seqs[i])){
                    fprintf(fout, "%c", proteins[i]);
                    write++;
                    continue;
                }
                
            }
        }

        for (int i = 0; i < n; i++) {
            free(seqs[i]);
        }

        free(proteins);
        free(seqs);

        fclose(fin);
        fclose(codonF);
    }
    fclose(fout);
}

// 6
int genMutant(char *filename, int mutation[]) {
    // WORKS
    char outName[256] = {'m', '\0'};
    strcat(outName, filename);

    FILE* fin = fopen(filename, "r");
    FILE* fout = fopen(outName, "w");

    char read[7]; // read buffer
    
    int failure = 0;

    int pos = 1;

    while(fscanf(fin, "%2c", read) != EOF) {
        // if expected nucleobase is not there, we have a failure condition
        if (pos == mutation[0]) {
            // time to apply the mutation

            if (mutation[1] == 0) {
                if ((mutation[2] == 0 && (read[0] != '0' || read[1] != '0')) ||
                (mutation[2] == 1 && (read[0] != '0' || read[1] != '1')) ||
                (mutation[2] == 2 && (read[0] != '1' || read[1] != '0')) ||
                (mutation[2] == 3 && (read[0] != '1' || read[1] != '1'))) {
                    failure = 1;
                    break;
                }
                else {
                    fscanf(fin, "%2c", read); // push next position
                }
            }
            else if (mutation[1] == 2) {
                fscanf(fin, "%2c", read); // push next position
            }

            if (mutation[1] == 1 || mutation[1] == 2) {
                // insert
                switch (mutation[2])
                {
                case 0:
                    fprintf(fout, "00");
                    break;
                
                case 1:
                    fprintf(fout, "01");
                    break;

                case 2:
                    fprintf(fout, "10");
                    break;
                case 3:
                    fprintf(fout, "11");
                    break;
                }
            }
        }

        fprintf(fout, "%c%c", read[0], read[1]);

        pos++;
    }


    fclose(fin);
    fclose(fout);


    if (failure) {
        fin = fopen(filename, "r");
        fout = fopen(outName, "w");

        char read2;
        while(fscanf(fin, "%c", &read2) != EOF) {
            fprintf(fout, "%c", read2);
        }

        fclose(fin);
        fclose(fout);
    }

    return failure;
}

// 7 BONUS
int checkMutant(char *oriFilename, char *mutFilename) {
    // IMPLEMENT
    return 0;
}

