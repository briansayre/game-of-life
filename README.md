# Project 1B - Brian Sayre
 This program allows the client to initialize a one-dimensional cellular automaton, set values in the 1DCA, and display the 1DCA on the console, and apply rules to the 1DCA.  
 
## Compiling and running main.c
In the project's root directory run the following command:  
```$ make```  
Expected output:  
```
gcc ca.c main.c -o odca -I.
./odca 10 2 wrap 0 10
0 0 0 0 0 0 0 0 0 1
0 0 0 0 0 0 0 0 1 1
0 0 0 0 0 0 0 1 1 1
0 0 0 0 0 0 1 1 0 1
0 0 0 0 0 1 1 1 1 1
0 0 0 0 1 1 0 0 0 1
0 0 0 1 1 1 0 0 1 1
0 0 1 1 0 1 0 1 1 1
0 1 1 1 1 1 1 1 0 1
1 1 0 0 0 0 0 1 1 1
```