#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;

#include "CellularAutomaton.h"
#include "GraphicsClient.h"
#include "Message.h"

// Print to std::cerr and exit program
void error(string s, int code) {
    cerr << s << endl;
    exit(code);
}

// CA constructor
CellularAutomaton::CellularAutomaton(string file, int qstate) {
    this->qstate = qstate;
    this->running = 0;
    char data[100];
    int w, h;
    // read from given file
    ifstream infile;
    infile.open(file);
    infile >> h;
    infile >> w;
    if (h <= 0 || w <= 0) error("Invalid height and/or width", 1);
    width = w;
    height = h;
    cadata = new unsigned char*[h];
    cadataInitial = new unsigned char*[h];
    for (int i = 0; i < h; ++i) {
        cadata[i] = new unsigned char[w];
        cadataInitial[i] = new unsigned char[w];
    }
    if (cadata == NULL) error("Failed to initialize c->cadata", 1);
    if (cadataInitial == NULL) error("Failed to initialize c->cadata", 1);
    // read in the initial state from file
    unsigned char state = -1;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            infile >> state;
            cadata[i][j] = state;
            cadataInitial[i][j] = state;
        }
    }
}

// CA copy constructor
CellularAutomaton::CellularAutomaton(const CellularAutomaton& origCellularAutomaton) {
    // allocate new space
    cadata = new unsigned char*[origCellularAutomaton.height];
    cadataInitial = new unsigned char*[origCellularAutomaton.height];
    for (int i = 0; i < origCellularAutomaton.height; ++i) {
        cadata[i] = new unsigned char[origCellularAutomaton.width];
        cadataInitial[i] = new unsigned char[origCellularAutomaton.width];
    }
    *cadata = *(origCellularAutomaton.cadata);
    *cadataInitial = *(origCellularAutomaton.cadataInitial);
}

// CA deconstructor
CellularAutomaton::~CellularAutomaton() {
    for (int i = 0; i < height; ++i) {
        delete cadata[i];
        delete cadataInitial[i];
    }
    delete cadata;
    delete cadataInitial;
}

// CA operator= method
CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& objToCopy) {
    if (this != &objToCopy) {
        for (int i = 0; i < height; ++i) {
            delete cadata[i];
            delete cadataInitial[i];
        }
        delete cadata;
        delete cadataInitial;
        cadata = new unsigned char*[objToCopy.height];
        cadataInitial = new unsigned char*[objToCopy.height];
        for (int i = 0; i < objToCopy.height; ++i) {
            cadata[i] = new unsigned char[objToCopy.width];
            cadataInitial[i] = new unsigned char[objToCopy.width];
        }
        **cadata = **(objToCopy.cadata);
        **cadataInitial = **(objToCopy.cadataInitial);
        height = objToCopy.height;
        width = objToCopy.width;
        qstate = objToCopy.qstate;
        running = objToCopy.running;
    }
    return *this;
}

// Preforms a step for the 2DCA given a rule
void CellularAutomaton::step(unsigned char (*rule)(CellularAutomaton& ca, int x, int y)) {
    unsigned char** newcadata = new unsigned char*[height];  // create a new data array
    for (int i = 0; i < height; ++i)
        newcadata[i] = new unsigned char[width];
    if (newcadata == NULL) error("Failed to initialize c->cadata", 1);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            newcadata[i][j] = rule(*this, j, i);  // apply rule to each index
        }
    }
    for (int i = 0; i < height; ++i)  // delete old data
        delete cadata[i];
    delete cadata;
    cadata = newcadata;  // set new data
}

// Displays the current state in the GraphicsClient
void CellularAutomaton::display(GraphicsClient& gc) {
    int max = std::max(width, height);
    int cellWidth = 0;
    int cellGap = 0;
    int x, y;
    // set the gaps and margins
    if (max > 1 && max <= 50) {
        cellWidth = 10;
        cellGap = 2;
    } else if (max > 50 && max <= 100) {
        cellWidth = 4;
        cellGap = 1;
    } else if (max > 100 && max <= 200) {
        cellWidth = 2;
        cellGap = 1;
    } else if (max > 200 && max <= 600) {
        cellWidth = 1;
        cellGap = 0;
    }
    // display each cell
    gc.setDrawingColor(214, 217, 223);
    gc.fillRectangle(0, 0, 600, 600);
    gc.setDrawingColor(250, 250, 250);
    gc.fillRectangle(0, 0, (cellWidth + cellGap) * width, (cellWidth + cellGap) * height);
    gc.setDrawingColor(100, 30, 210);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cadata[i][j] == '1') {
                x = (j * cellWidth) + (j * cellGap);
                y = (i * cellWidth) + (i * cellGap);
                gc.fillRectangle(x, y, cellWidth, cellWidth);
            }
        }
    }
    string runningStatus = running ? "Running" : "Paused";
    string status = runningStatus + ", width: " + to_string(width) + ", height: " + to_string(height);
    gc.setDrawingColor(214, 217, 223);
    gc.fillRectangle(625, 575, 200, 30);
    gc.setDrawingColor(0, 0, 0);
    gc.drawString(625, 595, status);
    gc.repaint();  // refresh display
}

// Get a cell at position x, y (accounts for wrapping)
unsigned char CellularAutomaton::getCell(int x, int y) {
    int xToGet = x;  // x index I want to return
    int yToGet = y;  // y index I want to return
    // adjust x and y for wrapping
    if (x < 0) {
        xToGet = width + (x % width);
    } else if (x > width - 1) {
        xToGet = x % width;
    }
    if (y < 0) {
        yToGet = height + (y % height);
    } else if (y > height - 1) {
        yToGet = y % height;
    }
    return cadata[yToGet][xToGet];  // in bounds
}

// Set a cell at position x, y to c
void CellularAutomaton::setCell(int x, int y, unsigned char c) {
    if (x < 0 || x > width - 1) error("Invalid x argument", 1);
    if (y < 0 || y > height - 1) error("Invalid y argument", 1);
    cadata[y][x] = c;  // set value
}

// Set running to r
void CellularAutomaton::setRunning(int r) {
    running = r;
}

// Returns running
int CellularAutomaton::getRunning() {
    return running;
}

// Resets ca to initial state
void CellularAutomaton::reset() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cadata[i][j] = cadataInitial[i][j];
        }
    }
}

// Resets ca to 0
void CellularAutomaton::clear() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cadata[i][j] = '0';
        }
    }
}

// Sets ca to random state
void CellularAutomaton::random() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (rand() % 5 == 0) {
                cadata[i][j] = '1';
                cadataInitial[i][j] = '1';
            } else {
                cadata[i][j] = '0';
                cadataInitial[i][j] = '0';
            }
        }
    }
}

// Toggles the state of a cell given mouse coordinates
void CellularAutomaton::toggleCell(int mx, int my) {
    int max = std::max(height, width);
    int cellWidth = 0;
    int cellGap = 0;
    if (max > 1 && max <= 50) {
        cellWidth = 10;
        cellGap = 2;
    } else if (max > 50 && max <= 100) {
        cellWidth = 4;
        cellGap = 1;
    } else if (max > 100 && max <= 200) {
        cellWidth = 2;
        cellGap = 1;
    } else if (max > 200 && max <= 600) {
        cellWidth = 1;
        cellGap = 0;
    }
    int cellX = mx / (cellWidth + cellGap);
    int cellY = my / (cellWidth + cellGap);
    if (cellY < height && cellX < width) {
        cout << "Toggling cell: (" << cellX << ", " << cellY << ")" << endl;
        unsigned char cur = getCell(cellX, cellY);
        if (cur == '0') setCell(cellX, cellY, '1');
        if (cur == '1') setCell(cellX, cellY, '0');
    }
}