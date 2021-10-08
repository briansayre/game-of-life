#pragma once

struct ca_data {
    int length;
    int numStates;
    int wrap;
    unsigned char intialState;
    unsigned char *cells;
};

/**
 *  The return value is a pointer to a ca_data structure initialized as such
**/
struct ca_data *create1DCA(int length, unsigned char value);

/**
 * This function initializes a one-dimensional cellular automaton to 
 * the quiescent, all zero state. The 1DCA is stored as an array of unsigned char type.
**/
void init1DCA(struct ca_data *data, int value);

/**
 * This function allows the client to set the specified cell to a specified state.
**/
int set1DCACell(struct ca_data *data, unsigned int index, unsigned char value);

/**
 * Gets the value of the CA given an index.
**/
unsigned char get1DCACell(struct ca_data *data, unsigned int index);

/**
 * This function outputs the current state of the 1DCA. Each cell state is separated by 
 * a space and terminated with an end of line character (\n)..
**/
void display1DCA(struct ca_data *data);

/**
 * Performs one step of the 1DCA given by the first parameter.  
 * The rule for how to perform the step is given in by the second parameter
**/
void stepCA(struct ca_data *data, unsigned char (*func)(struct ca_data *d, int index), int flag);

/**
 * Validates the command line arguments of main.c
**/
int validArgs(char *argv[]);

/** 
 * Displays error messages and exits program.
**/
void error(char *message, int code);
