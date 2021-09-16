# Developer

## dca1d.c

### void init1DCA(int numberOfCells, unsigned char* arr)  
This function initializes a one-dimensional cellular 
automaton to the quiescent, all zero state. The 1DCA is stored as an array of unsigned char type.  
##### Parameters:  
numberOfCells - Number of cells in the array.  
arr - Pointer to the first element of the array.  
  
### void set1DCACell(unsigned char* arr, int index, unsigned char value)
This function allows the client to set the specified cell to a specified state.  
##### Parameters:  
arr - Pointer to the first element of the array.  
index - Index of the element you wish to be set.  
value - The value that will be set at the given index.  

### void display1DCA(unsigned char* arr, int numberOfCells) 
This function outputs the current state of the 1DCA. Each cell state is separated by a space and terminated with an end of line character (\n).  
##### Parameters:    
arr - Pointer to the first element of the array.  
numberOfCells - Number of cells in the array.  