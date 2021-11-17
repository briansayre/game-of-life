# Project 2A - Brian Sayre
 This program allows the client to simulate a two-dimensional cellular automaton and display each generation of the 2DCA using the CellularAutomaton C++ class, the GraphicsClient C++ class, and the GraphicsServer.jar file.

## Compiling and running main.cpp
1. In the project's root directory run the following command:  
```$ java -jar GraphicsServer.jar```  
This will start the graphics server on port 7777 on localhost.

2. Now we will compile and run main.cpp using the following command:  
```$ make```    
That will start a 2DCA simulation window. To change the initial state/file to read from change the file name on line 3 of the make file.  
  
Each time the user presses the return key, another step of the CA is displayed.  If the user types any character followed by a return key, the simulation stops, the display is disconnected, and the program terminates. 