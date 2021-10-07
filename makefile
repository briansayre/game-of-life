ocda:	ca.c ca.h main.c 
	gcc ca.c main.c -o odca -I.
	# numCells numStates wrap initValue steps
	./odca 10 2 wrap 0 10
