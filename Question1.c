/*
===============================================================================================
Author: Patrick Maldonado Lentz
ID: 190647690
Date: April 3rd 2022

Programming Banker's Algorithm
================================================================================================
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Declare global variables
static int *available;
static int maximum[5][4] = {{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};
static int *allocated;
static int *need;


int main(int argc, char *argv[]){
	//allocate memory to global arrays
	available = malloc(sizeof(int)*4);
	allocated = malloc(sizeof(int)*4);
	need = malloc(sizeof(int)*4);

	//populate available array
	for(int i=1; i < argc; i++){
		available[i] = atoi(argv[i]);
	}
	//Setup for exit conditions
	char command[12]={0};
	char terminate[5]={'e','x','i','t'};
	int exit_cond = 1;

	//main while loop
	while(exit_cond != 0){
		printf("Enter a command:");
		scanf("%s",command);
		for(int i = 0; terminate[i];i++){
			command[i]=tolower(command[i]);
		}
		printf("%d",strcmp(terminate,command));
		if(strcmp(terminate,command)==0){

			exit_cond=0;
		}

	}

}


