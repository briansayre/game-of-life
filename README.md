# Project 2B - Brian Sayre
 This program allows the client to simulate a two-dimensional cellular automaton and display each generation of the 2DCA using the CellularAutomaton C++ class, the GraphicsClient C++ class, and the GraphicsServer.jar file.

## Compiling and running main.cpp
1. In the project's root directory run the following command:  
```$ java -jar GraphicsServer.jar```  
This will start the graphics server on port 7777 on localhost.

2. Now we will compile and run main.cpp using the following command:  
```$ make```    
That will start a 2DCA simulation window. To change the initial state/file to read from change the file name on line 3 of the make file.  
  
This program allows the user to:  
a. STEP.  Exceutes one step of the CA and displays the result.   
b. RUN. Continulously runs (steps) the CA at a rate of approximately 1 step every 100 ms.  (You may add a speed control for variable speed control if you wish.)   
c. PAUSE.  If the CA is in the run mode, the CA will stop running.   
d. QUIT. Terminites the and exits the program.   
e. RESET. Sets the state of the CA back to the initial state when it was loaded   
f. LOAD.  Uses a “file browser” to select a file to load.  (see additional messages in revised message format document)   
g. CLEAR.  Sets all the cells to state 0.   
h. RANDOMIZE.  Sets the cells in the CA to random initial states.  