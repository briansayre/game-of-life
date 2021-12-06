#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <iostream>

#include "CellularAutomaton.h"
#include "GraphicsClient.h"
#include "Message.h"

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
    GraphicsClient* gc = new GraphicsClient("127.0.0.1", 7777);
    CellularAutomaton* ca = new CellularAutomaton(argv[1], 0);
    struct timespec remaining, request = {0, 100000000};
    ca->display(*gc);

    while (1) {
        Message m = gc->readMessage();  // get message from server
        int function = m.getFunction();

        if (function == 0 && ca->getRunning() == 0) {  // step
            ca->step(gameOfLife);
        } else if (function == 1) {  // run
            ca->setRunning(1);
        } else if (function == 2) {  // pause
            ca->setRunning(0);
        } else if (function == 3) {  // reset
            ca->reset();
        } else if (function == 4) {  // random
            ca->random();
        } else if (function == 6) {  // quit
            break;
        } else if (function == 7) {  // 25 by 25
            ca = new CellularAutomaton("25by25.txt", 0);
        } else if (function == 8) {  // 50 by 50
            ca = new CellularAutomaton("50by50.txt", 0);
        } else if (function == 9) {  // 75 by 75
            ca = new CellularAutomaton("75by75.txt", 0);
        } else if (function == 10) {  // load
            ca = new CellularAutomaton(m.getFilePath(), 0);
        } else if (function == 11) {  // toggling cell on ca
            ca->toggleCell(m.getMouseX(), m.getMouseY());
        } else if (function == 12) {  // clear
            ca->clear();
        }

        if (ca->getRunning() == 1) {  // step if running
            ca->step(gameOfLife);
        }

        ca->display(*gc);
        nanosleep(&request, &remaining);  // sleep 100 ms
    }

    delete ca;
    delete gc;
}
