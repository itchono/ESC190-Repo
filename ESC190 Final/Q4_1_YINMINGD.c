#include <stdio.h>
#define L 3
#define M 2
#define N 5
// 3 x 2 x 5 prism

int prism1[L][M][N];
int prism2[L][M][N];
// prisms

// HELPER FUNCTION
int powerOf2(int n) {
    if (n==0) return 1;
    else return 2*powerOf2(n-1);
}

void PartA(int p[L][M][N]) {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < N; k++) {
                p[i][j][k] = powerOf2(i+j+k);
            }
        }
    }
}

void PartB(int p1[L][M][N], int p2[L][M][N]) {
    // p1: the source prism
    // p2: the new prism
    
    for (int x = 0; x < L*M*N; x++) {
        // basically, make it so that we are able to cycle between values
        int i = x / (M*N);
        int j = (x / N) % M;
        int k = x % N;
        p2[i][j][k] = p1[i][j][k];
    }
}

void PartC(int p[L][M][N], int a) {
    for (int x = 0; x < M*N; x++) {
        // similar idea; use modulo and division to achieve single for loop
        // 4^a is the same as 2^(2a)
        // results in a plane of values equal to 4^a along index 2,3 axes
        int j = (x / N) % M;
        int k = x % N;
        p[a][j][k] = powerOf2(2*a);
    }
}

void PartD(int p[L][M][N], int b, int c) {
    for (int x = 0; x < L; x++) {
        // same idea as with C
        // results in a "line" of material along index 1
        p[x][b][c] = powerOf2(b*c);
    }
}

int main() {
    // Just to test and demo the functions
    PartA(prism1);
    // printing
    printf("OG ARRAY\n");
    for (int k = 0; k < N; k++) {
    for (int j = 0; j < M; j++) {
    for (int i = 0; i < L; i++) {
        printf("%d ", prism1[i][j][k]); 
    }
        printf("\n");
    }
        printf("\nNEXT SLICE\n\n");
    }

    PartB(prism1, prism2);

    PartD(prism2, 1, 3);

    printf("NEW ARRAY\n");
    for (int k = 0; k < N; k++) {
    for (int j = 0; j < M; j++) {
    for (int i = 0; i < L; i++) {
        printf("%d ", prism2[i][j][k]); 
    }
        printf("\n");
    }
        printf("\nNEXT SLICE\n\n");
    }

}