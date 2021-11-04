

# Developer
  
## ca.c
  
### void initCA( struct ca_data *ca, int state )
This function initializes a cellular automaton to 
the quiescent, all zero state. The CA is stored as an array of unsigned char type.
  
### int set1DCACell( struct ca_data *ca, unsigned int x, unsigned char state)
This function allows the client to set the specified cell to a specified state.  
  
### set2DCACell( struct ca_data *ca, unsigned int x, unsigned int y, unsigned char state)
This function allows the client to set the specified cell to a specified state.  
  
### unsigned char get1DCACell(struct ca_data *ca, int x)
Gets the value of the 1DCA given an index.
  
### unsigned char get2DCACell(struct ca_data *ca, int x, int y)
Gets the value of the 1DCA given an index.
  
### void displayCA( struct ca_data *ca )
This function outputs the current state of the CA. Each cell state is separated by 
a space and terminated with an end of line character (\n). 

### struct ca_data *create1DCA( int w, unsigned char qstate)
Allocates space and creates a pointer for the CA 
  
### struct ca_data *create2DCA( int w, int h, unsigned char qstate)
Allocates space and creates a pointer for the CA 
  
### void step1DCA( struct ca_data *ca, unsigned char (*rule)(struct ca_data *ca, int x))
Performs one step of the 1DCA given by the first parameter. The rule for how to perform the step is given in by the second parameter
  
### void step2DCA( struct ca_data *ca, unsigned char (*rule)(struct ca_data *ca, int x, int y))
Performs one step of the 2DCA given by the first parameter. The rule for how to perform the step is given in by the second parameter
  
### void error(char* message, int code)
Displays error messages and exits program.