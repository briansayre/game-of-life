#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ca.h"

unsigned char rule110(struct ca_data *d, int i);
unsigned char rule30(struct ca_data *d, int i);
unsigned char rule54(struct ca_data *d, int i);
unsigned char rule(struct ca_data *d, int i, char *r);

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

    free(c->cells);
    free(c);
    return 0;
}

unsigned char rule110(struct ca_data *d, int i) { return rule(d, i, "01101110"); }
unsigned char rule30(struct ca_data *d, int i) { return rule(d, i, "00011110"); }
unsigned char rule54(struct ca_data *d, int i) { return rule(d, i, "00110110"); }

unsigned char rule(struct ca_data *d, int i, char *r) {
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '1') return r[0];
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '0') return r[1];
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '1') return r[2];
    if (get1DCACell(d, i - 1) == '1' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '0') return r[3];
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '1') return r[4];
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '1' && get1DCACell(d, i + 1) == '0') return r[5];
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '1') return r[6];
    if (get1DCACell(d, i - 1) == '0' && get1DCACell(d, i) == '0' && get1DCACell(d, i + 1) == '0') return r[7];
    return '*';
}