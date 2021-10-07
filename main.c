#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ca.h"

unsigned char rule110(struct ca_data *d, int i) {
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '1') return '0';
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '0') return '1';
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '1') return '1';
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '0') return '0';
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '1') return '1';
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '0') return '1';
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '1') return '1';
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '0') return '0';
    return '*';
}

unsigned char rule30(struct ca_data *d, int i) {
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '1') return '0';
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '0') return '0';
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '1') return '0';
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '0') return '1';
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '1') return '1';
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '0') return '1';
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '1') return '1';
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '0') return '0';
    return '*';
}

int main(int argc, char *argv[]) {
    if (argc != 6) return -1;
    if (!validArgs(argv)) return -1;

    int numCells = atoi(argv[1]);
    int numStates = atoi(argv[2]);
    int initState = atoi(argv[4]);
    int numSteps = atoi(argv[5]);

    struct ca_data *c = create1DCA(numCells, *argv[4]);
    c->numStates = numStates;
    c->wrap = (strcmp(argv[3], "wrap") == 0);

    init1DCA(c, initState);
    //set1DCACell(c, 9, '1');

    for (int i = 0; i < numSteps; i++) {
        display1DCA(c);
        stepCA(c, rule110, c->wrap);
    }

    return 0;
}
