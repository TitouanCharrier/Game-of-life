main : main.c lib/chained.h lib/chained_array.c src/mainfunc.c src/mainfunc.h
	gcc -c lib/chained_array.c -o chained.o
	gcc -c src/mainfunc.c -o mainfunc.o -lSDL2
	gcc main.c -o main chained.o mainfunc.o -lSDL2
	rm chained.o mainfunc.o
	./main