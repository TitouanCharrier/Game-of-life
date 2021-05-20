PROG := main
CC := gcc
CFLAGS := -Wall -Wextra -g -O -std=c99 
CFLAGS += $(shell pkg-config --cflags SDL2_ttf)
LDFLAGS := $(shell pkg-config --libs SDL2_ttf)

all: $(PROG)

$(PROG): gol.o gol_gui.o main.o
	$(CC) -o $@ $^ $(LDFLAGS)

gol.o: src/game_of_life.c src/game_of_life.h src/struct.h src/game_of_life_gui.h
	$(CC) -c -o $@ $< $(CFLAGS)

gol_gui.o: src/game_of_life_gui.c src/game_of_life_gui.h src/struct.h 
	$(CC) -c -o $@ $< $(CFLAGS)

main.o: main.c src/game_of_life_gui.h src/struct.h 
	$(CC) -c -o $@ $< $(CFLAGS)

clean: 
	rm *.o $(PROG)