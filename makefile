CFLAGS = -O
CC = g++
FILE = 50by50.txt

all:	casimulator.o GraphicsClient.o CellularAutomaton.o Message.o
	$(CC) $(CFLAGS) -o casimulator.out casimulator.o GraphicsClient.o CellularAutomaton.o Message.o
	./casimulator.out $(FILE)

casimulator.o:	casimulator.cpp
	$(CC) $(CFLAGS) -c casimulator.cpp

GraphicsClient.o:	GraphicsClient.cpp
	$(CC) $(CFLAGS) -c GraphicsClient.cpp

CellularAutomaton.o:	CellularAutomaton.cpp
	$(CC) $(CFLAGS) -c CellularAutomaton.cpp
	
Message.o:	Message.cpp
	$(CC) $(CFLAGS) -c Message.cpp

clean:	
	rm -f core *.o*