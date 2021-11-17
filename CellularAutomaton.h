#pragma once

#include <string>

#include "GraphicsClient.h"
using namespace std;

/**
 * Class to simulate a 2D cellular automaton
 */
class CellularAutomaton {
   public:
    /**
     * CA constructor
     * @param file the file to be used as the initial state
     * @param qstate the initial state / default value
     */
    CellularAutomaton(string file, int qstate);

    /**
     * CA copy constructor
     * @param origCellularAutomaton original CA to be copied
     */
    CellularAutomaton(const CellularAutomaton& origCellularAutomaton);

    /**
     * CA deconstructor
     */
    ~CellularAutomaton();

    /**
     * CA operator= method
     * @param objToCopy the rhs object to copy
     * @param
     */
    CellularAutomaton& operator=(const CellularAutomaton& objToCopy);

    /**
     * Preforms a step for the 2DCA given a rule
     * @param rule rule function that calculates a cell's next state
     */
    void step(unsigned char (*rule)(CellularAutomaton& ca, int x, int y));

    /**
     * Displays the current state in the GraphicsClient
     * @param gc
     */
    void display(GraphicsClient& gc);

    /**
     * Get a cell at position x, y (accounts for wrapping)
     * @param x coordinate of cell
     * @param y coordinate of cell
     */
    unsigned char getCell(int x, int y);

    /**
     * Set a cell at position x, y to c
     * @param x coordinate of cell
     * @param y coordinate of cell
     * @param c value to set 
     */
    void setCell(int x, int y, unsigned char c);

   private:
    /**
     * Height of the 2DCA
     */
    int height;

    /**
     * Width of the 2DCA
     */
    int width;

    /**
     * Initial/default state
     */
    unsigned char qstate;

    /**
     * 2DCA data
     */
    unsigned char** cadata;
};
