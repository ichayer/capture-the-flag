#ifndef _CHALLENGES_H_
#define _CHALLENGES_H_

/**
 * @brief Executes the challenge whose number is the given in index.
 * 
 * @returns 1 if the challenge existed and was run, 0 otherwise.
 */
int executeChallenge(int index, int fdIn, int fdOut);

#endif