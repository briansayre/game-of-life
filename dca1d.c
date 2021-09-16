#include <stdio.h>
#include <stdlib.h>
#include <dca1d.h>

void main() {
    int n = 25;
    unsigned char a[n];
    init1DCA(n, a);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            set1DCACell(a, i, '2');
        } else {
            set1DCACell(a, i, '1');
        }
    }
    display1DCA(a, n);
}

void init1DCA(int numberOfCells, unsigned char* arr) {
    for (int i = 0; i < numberOfCells; i++) {
        *arr = '0';
        arr++;
    }
}

void set1DCACell(unsigned char* arr, int index, unsigned char value) {
    if (index < 0) return;
    arr += index;
    *arr = value;
}

void display1DCA(unsigned char* arr, int numberOfCells) {
    for (int i = 0; i < numberOfCells; i++) {
        printf("%c ", *arr);
        arr++;
    }
    printf("\n");
}