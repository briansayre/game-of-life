#pragma once

/**
 * This function initializes a one-dimensional cellular automaton to 
 * the quiescent, all zero state. The 1DCA is stored as an array of unsigned char type.
**/
void init1DCA(int numberOfCells, unsigned char* p);

/**
 * This function allows the client to set the specified cell to a specified state.
**/
void set1DCACell(unsigned char* arr, int index, unsigned char value);

/**
 * This function outputs the current state of the 1DCA. Each cell state is separated by 
 * a space and terminated with an end of line character (\n)..
**/
void display1DCA(unsigned char* arr, int numberOfCells);
