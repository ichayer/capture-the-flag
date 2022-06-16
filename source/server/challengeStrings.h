#ifndef _CHALLENGE_STRINGS_H_
#define _CHALLENGE_STRINGS_H_

const char* const questions[] = {
    /*01*/ "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\n"
           "En este TP deberan finalizar el juego que ya comenzaron resolviendo los desafios de cada nivel.\n"
           "Ademas tendran que investigar otras preguntas para responder durante la defensa.\n"
           "El desafio final consiste en crear un programa que se comporte igual que yo, es decir, que provea\n"
           "los mismos desafios y que sea necesario hacer lo mismo para resolverlos. No basta con esperar la respuesta.\n"
           "Ademas, deberan implementar otro programa para comunicarse conmigo.\n"
           "Deberan estar atentos a los easter eggs.\n\n"
           "Para verificar que sus respuestas tienen el formato correcto respondan a este desafio con la palabra \'entendido\'",
    /*02*/ "The Wire S1E5 \n5295 888 6288",
    /*03*/ "https://ibb.co/tc0Hb6w",
    /*04*/ "EBADF... \nwrite: Bad file descriptor",
    /*05*/ "respuesta = strings:277",
    /*06*/ ".data .bss .comment ? .shstrtab .symtab .strtab",
    /*07*/ "Filter error",
    /*08*/ "¿?",
    /*09*/ "Latexme \nSi \n\\mathrm{d}y = u^v{\\cdot}(v'{\\cdot}\\ln{(u)}+v{\\cdot}\frac{u'}{u}) \nentonces \ny =",
    /*10*/ "quine",
    /*11*/ "b gdbme y encontrá el valor mágico",
    /*12*/ "Me conoces"
};

const char* const questionsInvestigate[] = {
    /*01*/ "¿Como descubrieron el protocolo, la direccion y el puerto para conectarse?",
    /*02*/ "¿Que diferencias hay entre TCP y UDP y en que casos conviene usar cada uno?",
    /*03*/ "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por que?",
    /*04*/ "¿Que util abstraccion es utilizada para comunicarse con sockets? ¿Se puede utilizar read(2) y write(2) para operar?",
    /*05*/ "¿Como garantiza TCP que los paquetes llegan en orden y no se pierden?",
    /*06*/ "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Que conviene mas?",
    /*07*/ "¿Como se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
    /*08*/ "¿Que aplicaciones se pueden utilizar para ver el trafico por la red?",
    /*09*/ "sockets es un mecanismo de IPC. ¿Que es mas eficiente entre sockets y pipes?",
    /*10*/ "¿Cuales son las caracteristicas del protocolo SCTP?",
    /*11*/ "¿Que es un RFC?",
    /*12*/ "¿Fue divertido?"
};

const char* const answers[] = {
    /*01*/ "entendido",
    /*02*/ "itba",
    /*03*/ "M4GFKZ289aku",
    /*04*/ "fk3wfLCm3QvS",
    /*05*/ "too_easy",
    /*06*/ ".RUN_ME",
    /*07*/ "K5n2UFfpFMUN",
    /*08*/ "BUmyYq5XxXGt",
    /*09*/ "u^v",
    /*10*/ "chin_chu_lan_cha",
    /*11*/ "gdb_rules",
    /*12*/ "normal"
};

#endif