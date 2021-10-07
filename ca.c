#include "ca.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_CELLS 10
#define MAX_CELLS 100

struct ca_data *create1DCA(int length, unsigned char value) {
    struct ca_data *c = malloc(sizeof(struct ca_data));
    if (c == NULL) error("Failed to initialize ca_data struct", 1);
    c->cells = malloc(length * sizeof(unsigned char));
    if (c->cells == NULL) error("Failed to initialize c->cells", 1);
    c->length = length;
    if (value == '-') {
        c->intialState = '0';
    } else {
        c->intialState = value;
    }
    return c;
}

/**
 * This function initializes a one-dimensional cellular automaton to 
 * the quiescent, all zero state. The 1DCA is stored as an array of unsigned char type.
**/
void init1DCA(struct ca_data *data, int value) {
    if (data == NULL) error("NULL data argument", 1);
    srand(time(0));
    for (int i = 0; i < data->length; i++) {
        if (value == -1) {
            data->cells[i] = rand() % data->numStates + '0';
        } else {
            data->cells[i] = value + '0';  // initialize to 'value'
        }
    }
}

/**
 * This function allows the client to set the specified cell to a specified state.
**/
int set1DCACell(struct ca_data *data, unsigned int index, unsigned char value) {
    if (data == NULL) error("NULL data argument", 1);
    if (value-48 > data->numStates-1 || value-48 < 0) error("Invalid value argument", 1);
    if (index < 0 || index > data->length - 1) error("Invalid index argument", 1);
    data->cells[index] = value;  // set value
    return 1;
}

/**
 * Gets the value of the CA given an index.
**/
unsigned char get1DCACell(struct ca_data *data, unsigned int index) {
    if (data == NULL) error("NULL data argument", 1);
    if (index < 0 || index > data->length - 1) {
        if (data->wrap) {
            if (index < 0) return data->cells[data->length + (index % data->length)];
            return data->cells[index % data->length];
        }
        return data->intialState;
    }
    return data->cells[index];
}

/**
 * This function outputs the current state of the 1DCA. Each cell state is separated by 
 * a space and terminated with an end of line character (\n)..
**/
void display1DCA(struct ca_data *data) {
    if (data == NULL) error("NULL data argument", 1);
    for (int i = 0; i < data->length; i++) {
        printf("%c ", data->cells[i]);  // print the value at arr with space
    }
    printf("\n");
}

/**
 * Performs one step of the 1DCA given by the first parameter.  
 * The rule for how to perform the step is given in by the second parameter
**/
void stepCA(struct ca_data *data, unsigned char (*func)(struct ca_data *d, int index), int flag) {
    if (data == NULL) error("NULL data argument", 1);
    unsigned char *nextStep = malloc(data->length * sizeof(unsigned char));
    if (nextStep == NULL) error("Failed to initialize nextStep", 1);
    for (int i = 0; i < data->length; i++) {
        nextStep[i] = func(data, i);
    }
    free(data->cells);
    data->cells = nextStep;
}

/**
 * Validates the command line arguments of main.c
**/
int validArgs(char *argv[]) {
    int numCells = atoi(argv[1]);
    int numStates = atoi(argv[2]);
    int initState = atoi(argv[4]);
    int numSteps = atoi(argv[5]);
    if (numCells < MIN_CELLS || numCells > MAX_CELLS) error("Invalid number of cells argument", 1);
    if (strcmp(argv[3], "wrap") != 0 && strcmp(argv[3], "nowrap") != 0) error("Invalid wrap argument", 1);
    if (initState < -1 || initState > numStates - 1) error("Invalid initial state argument", 1);
    return 1;
}

void error(char* message, int code) {
    fprintf(stderr, "\n%s\n", message);
    exit(code);
}