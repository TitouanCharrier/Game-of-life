main : main.c src/game_of_life.c src/game_of_life_gui.c 
	gcc -c src/game_of_life.c -o gol.o
	gcc -c src/game_of_life_gui.c -o gol_gui.o -lSDL2 -lSDL2_ttf 
	gcc main.c -o main gol_gui.o gol.o -lSDL2 -lm -lSDL2_ttf 
	rm gol_gui.o gol.o
	./main