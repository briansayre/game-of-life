#include "ca.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CHAR_INT_OFFSET 48


/**
 *  Allocates space and creates a pointer for the CA
**/
struct ca_data *create1DCA( int w, unsigned char qstate) {
    struct ca_data *c = malloc(sizeof(struct ca_data));
    if (c == NULL) error("Failed to initialize ca_data struct", 1);
    c->cadata = malloc(w * sizeof(unsigned char));
    if (c->cadata == NULL) error("Failed to initialize c->cadata", 1);
    c->width = w;
    c->height = -1;
    c->qstate = qstate;
    c->wrap = '1';
    c->dimension = '1';
    initCA(c, qstate);
    return c;
}

/**
 *  Allocates space and creates a pointer for the CA
**/
struct ca_data *create2DCA( int w, int h, unsigned char qstate) {
    struct ca_data *c = (struct ca_data *)malloc(sizeof(struct ca_data));
    if (c == NULL) error("Failed to initialize ca_data struct", 1);
    c->cadata = malloc(h * sizeof(char *)); // Allocate row pointers
    for(int i = 0; i < h; i++)
        c->cadata[i] = malloc(w * sizeof(unsigned char));  // Allocate each row separately
    if (c->cadata == NULL) error("Failed to initialize c->cadata", 1);
    c->width = w;
    c->height = h;
    c->qstate = qstate;
    c->wrap = '1';
    c->dimension = '2';
    initCA(c, qstate - CHAR_INT_OFFSET);
    return c;
}

/**
 * This function initializes a cellular automaton to 
 * the quiescent, all zero state. The CA is stored as an array of unsigned char type.
**/
void initCA( struct ca_data *ca, int state ) {
    if (ca == NULL) error("NULL data argument", 1);
    for (int i = 0; i < ca->height; i++) {
        for (int j = 0; j < ca->width; j++) {
            // set all to qstate
            ca->cadata[i][j] =  state + CHAR_INT_OFFSET;
        }
    }
}


/**
 * This function allows the client to set the specified cell to a specified state.
**/
int set1DCACell( struct ca_data *ca, unsigned int x, unsigned char state) {
    if (ca == NULL) error("NULL data argument", 1);
    if (x < 0 || x > ca->width - 1) error("Invalid index argument", 1);
    ca->cadata[0][x] = state;  // set value
    return 1;
}

/**
 * This function allows the client to set the specified cell to a specified state.
**/
int set2DCACell( struct ca_data *ca, unsigned int x, unsigned int y, unsigned char state) {
    if (ca == NULL) error("NULL data argument", 1);
    if (x < 0 || x > ca->width - 1) error("Invalid x argument", 1);
    if (y < 0 || y > ca->height - 1) error("Invalid y argument", 1);
    ca->cadata[y][x] = state;  // set value
    return 1;
}

/**
 * Gets the value of the 1DCA given an index.
**/
unsigned char get1DCACell(struct ca_data *ca, int x) {
    if (ca == NULL) error("NULL data argument", 1);
    if (x < 0 || x > ca->width - 1) {
        if (x < 0) return ca->cadata[0][ca->width + (x % ca->width)];
        return ca->cadata[0][x % ca->width];
    }
    return ca->cadata[0][x];  // in bounds
}

/**
 * Gets the value of the 2DCA given an index.
**/
unsigned char get2DCACell(struct ca_data *ca, int x, int y) {
    if (ca == NULL) error("NULL data argument", 1);
    unsigned int xToGet = x; // x index I want to return
    unsigned int yToGet = y; // y index I want to return
    // adjust x and y for wrapping
    if (x < 0) {
        xToGet = ca->width + (x % ca->width);
    } else if (x > ca->width - 1){
        xToGet = x % ca->width;
    }
    if (y < 0) {
        yToGet = ca->height + (y % ca->height);
    } else if (y > ca->height - 1){
        yToGet = y % ca->height;
    }
    return ca->cadata[yToGet][xToGet];  // in bounds
}

/**
 * This function outputs the current state of the 1DCA. Each cell state is separated by 
 * a space and terminated with an end of line character (\n).
**/
void displayCA( struct ca_data *ca ) { 
    int blocks = 0;
    if (ca == NULL) error("NULL data argument", 1);
    for (int i = 0; i < ca->height; i++) {
        for (int j = 0; j < ca->width; j++) {
            if (blocks) {  // prints using blocks for better visualization
                if (ca->cadata[i][j] == '0') {
                    printf("  ");
                } else {
                    printf("■ ");
                }
            } else {  // prints the state normally
                printf("%c ", ca->cadata[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
    fflush(stdout);
}

/**
 * Performs one step of the 1DCA given by the first parameter.  
 * The rule for how to perform the step is given in by the second parameter
**/
void step1DCA( struct ca_data *ca, unsigned char (*rule)(struct ca_data *ca, int x)) {
    if (ca == NULL) error("NULL data argument", 1);
    unsigned char *nextStep = malloc(ca->width * sizeof(unsigned char));  // the next step of cadata
    if (nextStep == NULL) error("Failed to initialize nextStep", 1);
    for (int i = 0; i < ca->width; i++) {
        nextStep[i] = rule(ca, i);
    }
    free(ca->cadata);  // free old cadata
    ca->cadata[0] = nextStep;
}

/**
 * Performs one step of the 2DCA given by the first parameter.  
 * The rule for how to perform the step is given in by the second parameter
**/
void step2DCA( struct ca_data *ca, unsigned char (*rule)(struct ca_data *ca, int x, int y)) {
    if (ca == NULL) error("NULL data argument", 1);
    unsigned char **nextStep = malloc(ca->height * sizeof(char *)); // Allocate row pointers
    for(int i = 0; i < ca->height; i++)
        nextStep[i] = malloc(ca->width * sizeof(unsigned char));  // Allocate each row separately
    if (nextStep == NULL) error("Failed to initialize nextStep", 1);
    for (int i = 0; i < ca->height; i++) {
        for (int j = 0; j < ca->width; j++) {
            nextStep[i][j] = rule(ca, j, i); // apply rule to each index
        }
    }
    // free old cadata
    for(int i = 0; i < ca->height; i++)
        free(ca->cadata[i]); 
    free(ca->cadata);
    ca->cadata = nextStep;
}

/** 
 * Displays error messages and exits program.
**/
void error(char *message, int code) {
    fprintf(stderr, "\n%s\n", message);
    exit(code);
}