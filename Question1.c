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
#include <pthread.h>




//Declare global variables
static int *available;
static int maximum[5][4] = {{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};
static int allocated[5][4];
static int need[5][4] = {{6,4,7,3},{4,2,3,2},{2,5,3,3},{6,3,3,2},{5,5,7,5}};
static char terminate[5]={'e','x','i','t'};
static char request[3]={'r','q'};
static char release[3]={'r','l'};
static char status[7]={'s','t','a','t','u','s'};
static char run[4]={'s','u','n'};
static int exit_cond = 1;
static int holder[5];
pthread_t t1;
pthread_t t2;
pthread_t t3;
pthread_t t4;
pthread_t t5;




int main(int argc, char *argv[]){
	//allocate memory to global arrays
	available = malloc(sizeof(int)*4);

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
				int safe = 1;
				while(comp != NULL)
				{
					holder[i]=atoi(comp);
					comp = strtok(NULL," ");
					i++;
				}
				if(holder[2]>maximum[holder[1]][0]||available[1]-holder[2]<0){
					safe=0;
				}
				if(holder[3]>maximum[holder[1]][1]||available[2]-holder[3]<0){
					safe=0;
				}
				if(holder[4]>maximum[holder[1]][2]||available[3]-holder[4]<0){
					safe=0;
				}
				if(holder[5]>maximum[holder[1]][3]||available[4]-holder[5]<0){
					safe=0;
				}
				if(safe==1){
					printf("State is safe, and request is satisfied\n");
					for(int i = 1; i < 6; i++){
						allocated[holder[1]][i-1] = holder[i+1];
						available[i]-=holder[i+1];
						need[holder[1]][i-1]-=holder[i+1];
					}
				}
				else{
					printf("Request denied\n");
				}
			}
			else if(strcmp(comp,release)==0){
				while(comp != NULL)
				{
					holder[i]=atoi(comp);
					comp = strtok(NULL," ");
					i++;
				}
				for(int i = 1; i < 6; i++){
					allocated[holder[1]][i-1] -= holder[i+1];
					available[i]+=holder[i+1];
				}
				printf("Customer %d released resources.\n",holder[1]);
			}
			else if(strcmp(comp,status)==0){
				printf("Number of customers: %d\n",5);
				printf("Available resources: %d %d %d %d\n",available[1],available[2],available[3],available[4]);
				printf("Maximum Resources:\n");
				for(int i = 0; i < 5; i++){
					for(int j = 0; j<4; j++){
						printf("%d ",maximum[i][j]);
					}
					printf("\n");
				}
				printf("Allocated Resources: \n");
				for(int i = 0; i < 5; i++){
					for(int j = 0; j<4; j++){
						printf("%d ",allocated[i][j]);
					}
					printf("\n");
				}
				printf("Need resources:\n");
				for(int i = 0; i < 5; i++){
					for(int j = 0; j<4; j++){
						printf("%d ",need[i][j]);
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


