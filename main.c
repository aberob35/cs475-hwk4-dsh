/*
 * main.c
 *
 *  Created on: Mar 17 2017
 *      Author: david
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include "dsh.h"
#include <sys/wait.h>

int main(int argc, char **argv){
	//create variables 
	char temp[256];
	int boolean = 0;

	//while loop to reprompt
	//reprompt may look a little weird when & is inputted 
	//but it does work
	while(boolean == 0){
	//prompt user 1st time and adds terminating char at end of string
	printf("Dsh> ");
	fgets(temp,256,stdin);
	temp[strlen(temp) - 1] = '\0';

	//ends while loop is exit inputted
	if(strcmp(temp,"exit") == 0){
		exit(1);
		//boolean = 1;
	}else if(strcmp(temp,"\0") == 0){
	printf("ERROR EMPTY STRING ENTERED \n");
	printf("Dsh> ");
	fgets(temp,256,stdin);
	temp[strlen(temp) - 1] = '\0';
	}


	if(temp[0] == '/'){
		//checks for & symbol at end of command and runs mode 1
		//check in order to see if it should run for or background
		int bgVal = 0;
		char *andCheck = strchr(temp,'&');
		if(andCheck != NULL && andCheck == (temp + strlen(temp) -1)){
			temp[strlen(temp) - 2] = '\0';
			bgVal = 1;
		}
		mode1(temp, bgVal);
	}else {
		//checks for & symbol at end of command and runs mode 2
		//check in order to see if it should run for or background
		
		int bgVal = 0;
		char *andCheck = strchr(temp,'&');
		if(andCheck != NULL && andCheck == (temp + strlen(temp) -1)){
			temp[strlen(temp) - 2] = '\0';
			bgVal = 1;
		}
		mode2(temp,bgVal);
	}
}
	return 0;
}
