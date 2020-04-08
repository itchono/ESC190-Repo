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
    // helper function, from lab3
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

    char outName[1024] = {'b', '\0'}; // add to string
    strcat(outName, filename);
    FILE* fin = fopen(filename, "r");
    FILE* fout = fopen(outName, "w");

    char seq = 0;

    while(fscanf(fin, "%c", &seq) != EOF) {
        switch (seq) {
            case 'A': fprintf(fout, "00"); break;
            case 'C': fprintf(fout, "01"); break;
            case 'G': fprintf(fout, "10"); break;
            case 'T': fprintf(fout, "11"); break;
        }
    }
    fclose(fout);
    fclose(fin);
}

// 2
void decodeBin(char *filename) {
    // WORKS
    char outName[1024] = {'n', '\0'};
    strcat(outName, filename);
    FILE* fin = fopen(filename, "r");
    FILE* fout = fopen(outName, "w");
    char seq1 = 0;
    char seq2 = 0;
    char read[3]; // reading the 2 binary bits
    while(fscanf(fin, "%2c", &read) != EOF) {
        seq1 = read[0]-48;
        seq2 = read[1]-48;
        // case by case
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
    // WORKS
    FILE* fin = fopen(filename, "r");
    FILE* codonF = fopen("codons.txt", "r");

    int n = numLines("codons.txt");

    char seqs[1024][7]; // binary sequences
    char proteins[1024]; // corresponding proteins

    int x = -1;

    do {
        x++;
        seqs[x][6] = '\0'; // string array

    } while(fscanf(codonF, "%6c,%c\n", seqs[x], &(proteins[x])) != EOF);
    // arrays ready to use

    char read[7]; // read buffer

    for (int i = 0; i < (checkPos-1) && fscanf(fin, "%2c", read) != EOF; i++);
    // skip this many positions OK

    int nucleoStart = 1 + (checkPos-1);
    int aminoLength = 0;

    // Flags to indicate whether we have started and/or ended
    int start = 0;
    int end = 0;

    while(fscanf(fin, "%6c", read) != EOF && !end) {
        read[6] = '\0';

        for (int i = 0; i < n; i++) {

            if (!strcmp(read, seqs[i]) && proteins[i] == 'M' && !start) {
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
        nucleoStart += 3; // keep moving if we haven't found a valid start protein
    }

    if (!aminoLength || !end) {
        // if we have an invalid protein
        proteinInfo[0] = 0; // fallback
        proteinInfo[1] = 0;
    }
    fclose(fin);
    fclose(codonF);
}

// 4
void proteinReport(char* filename) {
    char outName[1024] = {'r', '\0'};
    strcat(outName, filename);

    FILE* fin = fopen(filename, "r");
    FILE* fout = fopen(outName, "w");

    // determine active reading frame
    int s1[2], s2[2], s3[2];
    int p1 = 1, p2 = 2, p3 = 3;

    findProtein(filename, p1, s1);
    findProtein(filename, p2, s2);
    findProtein(filename, p3, s3);

    // Take the minmum of all three reading frames
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

            // set initial positions for the next reading frames based off of the end of the previous protein
            p1 = s[0] + 3*s[1] + 1;
            p2 = s[0] + 3*s[1] + 2;
            p3 = s[0] + 3*s[1] + 3;

            findProtein(filename, p1, s1);
            findProtein(filename, p2, s2);
            findProtein(filename, p3, s3);

            // Take the minmum of all three reading frames, again
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
    char outName[1024] = {'p', '\0'};
    strcat(outName, filename);
    FILE* fout = fopen(outName, "w");

    if (proteinInfo[0] == 0 && proteinInfo[1] == 0) {
        ; // nothing
    }
    else {
        FILE* fin = fopen(filename, "r");
        FILE* codonF = fopen("codons.txt", "r");

        int n = numLines("codons.txt");

        char seqs[1024][7]; // binary sequences
    char proteins[1024]; // corresponding proteins

        int x = -1;

        do {
            x++;
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
                    write++; // next state
                    continue;
                }
                
            }
        }

        fclose(fin);
        fclose(codonF);
    }
    fclose(fout);
}

// 6
int genMutant(char *filename, int mutation[]) {
    // WORKS
    char outName[1024] = {'m', '\0'};
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

void isolateProtein2(char *filename, int proteinInfo[]) {
    // WORKS
    char outName[1024] = {'i', '\0'};
    strcat(outName, filename);
    FILE* fout = fopen(outName, "w");

    if (proteinInfo[0] == 0 && proteinInfo[1] == 0) {
        ; // nothing
    }
    else {
        FILE* fin = fopen(filename, "r");
        FILE* codonF = fopen("codons.txt", "r");

        int n = numLines("codons.txt");

        char seqs[1024][7]; // binary sequences
        char proteins[1024]; // corresponding proteins

        int x = -1;

        do {
            x++;
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
                    fprintf(fout, "%s", seqs[i]);
                    write++; // next state
                    continue;
                }
                
            }
        }
        fclose(fin);
        fclose(codonF);
    }
    fclose(fout);
}

// 7 BONUS
int checkMutant(char *oriFilename, char *mutFilename) {
    char outName[1024] = {'c', '\0'};
    strcat(outName, mutFilename);

    FILE* fOG = fopen(oriFilename, "r");
    FILE* fMUT= fopen(mutFilename, "r");
    FILE* fout = fopen(outName, "w");

    // only take the first proteins identified

    // stage 1: find diffs

    // determine active reading frame
    int s1[2], s2[2], s3[2];

    findProtein(oriFilename, 1, s1);
    findProtein(oriFilename, 2, s2);
    findProtein(oriFilename, 3, s3);

    // Take the minmum of all three reading frames
    int sA[2]; // sequence A: original
    if (s1[0] && (s1[0] <= s2[0] || !s2[0]) && (s1[0] <= s3[0] || !s3[0])) {sA[0] = s1[0]; sA[1] = s1[1];}
    else if(s2[0] && (s2[0] <= s1[0] || !s1[0]) && (s2[0] <= s3[0] || !s3[0])) {sA[0] = s2[0]; sA[1] = s2[1];}
    else if (s3[0] && (s3[0] <= s1[0] || !s1[0]) && (s3[0] <= s2[0] || !s2[0])) {sA[0] = s3[0]; sA[1] = s3[1];}

    // sA is now our protein of interest A

    findProtein(mutFilename, 1, s1);
    findProtein(mutFilename, 2, s2);
    findProtein(mutFilename, 3, s3);

    // Take the minmum of all three reading frames
    int sB[2]; // sequence B: mutation
    if (s1[0] && (s1[0] <= s2[0] || !s2[0]) && (s1[0] <= s3[0] || !s3[0])) {sB[0] = s1[0]; sB[1] = s1[1];}
    else if(s2[0] && (s2[0] <= s1[0] || !s1[0]) && (s2[0] <= s3[0] || !s3[0])) {sB[0] = s2[0]; sB[1] = s2[1];}
    else if (s3[0] && (s3[0] <= s1[0] || !s1[0]) && (s3[0] <= s2[0] || !s2[0])) {sB[0] = s3[0]; sB[1] = s3[1];}

    // sB is now our protein of interest B

    // KNOW: start codon will not be mutated
    // no more than 1 point mutation per codon (2 bits)

    isolateProtein2(oriFilename, sA);
    isolateProtein2(mutFilename, sB);
    // extract protein sequences

    // convert to nucleobase

    // open the new files
    char AName0[1024] = {'i', '\0'};
    strcat(AName0, oriFilename);

    char BName0[1024] = {'i', '\0'};
    strcat(BName0, mutFilename);

    decodeBin(AName0);
    decodeBin(BName0);

    // open the new files
    char AName[1024] = {'n', '\0'};
    strcat(AName, AName0);

    char BName[1024] = {'n', '\0'};
    strcat(BName, BName0);

    FILE* fA = fopen(AName, "r");
    FILE* fB = fopen(BName, "r");

    // start of the start codon is position 1

    // each char is 1 position.

    int numChanges = 0;

    char pA[32768];
    char pB[32768]; // proteins ready to go.

    fgets(pA, 32768, fA);
    fgets(pB, 32768, fB); // read proteins

    printf("%s vs\n%s\n", pA, pB); // debug

    // advance both strings and examine differences

    int pos = 2; // start at second step of protein, after the start codon
    int Boffset = 0; // offset of seqB

    while(pA[pos-1] != '\0') {
        int i = pos-1;

        // case 3: substitution
        // same example, but now let's sub at N = 5

        // ATGABCDEFG
        // 0123456789

        // ATGKABJDEFG
        // 0123456789

        // N = 5 mutation
        // Boff = -1

        // A[5-1] = B[5-1-(-1)] and A[5+1] = B[5+1-(-1)]

        if (pA[i-1] == pB[i-1-Boffset] && pA[i+1] == pB[i+1-Boffset] && pA[i] != pB[i-Boffset]) {
            printf("s\n");

            int c = -1;

            // this time, get the newly inserted one

            if(pB[i-Boffset] == 'A') c = 0;
            else if(pB[i-Boffset] == 'C') c = 1;
            else if(pB[i-Boffset] == 'G') c = 2;
            else if(pB[i-Boffset] == 'T') c = 3;

            fprintf(fout, "%d,2,%d\n", pos, c);
            numChanges++;

            // no change to Boffset;
        }

        // case 1: deletion, given A is correct
        // DELETE at positions 4, 7
        // ex. ATGABCDEFG vs
        //     0123456789
        //     ATGA CD FG
        //     0123 45 67
        // same values at A[3], and A[5] = B[4] for N = 4
        // we then give B an offset
        // if Boffset = 1, then it realigns with A
        // A[6] = B[6-Boffset] and A[7+1] = B[7-Boffset] for N = 7
        else if (pA[i-1] == pB[i-1-Boffset] && pA[i+1] == pB[i-Boffset] && pA[i] != pB[i-Boffset]) {
            printf("d\n");
            // deletion
            int c = -1;

            if(pA[i] == 'A') c = 0;
            else if(pA[i] == 'C') c = 1;
            else if(pA[i] == 'G') c = 2;
            else if(pA[i] == 'T') c = 3;

            fprintf(fout, "%d,0,%d\n", pos, c);
            numChanges++;

            Boffset++;
        }

        // case 2: insertion
        // might not work

        // inserted at N = 4, 7 

        // ex. ATGA BCD E vs
        //     0123 456 7

        //     ATGAZBCDJE
        //     0123456789

        // A[4-1] = B[4-1] same, B[5] = A[4]

        // let Boffset = -1

        // A[7-1] = B[7-1-(-1)], B[9] = A[7]

        // at N = 7, newly inserted is B[7-Boffset]

        else if(pA[i-1] == pB[i-1-Boffset] && pA[i] == pB[i+1-Boffset] && pA[i] != pB[i-Boffset]) {

            printf("i\n");

            int c = -1;

            // this time, get the newly inserted one

            if(pB[i-Boffset] == 'A') c = 0;
            else if(pB[i-Boffset] == 'C') c = 1;
            else if(pB[i-Boffset] == 'G') c = 2;
            else if(pB[i-Boffset] == 'T') c = 3;

            // NOTE: pos may not be the right thing to put

            fprintf(fout, "%d,1,%d\n", pos, c);
            numChanges++;

            Boffset--;
        }
        pos++;
    }
    fclose(fA);
    fclose(fB);
    fclose(fOG);
    fclose(fMUT);
    fclose(fout);
    
    return numChanges;
}