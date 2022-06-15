#include "utils.h"
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

double randNormalize() {
    return rand() / ((double) RAND_MAX + 1);
}

char randPrintableCharacter() {
    char c = randNormalize() * 127;
    while(!isprint(c)){
        c = randNormalize() * 127;
    }
    return c;
}

//https://www.tutorialspoint.com/generate-random-numbers-following-a-normal-distribution-in-c-cplusplus
double randNormal() {
   // return a normally distributed random value
   double v1=randNormalize();
   double v2=randNormalize();
   return cos(2*3.14*v2)*sqrt(-2.*log(v1));
}