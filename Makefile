main : main.c lib/chained.h lib/chained_array.c src/mainfunc.c src/mainfunc.h lib/geometrie_SDL2.c lib/geometrie_SDL2.h
	gcc -c lib/geometrie_SDL2.c -o geometrie.o -lSDL2 -lm
	gcc -c lib/chained_array.c -o chained.o
	gcc -c src/mainfunc.c -o mainfunc.o -lSDL2
	gcc main.c -o main chained.o mainfunc.o geometrie.o -lSDL2 -lm
	rm chained.o mainfunc.o
	./main