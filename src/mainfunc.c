#include "mainfunc.h"

Case **LoadCase(int width, int height) {
    Case **ListCase = malloc(height*sizeof (*ListCase));
    assert(ListCase);
    for (int i = 0; i < height; i++) {
        ListCase[i] = malloc(sizeof *ListCase[i] * width);
        assert(ListCase[i]);
        for (int j = 0; j < width; j++) {
            ListCase[i][j].posx = j;
            ListCase[i][j].posy = i;
            ListCase[i][j].state = 0;
        }
    }
    return ListCase;
}

void PrintScene(SDL_Renderer *renderer, Case **ListCase) {
	for (int i=0; i<100; i++) {
		for (int j=0; j<100; j++) {
			SDL_SetRenderDrawColor(renderer, 255,80,0,255);
			SDL_Rect RectCase = {ListCase[i][j].posx*51,ListCase[i][j].posy*51,50,50};
			SDL_RenderFillRect(renderer,&RectCase);
		}
	}
	SDL_RenderPresent(renderer);
}