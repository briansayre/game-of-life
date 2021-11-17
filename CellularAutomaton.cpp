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

// Print to std::cerr and exit program
void error(string s, int code) {
    cerr << s << endl;
    exit(code);
}

// CA constructor
CellularAutomaton::CellularAutomaton(string file, int qstate) {
    this->qstate = qstate;
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
    for (int i = 0; i < h; ++i)
        cadata[i] = new unsigned char[w];
    if (cadata == NULL) error("Failed to initialize c->cadata", 1);
    // read in the initial state from file
    unsigned char state = -1;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            infile >> state;
            cadata[i][j] = state;
        }
    }
}

// CA copy constructor
CellularAutomaton::CellularAutomaton(const CellularAutomaton& origCellularAutomaton) {
    // allocate new space
    cadata = new unsigned char*[origCellularAutomaton.height];
    for (int i = 0; i < origCellularAutomaton.height; ++i)
        cadata[i] = new unsigned char[origCellularAutomaton.width];
    *cadata = *(origCellularAutomaton.cadata);
}

// CA deconstructor
CellularAutomaton::~CellularAutomaton() {
    for (int i = 0; i < height; ++i)
        delete cadata[i];
    delete cadata;
}

// CA operator= method
CellularAutomaton& CellularAutomaton::operator=(const CellularAutomaton& objToCopy) {
    if (this != &objToCopy) {
        for (int i = 0; i < height; ++i)
            delete cadata[i];
        delete cadata;
        cadata = new unsigned char*[objToCopy.height];
        for (int i = 0; i < objToCopy.height; ++i)
            cadata[i] = new unsigned char[objToCopy.width];
        **cadata = **(objToCopy.cadata);
        height = objToCopy.height;
        width = objToCopy.width;
        qstate = objToCopy.qstate;
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
    } else {
        error("Invalid height and/or width", 1);
    }
    // display each cell
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (cadata[i][j] == '0') {
                gc.setDrawingColor(250, 250, 250);
            } else {
                gc.setDrawingColor(50, 50, 250);
            }
            x = (j * cellWidth) + (j * cellGap);
            y = (i * cellWidth) + (i * cellGap);
            gc.fillRectangle(x, y, cellWidth, cellWidth);
        }
    }
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
