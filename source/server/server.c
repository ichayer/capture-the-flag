#include <stdio.h>
#include <unistd.h>
#include "challenges.h"

int main(int argc, char* argv[]) {
    printf("Hola ;)\n");

    int index = 0;
    while (executeChallenge(index, STDIN_FILENO, STDOUT_FILENO)) {
        index++;
    }
}