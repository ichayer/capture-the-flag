// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/* Standard library */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

/* Local headers */
#include "challenges.h"
#include "utils.h"

#define CHALLENGE_BADFD 13
#define MAX_RAND_CHARACTERS 15

/**
 * @brief Represents a function that will handle a challenge question.
 */
typedef void (*TChallengeQuestionFunction)(int fdOut);

/**
 * @brief Represents a function that will handle a challenge answer.
 *
 * @returns Whether the question was answered correctly.
 */
typedef int (*TChallengeAnswerFunction)(int fdIn, int fdOut);

/**
 * @brief Represents a single challenge. A challenge may be as simple as
 * a string question with a string answer, or may implement functions and
 * save them as pointers in this struct to create more complex functionality.
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
    ssize_t r;
    char c;
    while ((r = read(fd, &c, 1)) >= 0 && c != '\n') {
        if (c < 32 || c > 126) {
            continue;
        }

        if (count < maxSize - 1) {
            buffer[count++] = c;
        }
    }

    buffer[count] = '\0';
    return count == 0 ? r : count;
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

    return 0;
}

static const TChallenge challenges[] = {
    {"Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\n"
     "En este TP deberan finalizar el juego que ya comenzaron resolviendo los desafios de cada nivel.\n"
     "Ademas tendran que investigar otras preguntas para responder durante la defensa.\n"
     "El desafio final consiste en crear un programa que se comporte igual que yo, es decir, que provea\n"
     "los mismos desafios y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\n"
     "Ademas, deberan implementar otro programa para comunicarse conmigo.\n"
     "Deberan estar atentos a los easter eggs.\n\n"
     "Para verificar que sus respuestas tienen el formato correcto respondan a este desafio con la palabra \'entendido\'",
     "¿Como descubrieron el protocolo, la direccion y el puerto para conectarse?", NULL, "entendido", NULL},
    {"The Wire S1E5 \n5295 888 6288", "¿Que diferencias hay entre TCP y UDP y en que casos conviene usar cada uno?", NULL, "itba", NULL},
    {"https://ibb.co/tc0Hb6w", "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por que?", NULL, "M4GFKZ289aku", NULL},
    {"EBADF... \nwrite: Bad file descriptor", "¿Que util abstraccion es utilizada para comunicarse con sockets? ¿Se puede utilizar read(2) y write(2) para operar?", writeBadFD, "fk3wfLCm3QvS", NULL},
    {"respuesta = strings:63", "¿Como garantiza TCP que los paquetes llegan en orden y no se pierden?", NULL, "too_easy", NULL},
    {".text .fini .rodata ? .eh_frame_hdr .eh_frame .init_array", "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Que conviene mas?", NULL, ".RUN_ME", NULL},
    {"Filter error", "¿Como se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?", filter, "K5n2UFfpFMUN", NULL},
    {"¿?", "¿Que aplicaciones se pueden utilizar para ver el trafico por la red?", hiddenString, "BUmyYq5XxXGt", NULL},
    {"Latexme \nSi \n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\frac{u'}{u}) \nentonces \ny =", "sockets es un mecanismo de IPC. ¿Que es mas eficiente entre sockets y pipes?", NULL, "u^v", NULL},
    {"quine", "¿Cuales son las caracteristicas del protocolo SCTP?", NULL, "chin_chu_lan_cha", quine},
    {"b gdbme y encontrá el valor mágico", "¿Que es un RFC?", NULL, "gdb_rules", gdbme},
    {"Me conoces", "¿Fue divertido?", normal, "normal", NULL}
};

int executeChallenge(int index, int fdIn, int fdOut) {
    if (index < 0 || index >= (sizeof(challenges) / sizeof(challenges[0]))) {
        return 0;
    }

    const TChallenge* challenge = &challenges[index];
    char enteredAnswer[1024];
    int answeredCorrectly;

    do {
        clearScreen();
        if (challenge->question != NULL) {
            dprintf(fdOut, "%s", "------------- DESAFIO -------------\n");
            dprintf(fdOut, "%s\n", challenge->question);
        }

        if (challenge->questionInvestigate != NULL) {
            dprintf(fdOut, "%s", "\n----- PREGUNTA PARA INVESTIGAR -----\n");
            dprintf(fdOut, "%s\n", challenge->questionInvestigate);
        }

        if (challenge->questionFunction != NULL) {
            challenge->questionFunction(fdOut);
        }

        answeredCorrectly = 1;

        if (challenge->answerFunction != NULL) {
            answeredCorrectly = challenge->answerFunction(fdIn, fdOut);
        }

        if (challenge->answer != NULL) {
            ssize_t n = dgetline(fdIn, enteredAnswer, sizeof(enteredAnswer));
            if (n < 0) {
                printf("Failed to read from file descriptor %d. Server closing.\n", fdIn);
                perror(NULL);
                return 0;
            }

            while (n > 0 && isspace(enteredAnswer[n - 1])) {
                n--;
                enteredAnswer[n] = '\0';
            }

            char* start = enteredAnswer;
            while (n > 0 && isspace(*start)) {
                start++;
                n--;
            }

            answeredCorrectly = (strcmp(start, challenge->answer) == 0);

            if (!answeredCorrectly) {
                dprintf(fdOut, "Respuesta incorrecta: %s", start);
                sleep(2);
            }
        }

    } while (!answeredCorrectly);
    dprintf(fdOut, "\n\n");
    return 1;
}

void writeBadFD(int fdOut) {
    const char* s = "................................La respuesta es fk3wfLCm3QvS";
    write(CHALLENGE_BADFD, s, strlen(s));
}

static void filter(int fdOut) {
    static char* answer = "La respuesta es K5n2UFfpFMUN";

    srand(time(NULL));

    for (int i = 0; answer[i]; ++i) {
        int random = randNormalize() * MAX_RAND_CHARACTERS;
        for (int j = 0; j < random; ++j) {
            dprintf(fdOut, "%c", randPrintableCharacter());
        }
        dprintf(fdOut, "%c", answer[i]);
    }
}

static void hiddenString(int fdOut) {
    dprintf(fdOut, "%s", "\033[30;40mLa respuesta es: BUmyYq5XxXGt\033[0m\n");
}

static void normal(int fdOut) {
    for (int i = 0; i < 1000; ++i) {
        dprintf(fdOut, "%g ", randNormal());
    }
}

static int quine(int fdIn, int fdOut) {
    int e = system("gcc quine.c -o quine");
    if (e != 0) {
        return 0;
    }

    dprintf(fdOut, "%s", "\n¡Genial!, ya lograron meter un programa en quine.c, veamos si hace lo que corresponde.\n");

    e = system("./quine | diff - quine.c");
    if (e != 0) {
        dprintf(fdOut, "%s", "diff encontró diferencias.\n");
        return 0;
    }

    dprintf(fdOut, "%s", "La respuesta es chin_chu_lan_cha\n");
    return 1;
}