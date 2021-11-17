CFLAGS = -O
CC = g++
FILE = 50by50.txt

all:	main.o GraphicsClient.o CellularAutomaton.o
	$(CC) $(CFLAGS) -o main.out main.o GraphicsClient.o CellularAutomaton.o
	./main.out $(FILE)

main.o:	main.cpp
	$(CC) $(CFLAGS) -c main.cpp

GraphicsClient.o:	GraphicsClient.cpp
	$(CC) $(CFLAGS) -c GraphicsClient.cpp

CellularAutomaton.o:	CellularAutomaton.cpp
	$(CC) $(CFLAGS) -c CellularAutomaton.cpp

clean:	
	rm -f core *.o*