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


struct Process* create_process(char* name, long start, long end, long size) {
    struct Process* tmp = NULL;
    tmp = (struct Process*)malloc(sizeof(struct Process));
    strcpy(tmp->p_name, name);
    tmp->p_start = start;
    tmp->p_end = end;
    tmp->p_size = size;
    return tmp;
}

/*
Creates struct node where it points to process and next is null
returns created node
*/
struct Node* create_node(struct Process *process) {
    struct Node* newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->p = *process;
    newNode->next = NULL;
    return newNode;
}

/*
Insert process into LinkedList
head - head of linked list
process - Process to be inserted into linked list
pos - position for the process to be inserted at
*/
void insert_process(struct Node** head, struct Process* process, int pos) {
    while (pos--) {
        if (pos == 0) {
            struct Node *temp = create_node(process);
            temp->next = *head;
            *head = temp;
        } else {
            head = &(*head)->next;
        }
    }

    data->free_memory = data->free_memory - process->p_size;
    data->processes++;
}

/*
Delete process from linkedList given name of the process
head - head of linked list
name - name of process to be deleted
*/
void delete_process(struct Node** head, char *name) {
    struct Node *temp = *head, *prev;
    while (temp != NULL && strcmp(temp->p.p_name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL){
        return;
    }
    prev->next = temp->next;
    data->free_memory = data->free_memory + temp->p.p_size;
    data->processes--;
    free (temp);
}

/*
Print out contents of head
*/
void print_handler(struct Node* head) {
    while (head != NULL) {
        printf("[%ld : %ld] Process - %s\n", head->p.p_start, head->p.p_end, head->p.p_name);
        head = head->next;
    }
}

int main(int argc, char *argv[]) {
/*
Variables
*/
    data = (struct Handler*)malloc(sizeof(struct Handler));


    data->allocated_memory = atoi(argv[1]);
    data->free_memory = atoi(argv[1]);
    data->processes = 0;

    // Creating initial structure for process management
    struct Process *end = create_process("test1", data->allocated_memory, data->allocated_memory, 0);
    struct Node *endNode = create_node(end);
    struct Process *start = create_process("test2", 0, 0, 0);
    struct Node *processInfo = create_node(start);
    processInfo->next = endNode;
    // Finished creating structure

    struct Process *test = create_process("test3", 0, 0, 0);;
    insert_process(&processInfo, test, 2);
    print_handler(processInfo);
    printf("Trying to delete\n");
    delete_process(&processInfo, "test3");
    print_handler(processInfo);



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