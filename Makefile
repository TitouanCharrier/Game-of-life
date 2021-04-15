main : main.c lib/chained.h lib/chained_array.c
	gcc -c lib/chained_array.c -o chained.o
	gcc main.c -o main chained.o -lSDL2
	rm chained.o
	./main