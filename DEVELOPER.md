# Developer

## ca.c

### void init1DCA( struct ca_data *data, int value)
This function initializes a one-dimensional cellular 
automaton to the quiescent, all zero state. The 1DCA is stored as an array of unsigned char type.  
##### Parameters:  
data - Pointer to a ca_data struct.  
value - Value to be initialized to.    
  
### int set1DCACell(struct ca_data *data, unsigned int index, unsigned char value)
This function allows the client to set the specified cell to a specified state.  
##### Parameters:  
data - Pointer to a ca_data struct.  
index - Index of the element you wish to be set.   
value - The value that will be set at the given index.   

### unsigned char get1DCACell(struct ca_data *data, unsigned int index)
Gets the value of the CA given an index
##### Parameters:  
data - Pointer to a ca_data struct.  
index - Index of the element you wish to be set.  

### void display1DCA(struct ca_data *data)
This function outputs the current state of the 1DCA. Each cell state is separated by a space and terminated with an end of line character (\n).  
##### Parameters:    
data - Pointer to a ca_data struct.  
  
### struct ca_data* create1DCA( int length, unsigned char value)
The return value is a pointer to a ca_data structure initialized as such  
##### Parameters:    
length - Length of the 1DCA  
value - Value to be initialized to.  

### void stepCA(struct ca_data \*data, unsigned char (*func)(struct ca_data *d, int index), int flag)
Performs one step of the 1DCA given by the first parameter. The rule for how to perform the step is given in by the second parameter
##### Parameters:    
data - Pointer to a ca_data struct.  
func - Rule to be applied to the CA  
flag - Flag for wrapping the indices or not  

### int validArgs(char *argv[])
Validates the command line arguments of main.c
##### Parameters:    
argv - Command line arguments

### void error(char* message, int code)
Displays error messages and exits program.
##### Parameters:    
message - Message to be displayed  
code - Exit code to be used for the program  