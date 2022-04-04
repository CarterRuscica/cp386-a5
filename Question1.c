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
static int need[5][4] = {{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};
static char terminate[5]={'e','x','i','t'};
static char request[3]={'r','q'};
static char release[3]={'r','l'};
static char status[7]={'s','t','a','t','u','s'};
static char run[4]={'s','u','n'};
static int exit_cond = 1;
static int holder[5];





int main(int argc, char *argv[]){
	//allocate memory to global arrays
	available = malloc(sizeof(int)*4);
	allocated = malloc(sizeof(int)*4);

	//populate available array
	for(int i=0; i < argc; i++){
		available[i] = atoi(argv[i]);
	}
		//Setup for exit conditions
		char command[12]={0};
		//main while loop
		int j = 0;
		while(exit_cond != 0){
			printf("Enter a command:");
			scanf(" %[^\n]s",command);
			char* comm;
			for(int i = 0; terminate[i];i++){
				command[i]=tolower(command[i]);
			}
			//direct to one of if statements depending on command

			char *comp;
			int i = 0;
			char* ret;

			comp = strtok(command," ");
			if(strcmp(terminate,comp)==0){
				exit_cond=0;
			}
			else if(strcmp(comp,request)==0){
				while(comp != NULL)
				{
					holder[i]=atoi(comp);
					comp = strtok(NULL," ");
					i++;
				}
			}
			else if(strcmp(comp,release)==0){
				while(comp != NULL)
				{
					holder[i]=atoi(comp);
					comp = strtok(NULL," ");
					i++;
				}
			}
			else if(strcmp(comp,status)==0){
				printf("Number of customers: %d\n",5);
				printf("Currently available resources: %d %d %d %d\n",available[1],available[2],available[3],available[4]);
				printf("Maximum Resources from File:\n");
				for(int i = 0; i < 5; i++){
					for(int j = 0; j<4; j++){
						printf("%d ",maximum[i][j]);
					}
					printf("\n");
				}
			}
			else if(strcmp(comp,run)==0){
				printf("Run");
			}
			else{
				printf("Invalid input, use one of RQ, RL, Status, Run, Exit\n");
			}
		}

}


