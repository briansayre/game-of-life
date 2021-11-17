#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "CellularAutomaton.h"
#include "GraphicsClient.h"

using namespace std;

unsigned char gameOfLife(CellularAutomaton& ca, int x, int y) {
    int liveNeighbors = (int)ca.getCell(x - 1, y - 1) + (int)ca.getCell(x, y - 1) + (int)ca.getCell(x + 1, y - 1) - 144;
    liveNeighbors += (int)ca.getCell(x - 1, y) + ((int)ca.getCell(x + 1, y)) - 96;
    liveNeighbors += (int)ca.getCell(x - 1, y + 1) + (int)ca.getCell(x, y + 1) + (int)ca.getCell(x + 1, y + 1) - 144;
    int alive = ((int)ca.getCell(x, y) - 48);
    if (alive && liveNeighbors < 2) return '0';
    if (alive && (liveNeighbors == 2 || liveNeighbors == 3)) return '1';
    if (alive && liveNeighbors > 3) return '0';
    if (!alive && liveNeighbors == 3) return '1';
    return '0';
}

int main(int argc, char* argv[]) {
    if (argc != 2) exit(1);
    GraphicsClient gc = GraphicsClient("127.0.0.1", 7777);
    gc.setBackgroundColor(30, 30, 30);
    gc.setDrawingColor(240, 240, 240);
    gc.clear();
    gc.repaint();
    CellularAutomaton ca = CellularAutomaton(argv[1], 0);
    ca.display(gc);
    string input = "";
    while (input == "") {
        getline(cin, input);
        ca.step(gameOfLife);
        ca.display(gc);
    }
}
