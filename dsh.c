/*
 * dsh.c
 *
 *  Created on: Aug 2, 2013
 *      Author: chiu
 */
#include "dsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include <errno.h>
#include <err.h>
#include <sys/stat.h>
#include <string.h>
#include "builtins.h"

//TODO: Your function definitions (declarations in dsh.h)
char** split(char *str, char *delim){
    //allocating space 
    char **terms = (char**) malloc(256 * sizeof(char*));
    //variables for delimeter function
    char * delimeter = delim;       
    char * token = strtok(str, delim); 
    int counter = 0;
    //while loop to get all tokens
    while (token != NULL) { 
        terms[counter] = (char*) malloc(256 * sizeof(char));
        strcpy(terms[counter], token);
        counter++;
        //printf("%s \n", token);           
        token = strtok(NULL, delimeter);           
    }  
    terms[counter] = NULL;
    return terms;
}

void mode1(char *temp, int bgVal){
	//get commands and store them
	char **terms;
	terms = split(temp," ");
	if(access(terms[0], F_OK | X_OK) == 0){
		//create child to run command parent to reprompt
	if(0 != fork()){
		//deals with & case
		if(bgVal == 1){
		printf("\n");
		wait(NULL);
		}
	}else{
		//runs the command and reprompts
		execv(terms[0],terms);
		printf("ERROR: %s not found! \n", terms[0]);
		exit(1);
	}
	}else{
		//error to say file is not good
		printf("File %s does not exist \n", terms[0]);
	}
	free(terms);
 }

void mode2(char *temp, int bgVal){
	char **terms;
	char copyTemp[256];
	strcpy(copyTemp, temp);
	//get commands and store them
	terms = split(copyTemp," ");

	//checks if cd was entered and deals with comand
	if(strcmp(terms[0], "cd") == 0){
		cdCommand(temp);

	}else if(strcmp(terms[0], "pwd") == 0){
		char cwd[256];
		getcwd(cwd,256);
		printf("%s \n", cwd);
	}else if(access(terms[0], F_OK | X_OK) == 0){

	//run process
	if(0 != fork()){

	//dealing with & case
	if(bgVal == 0){
	printf("\n");
	wait(NULL);
	}

	//if not then output error
	}else{
		//runs the command and reprompts
		execv(terms[0],terms);
		printf("ERROR: %s not found! \n", terms[0]);
		exit(1);
	}
//if cd or pwd was not inputted test for other cases
//test if it is in current wd
}else{

	//get all possible paths and test 
	char *env = getenv("PATH");
	//copy over becuase my split destorys line feed to it
	// and i need the orginal line so i let split destroy a copy
	char *copy = (char *)malloc(strlen(env) + 1);
	strcpy(copy,env);

	char **allPath = split(copy, ":");
	for(int i = 0; allPath[i] != NULL; i++){
		strcat(allPath[i], "/");
		strcat(allPath[i], terms[0]);
		//printf("%s\n", allPath[i]);
		if(access(allPath[i], F_OK | X_OK) == 0){
			if(0 != fork()){

				//dealing with & case
				if(bgVal == 0){
				wait(NULL);
				printf("\n");
				}
			}else{
				execv(allPath[i], terms);
				//error case
				printf("Error: %s not valid \n", terms[0]);
				exit(1);
			}
		}
	}
	errorCase(terms);
	// if(strcmp(terms[0], "exit") != 0 || strcmp(terms[0], "cd") != 0 || strcmp(terms[0], "ls") != 0 || strcmp(terms[0], "cat") != 0)
	// printf("Error This ONE: %s not valid \n", terms[0]);
}
free(terms);
 
}


void cdCommand(char *temp){
	char **terms;
	char *path;
	char *currentD = (char*) malloc(256 * sizeof(char));

	//get commands and store them
	terms = split(temp, " ");
	//checks if command cd is inputted
	if(strcmp(terms[0],"cd") == 0 && terms[1] != NULL){

	//gets the current working directory and adds where user wants to go to
	path = getcwd(currentD, 256);
	strcat(path,"/");
	strcat(path, terms[1]);
	printf("%s", path);
	int successCD = chdir(path);
	//if it worked 
	if(successCD == 0){
		printf("\n");
	}else{
		printf("Cannot change into certain directory");
	}
	
  }else{
	char *home = getenv("HOME");
	chdir(home);
  }
  free(terms);
}

void errorCase(char **terms){
	//test to see if the inputted value is one of the commands to deal with
	//since our shell is supposed to only work with these commands 
	// I test them this way. If it is all possible commands this 
	//function would be way bigger but our shell only neeeds these commands
	if(strcmp(terms[0], "exit") == 0){
	}else if(strcmp(terms[0], "ls") == 0){
	}else if(strcmp(terms[0], "cat") == 0){
	}else if(strcmp(terms[0], "cd") == 0){
	}else if(strcmp(terms[0], "pwd") == 0){
	}else{
	printf("Error: %s not valid \n", terms[0]);
	}
}
