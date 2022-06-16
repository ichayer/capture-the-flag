// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/* Standard library */
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

/* Local headers */
#include "utils.h"

double randNormalize() {
    return rand() / ((double)RAND_MAX + 1);
}

char randPrintableCharacter() {
    char c = randNormalize() * 127;
    while (!isprint(c)) {
        c = randNormalize() * 127;
    }
    return c;
}

// https://www.tutorialspoint.com/generate-random-numbers-following-a-normal-distribution-in-c-cplusplus
double randNormal() {
    // return a normally distributed random value
    double v1 = randNormalize();
    double v2 = randNormalize();
    return cos(2 * 3.14 * v2) * sqrt(-2. * log(v1));
}

void clearScreen() {
    write(1, "\033[1;1H\033[2J", 10);
}