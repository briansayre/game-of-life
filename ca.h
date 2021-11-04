#pragma once

struct ca_data {
    int height;
    int width;
    unsigned char wrap;
    unsigned char qstate;
    unsigned char dimension;
    unsigned char **cadata;
};

/**
 *  Allocates space and creates a pointer for the CA
**/
struct ca_data *create1DCA( int w, unsigned char qstate);

/**
 *  Allocates space and creates a pointer for the CA
**/
struct ca_data *create2DCA( int w, int h, unsigned char qstate); 

/**
 * This function initializes a cellular automaton to 
 * the quiescent, all zero state. The CA is stored as an array of unsigned char type.
**/
void initCA( struct ca_data *ca, int state );

/**
 * This function allows the client to set the specified cell to a specified state.
**/
int set1DCACell( struct ca_data *ca, unsigned int x, unsigned char state); 

/**
 * This function allows the client to set the specified cell to a specified state.
**/
int set2DCACell( struct ca_data *ca, unsigned int x, unsigned int y, unsigned char state);

/**
 * Gets the value of the 1DCA given an index.
**/
unsigned char get1DCACell(struct ca_data *ca, int x);

/**
 * Gets the value of the 2DCA given an index.
**/
unsigned char get2DCACell(struct ca_data *ca, int x, int y);


/**
 * This function outputs the current state of the CA. Each cell state is separated by 
 * a space and terminated with an end of line character (\n)..
**/
void displayCA( struct ca_data *ca );

/**
 * Performs one step of the 1DCA given by the first parameter.  
 * The rule for how to perform the step is given in by the second parameter
**/
void step1DCA( struct ca_data *ca, unsigned char (*rule)(struct ca_data *ca, int x));

/**
 * Performs one step of the 2DCA given by the first parameter.  
 * The rule for how to perform the step is given in by the second parameter
**/
void step2DCA( struct ca_data *ca, unsigned char (*rule)(struct ca_data *ca, int x, int y));

/** 
 * Displays error messages and exits program.
**/
void error(char *message, int code);
