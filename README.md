# Project 1C - Brian Sayre
 This program allows the client to initialize a two-dimensional cellular automaton, set values in the 2DCA, and display the 2DCA on the console, and apply rules to the 2DCA to implement Conway's Game of Life.  

## Compiling and running main.c
In the project's root directory run the following command:  
```$ make```  
Expected output:  
```
gcc ca.c main.c -o gol -I.
./gol 2 glider.txt
0 0 0 0 0 0 0 0 0 0 
0 1 0 1 0 0 0 0 0 0 
0 0 1 1 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 


0 0 0 0 0 0 0 0 0 0 
0 0 0 1 0 0 0 0 0 0 
0 1 0 1 0 0 0 0 0 0 
0 0 1 1 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 


0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 
0 0 0 1 1 0 0 0 0 0 
0 0 1 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0


0 0 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0 
0 0 0 0 1 0 0 0 0 0
0 0 1 1 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0


0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 
0 0 1 0 1 0 0 0 0 0
0 0 0 1 1 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0

q
```