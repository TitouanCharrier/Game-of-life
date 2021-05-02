main : main.c src/mainfunc.c src/mainfunc.h 
	gcc -c src/mainfunc.c -o mainfunc.o -lSDL2 -lSDL2_ttf
	gcc main.c -o main mainfunc.o -lSDL2 -lm -lSDL2_ttf
	rm mainfunc.o
	./main