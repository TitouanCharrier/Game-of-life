#include "mainfunc.h"

Case **LoadCase(int NumberLine) {
    Case **ListCase = malloc(NumberLine*sizeof (*ListCase));
    assert(ListCase);
    for (int i = 0; i < NumberLine; i++) {
        ListCase[i] = malloc(sizeof *ListCase[i] * NumberLine);
        assert(ListCase[i]);
        for (int j = 0; j < NumberLine; j++) {
            ListCase[i][j].posx = j;
            ListCase[i][j].posy = i;
            ListCase[i][j].state = rand()%2;
        }
    }
    return ListCase;
}

void PrintScene(SDL_Renderer *renderer, Case **ListCase, location loc, int NumberLine) {

	SDL_SetRenderDrawColor(renderer, 100,100,100,255);
	SDL_RenderClear(renderer);

	for (int i=0; i<NumberLine; i++) {
		for (int j=0; j<NumberLine; j++) {
			
			if (ListCase[i][j].state ==1) {
				SDL_SetRenderDrawColor(renderer, 255,80,0,255);
			}
			else SDL_SetRenderDrawColor(renderer, 40,40,40,255);
			SDL_Rect RectCase = {(ListCase[i][j].posx+loc.locx-NumberLine/2)*(loc.scale+1),(ListCase[i][j].posy+loc.locy-NumberLine/2)*(loc.scale+1),loc.scale,loc.scale};
			SDL_RenderFillRect(renderer,&RectCase);
		}
	}
	SDL_RenderPresent(renderer);
}

void Life(Case **LC, int NumberLine) {
	
	int Neib;

	for (int i=0+2; i<NumberLine-1; i++) {
		for (int j=0+2; j<NumberLine-1; j++) {
			Neib = LC[i][j+1].state+LC[i][j-1].state
				+LC[i+1][j].state+LC[i-1][j].state+LC[i+1][j+1].state
				+LC[i-1][j+1].state+LC[i+1][j-1].state+LC[i-1][j-1].state;
			if (LC[i][j].state == 0) {
				if (Neib == 3) {
					LC[i][j].state = 1;
				}
			}
			else {
				if (Neib != 2) {
					LC[i][j].state = 0;
				}
			}
		}
	}
}