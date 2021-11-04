#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ca.h"

unsigned char gameOfLife(struct ca_data *ca, int x, int y);

int main(int argc, char *argv[]) {
    if (argc != 3) error("Incorrect number of arguments", 1);
    int dimension = atoi(argv[1]);
    if (dimension != 2) error("Unsupported dimensions", 1);;
    char* file = argv[2];
    int width, height;
    FILE* f = fopen(file, "r");
    if (f == NULL) error("Unable to open file", 1);;
    fscanf(f, "%d %d", &height, &width);

    // create the ca
    struct ca_data *c;
    if (dimension == 1) {
        c = create1DCA( width, '0');
    } else if (dimension == 2) {
        c = create2DCA( width, height, '0');
    }

    // read in the intial state
    unsigned char state = -1;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fscanf(f, " %c", &state);
            if (dimension == 1) {
                set1DCACell(c, j, state);
            } else if (dimension == 2) {
                set2DCACell(c, j, i, state);
            }
        }
    }

    // initial display
    displayCA(c);

    // step game of life while return is pressed
    char input = ' ';
    scanf("%c", &input);
    while (input == '\n') {
        step2DCA(c, gameOfLife);
        displayCA(c);
        scanf("%c", &input);
    }

    // free the memeory allocated
    for(int i = 0; i < height; i++)
        free(c->cadata[i]); 
    free(c->cadata);
    free(c);
    return 0;

}

/*
    GOL RULES:
    Any live cell with fewer than two live neighbours dies, as if by underpopulation.
    Any live cell with two or three live neighbours lives on to the next generation.
    Any live cell with more than three live neighbours dies, as if by overpopulation.
    Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/
unsigned char gameOfLife(struct ca_data *ca, int x, int y) {
    int liveNeighbors = ((int)get2DCACell(ca, x-1, y-1)-48)+((int)get2DCACell(ca, x, y-1)-48)+((int)get2DCACell(ca, x+1, y-1)-48);
    liveNeighbors += ((int)get2DCACell(ca, x-1, y)-48)+((int)get2DCACell(ca, x+1, y)-48);
    liveNeighbors += ((int)get2DCACell(ca, x-1, y+1)-48)+((int)get2DCACell(ca, x, y+1)-48)+((int)get2DCACell(ca, x+1, y+1)-48);
    int alive = ((int)ca->cadata[y][x]-48);
    if (alive && liveNeighbors < 2) return '0';
    if (alive && (liveNeighbors == 2 || liveNeighbors == 3)) return '1';
    if (alive && liveNeighbors > 3) return '0';
    if (!alive && liveNeighbors == 3) return '1';
    return '0';
}