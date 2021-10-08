ocda:	ca.c ca.h main.c 
	gcc ca.c main.c -o odca -I.
	./odca 20 2 nowrap 1 30
