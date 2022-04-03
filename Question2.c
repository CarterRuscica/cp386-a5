/*
===============================================================================================
Author: Carter Ruscica
ID: 131008600
Date: April 2nd 2022

Programming Best-Fit Algorithm for contiguous memory allocation
================================================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BUFFERSIZE 10

/*
Global variables
*/
struct Handler* data;

/*
Process Structure -
    Has necessary fields to make it such that a process takes up space and has a location
*/
struct Process {
    char p_name[10];
    long p_start;
    long p_end;
    long p_size;
};

struct Node {
    struct Process p;
    struct Node* next;
};

struct Handler {
    int allocated_memory;
    int free_memory;
    int processes;
};


struct Node* create_process(char* name, long start, long end, long size) {
    struct Node* tmp = NULL;
    tmp = (struct Node*)malloc(sizeof(struct Node));
    strcpy(tmp->p.p_name, name);
    tmp->p.p_start = start;
    tmp->p.p_end = end;
    tmp->p.p_size = size;
    return tmp;
}

struct Node* delete_process(struct Node* head, char name) {

}

void print_process_info(struct Process p) {
    printf("Address [%ld, %ld] Process %s\n", p.p_start, p.p_end, p.p_name);
}

int main(int argc, char *argv[]) {
/*
Variables
*/
    struct Node *head;
    data = (struct Handler*)malloc(sizeof(struct Handler));
    head = (struct Node*)malloc(sizeof(struct Node));


    data->allocated_memory = atoi(argv[1]);
    data->free_memory = atoi(argv[1]);
    data->processes = 0;
    /*
    data has attributes of memory

    head will track processes
    */

    printf("Allocated %d bytes of memory\n", data->allocated_memory);
    while (1) {
        char buffer[BUFFERSIZE];
        printf("command>");
        fgets(buffer, BUFFERSIZE, stdin);
        
        char *cmd;
        cmd = strtok (buffer, " ");
        char *func = &cmd[0];

        if (strcmp(func, "RQ") == 0) {
            printf("RQ\n");


        } else if (strcmp(func, "RL") == 0) {
            printf("RL\n");


        } else if (strcmp(func, "Status\n") == 0) {
            printf("IN STATUS\n");


        } else if (strcmp(func, "Exit\n") == 0) {
            printf("Exiting Program\n");
            exit(0);
        } else {
            printf("Improper command entered\n");
        }





    }




}