#include <stdio.h>
#include <stdlib.h>
#include <dca1d.h>

int main() {
    int n = 25;
    unsigned char a[n];
    init1DCA(n, a); // initialize the 1DCA
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) { // set the even indices to '2'
            set1DCACell(a, i, '2');
        } else { // set the odds to '1'
            set1DCACell(a, i, '1');
        }
    }
    display1DCA(a, n); // display the 1DCA to the console
    return 0;
}

/**
 * This function initializes a one-dimensional cellular automaton to 
 * the quiescent, all zero state. The 1DCA is stored as an array of unsigned char type.
**/
void init1DCA(int numberOfCells, unsigned char* arr) {
    for (int i = 0; i < numberOfCells; i++) {
        *arr = '0'; // initialize to '0';
        arr++; // update pointer to next index
    }
}

/**
 * This function allows the client to set the specified cell to a specified state.
**/
void set1DCACell(unsigned char* arr, int index, unsigned char value) {
    if (index < 0) return;
    arr += index; // update pointer to given index
    *arr = value; // set value
}

/**
 * This function outputs the current state of the 1DCA. Each cell state is separated by 
 * a space and terminated with an end of line character (\n)..
**/
void display1DCA(unsigned char* arr, int numberOfCells) {
    for (int i = 0; i < numberOfCells; i++) {
        printf("%c ", *arr); // print the value at arr with space
        arr++;
    }
    printf("\n");
}
