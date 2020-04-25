#include <stdio.h>
#include <math.h>


double find_nth_log(double x, double n, double epsilon) {
    /*
    x: number to take the logarithm of
    n: number specifying which logarithm base to apply
    epsilon: tolerance
    /*/
    // Implement below

    // how many times do we need to exponentiate to find?
    double log = 0;

    while(x >= pow(n, log + epsilon)) {
        log += epsilon;
    }
    return log;
}

int main() {
    // testing code

    int n = 3;

    for (int x = 1; x < 70; x++) {
        printf("%g vs actual %g\n", find_nth_log(x, n, 0.005), log(x)/log(n)); // compares values
    }
    
}