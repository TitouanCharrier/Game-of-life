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
            ListCase[i][j].state = rand()%2;
        }
    }
    return ListCase;
}

void PrintScene(SDL_Renderer *renderer, Case **ListCase) {

	SDL_SetRenderDrawColor(renderer, 100,100,100,255);
	SDL_RenderClear(renderer);
	
	for (int i=0; i<10; i++) {
		for (int j=0; j<10; j++) {
		}
	}

	for (int i=0; i<100; i++) {
		for (int j=0; j<100; j++) {
			
			if (ListCase[i][j].state ==1) {
				SDL_SetRenderDrawColor(renderer, 255,80,0,255);
			}
			else SDL_SetRenderDrawColor(renderer, 40,40,40,255);
			SDL_Rect RectCase = {ListCase[i][j].posx*51,ListCase[i][j].posy*51,50,50};
			SDL_RenderFillRect(renderer,&RectCase);
		}
	}
	SDL_RenderPresent(renderer);


}

void Life(Case **LC) {
	
	int Neib;

	for (int i=0+2; i<100-2; i++) {
		for (int j=0+2; j<100-2; j++) {
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

	printf("debugfinlife\n");
	printf("adresse liste %p\n",LC);
	
}