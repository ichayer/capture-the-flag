#include "challenges.h"
#include "challengeStrings.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define CHALLENGE_BADFD 13
#define MAX_RAND_CHARACTERS 15

/**
 * @brief Represents a function that will handle a challenge question.
 */
typedef void (*TChallengeQuestionFunction)(int fdOut);

/**
 * @brief Represents a function that will handle a challenge answer.
 * @returns Whether the question was answered correctly.
 */
typedef int (*TChallengeAnswerFunction)(int fdIn, int fdOut);

/**
 * @brief 
 */
typedef struct {
    const char* question;
    const char* questionInvestigate;
    TChallengeQuestionFunction questionFunction;
    const char* answer;
    TChallengeAnswerFunction answerFunction;
} TChallenge;

static ssize_t dgetline(int fd, char* buffer, size_t maxSize) {
    ssize_t count = 0;
    char c;

    while (read(fd, &c, 1) > 0 && c != '\n') {
        if (count < maxSize - 1) {
            buffer[count++] = c;
        }
    }

    buffer[count] = '\0';
    return count;
}

static void writeBadFD(int fdOut);
static void filter(int fdOut);
static void hiddenString(int fdOut);
static void normal(int fdOut);
static int quine(int fdIn, int fdOut);

int gdbme(int fdIn, int fdOut) {
    pid_t pid = getpid();
    if (pid == 0x12345678) {
        dprintf(fdOut, "La respuesta es gdb_rules");
    }

    char enteredAnswer[1024];
    ssize_t n = dgetline(fdIn, enteredAnswer, sizeof(enteredAnswer));
    return n >= 0 && strncmp(enteredAnswer, "gdb_rules", n) == 0;
}

static const TChallenge challenges[] = {
    {questions[0],  questionsInvestigate[0],    NULL,           answers[0],     NULL},
    {questions[1],  questionsInvestigate[1],    NULL,           answers[1],     NULL},
    {questions[2],  questionsInvestigate[2],    NULL,           answers[2],     NULL},
    {questions[3],  questionsInvestigate[3],    writeBadFD,     answers[3],     NULL},
    {questions[4],  questionsInvestigate[4],    NULL,           answers[4],     NULL},
    {questions[5],  questionsInvestigate[5],    NULL,           answers[5],     NULL},
    {questions[6],  questionsInvestigate[6],    filter,         answers[6],     NULL},
    {questions[7],  questionsInvestigate[7],    hiddenString,   answers[7],     NULL},
    {questions[8],  questionsInvestigate[8],    NULL,           answers[8],     NULL},
    {questions[9],  questionsInvestigate[9],    NULL,           answers[9],     quine},
    {questions[10], questionsInvestigate[10],   NULL,           answers[10],    gdbme},
    {questions[11], questionsInvestigate[11],   normal,         answers[11],    NULL}
};



int executeChallenge(int index, int fdIn, int fdOut) {
    if (index < 0 || index >= (sizeof(challenges) / sizeof(challenges[0]))) {
        return 0;
    }
    
    const TChallenge* challenge = &challenges[index];
    char enteredAnswer[1024];
    int answeredCorrectly;
    
    do {
        if (challenge->question != NULL) {
            dprintf(fdOut, "%s", "------------- DESAFIO -------------\n");
            dprintf(fdOut, "%s\n", challenge->question);
        }
        
        if (challenge->questionInvestigate != NULL) {
            dprintf(fdOut, "%s", "----- PREGUNTA PARA INVESTIGAR -----\n");
            dprintf(fdOut, "%s\n", challenge->questionInvestigate);
        }
        
        if (challenge->questionFunction != NULL) {
            challenge->questionFunction(fdOut);
        }

        if (challenge->answer != NULL) {
            ssize_t n = dgetline(fdIn, enteredAnswer, sizeof(enteredAnswer));
            if (n < 0) {
                printf("Failed to read from file descriptor %d. Server closing.\n", fdIn);
                return 0;
            }
            answeredCorrectly = (strncmp(enteredAnswer, challenge->answer, n) == 0);
        } else {
            answeredCorrectly = challenge->answerFunction == NULL ? 1 : challenge->answerFunction(fdIn, fdOut);
        }

    } while (!answeredCorrectly);

    dprintf(fdOut, "\n\n");
    return 1;
}

void writeBadFD(int fdOut) {
    dprintf(CHALLENGE_BADFD, "................................La respuesta es fk3wfLCm3QvS");
}

static void filter(int fdOut) {
    static char* answer = "La respuesta es K5n2UFfpFMUN";
    
    srand(time(NULL));
    
    int random;
    for (int i = 0; answer[i]; ++i) {
        random = randNormalize() * MAX_RAND_CHARACTERS;
        for (int j = 0; j < random ; ++j) {
            dprintf(STDERR_FILENO, "%c", randPrintableCharacter());
        } 
        dprintf(fdOut, "%c", answer[i]);
    }
}

static void hiddenString(int fdOut) {
    dprintf(fdOut, "%s", "\033[30;40mLa respuesta es: BUmyYq5XxXGt\033[0m\n");
}

static void normal(int fdOut){
    for(int i = 0 ; i < 1000 ; ++i){
        dprintf(fdOut, "%g ", randNormal());
    }
}

static int quine(int fdIn, int fdOut) {
    return 0;
}