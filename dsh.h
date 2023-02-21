/*
 * dsh.h
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */

#define MAXBUF 256
#define HISTORY_LEN 100

// TODO: Your function prototypes below
char** split(char *str, char *delim);
void mode1(char *temp, int bgVal);
void mode2(char *temp, int bgVal);
void cdCommand(char *temp);
void errorCase(char **terms);
