ocda:	ca.c ca.h main.c 
	gcc ca.c main.c -o odca -I.
	./odca 10 2 wrap -1 10
