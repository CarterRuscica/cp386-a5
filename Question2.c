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
#define BUFFERSIZE 500

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
    long start;
    start = 0;

    while (pos--) {
        if (pos == 0) {
            struct Node *temp = create_node(process);
            temp->next = *head;
            *head = temp;
            temp->p.p_start = start;
            temp->p.p_end = start + temp->p.p_size;
        } else {
            start = (*head)->p.p_end;
            head = &(*head)->next;
            // printf("Current starts at: %ld\n", start);
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

int find_spot(struct Node *head, long required_space) {
    long end, start, space, optimal_space, optimal_spot, spot;
    end = 0;
    start = 0;
    space = 0;
    optimal_space = 99999999999;
    optimal_spot = 0;
    spot = 2;
    while (head->next != NULL) {
        start = head->p.p_end;
        head = head->next;
        end = head->p.p_start;
        space = end - start;
        // printf("Current space: %ld\n", space);
        if (space >= required_space && space < optimal_space) {
            optimal_space = space;
            optimal_spot = spot;
            // printf("Optimal Spot found in space of: %ld\n", optimal_space);
            // printf("@: %ld\n", optimal_spot);
        }
        spot++;
    }
    return optimal_spot;
}

/*
Print out contents of head
*/
void print_handler(struct Node* head) {
    while (head != NULL) {
        printf("[%ld : %ld] Process - %s\n", head->p.p_start, (head->p.p_end - 1) , head->p.p_name);
        head = head->next;
    }
}

void len_print_handler(struct Node* head) {
    printf("Partitions [Allocated memory = %d]:\n", data->allocated_memory - data->free_memory);
    while (head != NULL) {
        if (strcmp(head->p.p_name, "IGNORE") != 0) {
            printf("Address [%ld : %ld] Process - %s\n", head->p.p_start, (head->p.p_end - 1) , head->p.p_name);
        }
        head = head->next;
    }
}

void hole_print_handler(struct Node* head) {
    long end, start, size;
    end = 0, start = 0;
    printf("Holes [Free memory = %d]:\n", data->free_memory);
    while (head != NULL) {
        if ((start - end) != 0) {
            printf("Address [%ld:%ld] len = %ld\n", end, start, (start - end));
        }
        end = head->p.p_end;
        size = head->p.p_size;
        head = head->next;
        if (head != NULL) {
            start = head->p.p_start;
        }
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
    struct Process *end = create_process("IGNORE", data->allocated_memory, data->allocated_memory, 0);
    struct Node *endNode = create_node(end);
    struct Process *start = create_process("IGNORE", 0, 0, 0);
    struct Node *processInfo = create_node(start);
    processInfo->next = endNode;
    // Finished creating structure

    // struct Process *test = create_process("test3", 125, 250, 125);;
    // insert_process(&processInfo, test, 2);
    // test = create_process("test4", 500, 700, 200);
    // insert_process(&processInfo, test, 3);
    // print_handler(processInfo);
    // printf("Trying to delete\n");
    // delete_process(&processInfo, "test3");
    // print_handler(processInfo);

    // int spot = find_spot(processInfo, 120);
    // printf("SPOT FOUND AT: %d\n", spot);

    /*
    data has attributes of memory

    head will track processes
    */

    printf("Allocated %d bytes of memory\n", data->allocated_memory);
    char *name;
    char *algo;
    long size;
    int i;
    int spot;
    struct Process *temp;

    while (1) {
        char buffer[BUFFERSIZE];
        printf("command>");
        fgets(buffer, BUFFERSIZE, stdin);
        buffer[strcspn(buffer, "\n")] = 0;

        char *cmd = strtok(buffer, " ");
        char *func = &cmd[0];

        i = 0;
        while( cmd != NULL ) {
            if (i == 0) {
                func = cmd;
            } else if (i == 1) {
                name = cmd;
            } else if (i == 2) {
                size = atoi(cmd);
            } else if (i == 3) {
                algo = cmd;
            }
            cmd = strtok(NULL, " ");
            i++;
        }


        if (strcmp(func, "RQ") == 0) {     
            spot = find_spot(processInfo, size);
            if (spot == 0) {
                printf("No hole of sufficient size");
            } else {
                temp = create_process(name, 0, 0, size);
                insert_process(&processInfo, temp, spot);
            }

        } else if (strcmp(func, "RL") == 0) {
            printf("releasing memory for process %s\n", name);
            delete_process(&processInfo, name);
            printf("Successfully released process %s\n", name);


        } else if (strcmp(func, "Status") == 0) {
            len_print_handler(processInfo);
            printf("\n");
            hole_print_handler(processInfo);
            // print_handler(processInfo);
        } else if (strcmp(func, "Exit") == 0) {
            printf("Exiting Program\n");
            exit(0);
        } else {
            printf("Improper command entered\n");
        }





    }




}