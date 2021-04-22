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
            //ListCase[i][j].state = rand()%2;
            ListCase[i][j].state = 0;
            ListCase[i][j].nextstate = 0;
        }
    }
    return ListCase;
}

void LoadButton(Button *ListButton) {

    strcpy(ListButton[0].text, " Quitter ");
    strcpy(ListButton[1].text, " Nettoyer ");
    strcpy(ListButton[2].text, " Copier ");
    strcpy(ListButton[3].text, " Coller ");
    strcpy(ListButton[4].text, " Thorique ");
    strcpy(ListButton[5].text, " Ferme ");
    strcpy(ListButton[6].text, " Planeur 1 ");
    strcpy(ListButton[7].text, " Planeur 2 ");
    strcpy(ListButton[8].text, " Grenouille ");
    strcpy(ListButton[9].text, " Clignotant ");
    strcpy(ListButton[10].text, " Canon ");

    for (int i=0; i<11; i++) {
        ListButton[i].state = 0;
        ListButton[i].sizex = 150;
        ListButton[i].sizey = 50;
    }
    ListButton[5].state = 1;
}

Couple CompareChunk(Case **ListCase, int NumberLine, location loc, int sourx, int soury) {
	int i = NumberLine/2;
	int j = NumberLine;
	int k = NumberLine/2;
	int l = NumberLine;
	int x = 0;
	int y = 0;
	Case NoCase;
	NoCase.state = 3;

	Couple Ret;

	START:

	//first chunk X
	if ((ListCase[y][x].posx+loc.locx)*(loc.scale+1) <= sourx
	&& (ListCase[y][i].posx+loc.locx)*(loc.scale+1)+loc.scale >= sourx) {
		j = i;
		i = (i-x)/2;
	}

	//second chunk X
	else if ((ListCase[y][i].posx+loc.locx)*(loc.scale+1) <= sourx
	&& (ListCase[y][j].posx+loc.locx)*(loc.scale+1)+loc.scale >= sourx) {
		x = i;
		i += (j-i)/2;
	}
	//error X
	else {
		Ret.x = -1;
		Ret.y = -1;
		return Ret;
	}

	//first chunk Y
	if ((ListCase[y][x].posy+loc.locy)*(loc.scale+1) <= soury
	&& (ListCase[k][x].posy+loc.locy)*(loc.scale+1)+loc.scale >= soury) {
		l = k;
		k = (k-y)/2;
	}
	else if ((ListCase[k][x].posy+loc.locy)*(loc.scale+1) <= soury
	&& (ListCase[l][x].posy+loc.locy)*(loc.scale+1)+loc.scale >= soury) {
		y = k;
		k += (l-k)/2;
	}

	//error Y
	else {
		Ret.x = -1;
		Ret.y = -1;
		return Ret;
	}

	if (j-i<=1 && l-k<=1) {
		if ((ListCase[y][i].posx+loc.locx)*(loc.scale+1) <= sourx
		&& (ListCase[y][i].posx+loc.locx)*(loc.scale+1)+loc.scale >= sourx) {
			Ret.x = i;
		}

		else if ((ListCase[y][j].posx+loc.locx)*(loc.scale+1) <= sourx
		&& (ListCase[y][j].posx+loc.locx)*(loc.scale+1)+loc.scale >= sourx) {
			Ret.x = j;
		}

		else if ((ListCase[y][x].posx+loc.locx)*(loc.scale+1) <= sourx
		&& (ListCase[y][x].posx+loc.locx)*(loc.scale+1)+loc.scale >= sourx) {
			Ret.x = x;
		}

		else Ret.x=-1;

		if ((ListCase[k][x].posy+loc.locy)*(loc.scale+1) <= soury
		&& (ListCase[k][x].posy+loc.locy)*(loc.scale+1)+loc.scale >= soury) {
			Ret.y = k;
		}

		else if ((ListCase[l][x].posy+loc.locx)*(loc.scale+1) <= soury
		&& (ListCase[l][x].posy+loc.locx)*(loc.scale+1)+loc.scale >= soury) {
			Ret.y = l;
		}

		else if ((ListCase[y][x].posy+loc.locy)*(loc.scale+1) <= soury
		&& (ListCase[y][x].posy+loc.locy)*(loc.scale+1)+loc.scale >= soury) {
			Ret.y = y;
		}

		else Ret.y = -1;

		return Ret;
	}

	else goto START;

}

void PrintScene(SDL_Renderer *renderer, Case **ListCase, Button *ListButton, location loc, int NumberLine, int timer, TTF_Font *police) {

	SDL_SetRenderDrawColor(renderer, 100,100,100,255);
	SDL_RenderClear(renderer);

    //Print Cases
	for (int i=0; i<NumberLine; i++) {
		for (int j=0; j<NumberLine; j++) {
			ListCase[i][j].state = ListCase[i][j].nextstate;
			if (ListCase[i][j].state == 1 && timer != 0) {
				SDL_SetRenderDrawColor(renderer, 255,80,0,255);
			}
			else if (ListCase[i][j].state == 1 && timer == 0) {
				SDL_SetRenderDrawColor(renderer,0,150,255,255);
			}
			else SDL_SetRenderDrawColor(renderer, 40,40,40,255);

			SDL_Rect RectCase = {(ListCase[i][j].posx+loc.locx)*(loc.scale+1),(ListCase[i][j].posy+loc.locy)*(loc.scale+1),loc.scale,loc.scale};
			SDL_RenderFillRect(renderer,&RectCase);
		}
	}

	SDL_Color White = {255,255,255};

	//Print Buttons
	int cornx = (ListCase[0][NumberLine-1].posx+loc.locx)*(loc.scale+1)+loc.scale+10;
	int corny = (ListCase[0][0].posy+loc.locy)*(loc.scale+1);
	for (int i=0; i<11; i++) {
		if (ListButton[i].state == 1) SDL_SetRenderDrawColor(renderer,255,80,0,255);
		else SDL_SetRenderDrawColor(renderer,40,40,40,255);
        SDL_Rect RectButton = {cornx,corny + i*50+i,ListButton[i].sizex, ListButton[i].sizey};
        SDL_Rect RectText = {cornx+10,corny+10 + i*50+i,ListButton[i].sizex-20, ListButton[i].sizey-20};
        SDL_RenderFillRect(renderer,&RectButton);
        SDL_Surface *surface = TTF_RenderText_Blended(police,ListButton[i].text,White);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &RectText);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
		
	}
	
	SDL_RenderPresent(renderer);
}

void LifeThor(Case **LC, int NumberLine) {

	int Neib;
	int ColSup;
	int ColInf;
	int RowSup;
	int Rowinf;

	for (int i=0; i<NumberLine; i++) {
		for (int j=0; j<NumberLine; j++) {

            //Columns
            if (i==0) {
                ColInf = NumberLine-1;
                ColSup = i+1;
            }
            else if (i==NumberLine-1) {
                ColInf = i-1;
                ColSup = 0;
            }
            else {
                ColInf = i-1;
                ColSup = i+1;
            }

            //Rows
            if (j==0) {
                Rowinf = NumberLine-1;
                RowSup = j+1;
            }
            else if (j==NumberLine-1) {
                Rowinf = j-1;
                RowSup = 0;
            }
            else {
                Rowinf = j-1;
                RowSup = j+1;
            }

            //Neibours
			Neib = LC[i][RowSup].state+LC[i][Rowinf].state
            +LC[ColSup][j].state+LC[ColInf][j].state+LC[ColSup][RowSup].state
            +LC[ColInf][RowSup].state+LC[ColSup][Rowinf].state+LC[ColInf][Rowinf].state;


			if (LC[i][j].state == 0) {
				if (Neib == 3) {
					LC[i][j].nextstate = 1;
				}
			}
			else {
				if (Neib != 2 && Neib != 3) {
					LC[i][j].nextstate = 0;
				}
			}
		}
	}
}

void LifeClosed(Case **LC, int NumberLine) {

	int Neib;
	for (int i=1; i<NumberLine-1; i++) {
		for (int j=1; j<NumberLine-1; j++) {

            //Neibours
			Neib = LC[i][j+1].state+LC[i][j-1].state
            +LC[i+1][j].state+LC[i-1][j].state+LC[i+1][j+1].state
            +LC[i-1][j+1].state+LC[i+1][j-1].state+LC[i-1][j-1].state;


			if (LC[i][j].state == 0) {
				if (Neib == 3) {
					LC[i][j].nextstate = 1;
				}
			}
			else {
				if (Neib != 2 && Neib != 3) {
					LC[i][j].nextstate = 0;
				}
			}
		}
	}
}

void SaveMap(Case **ListCase, int NumberLine, char name[]) {
    FILE* MapFile = NULL;

    MapFile = fopen(name, "r+");
    if (MapFile == NULL) printf("failed to open map file");

    fprintf(MapFile,"%d %d\n", NumberLine, NumberLine);
    for (int i=0; i<NumberLine; i++) {
        for (int j=0; j<NumberLine; j++) {
            fprintf(MapFile, "%d ", ListCase[i][j].state);
        }
        fprintf(MapFile,"\n");
    }

}

int LoadMap(Case **ListCase, int NumberLine, char name[]) {
    FILE* MapFile = NULL;

    MapFile = fopen(name, "r+");
    if (MapFile == NULL) printf("failed to open map file");

    fscanf(MapFile,"%d %d\n", &NumberLine, &NumberLine);
    for (int i=0; i<NumberLine; i++) {
        for (int j=0; j<NumberLine; j++) {
            fscanf(MapFile, "%d ", &ListCase[i][j].nextstate);
        }
        //fseek(MapFile, 1, SEEK_CUR);
    }
    return NumberLine;

}

int ButtonFunc(SDL_Renderer *renderer, Button *ListButton, Case **ListCase, int NumberLine, int *MapState, location loc, int timer, TTF_Font *police) {
	if (ListButton[1].state == 1) {
		ListCase = LoadCase(NumberLine);
		PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
		SDL_Delay(16);
		ListButton[1].state = 0; }
	if (ListButton[2].state == 1) {
		SaveMap(ListCase,NumberLine,"map/buffer.txt");
		PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
		SDL_Delay(16);
		ListButton[2].state = 0; }
	if (ListButton[3].state == 1) {
		LoadMap(ListCase,NumberLine,"map/buffer.txt");
		PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
		SDL_Delay(16);
		ListButton[3].state = 0; }
	if (ListButton[5].state == 1 && *MapState == 0) {
		*MapState = 1;
		ListButton[4].state = 0; }
	if (ListButton[4].state == 1 && *MapState == 1) {
		*MapState = 0;
		ListButton[5].state = 0; }
	
	if (ListButton[6].state == 1) {
		LoadMap(ListCase,NumberLine,"map/Planeur1.txt");
		PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
		SDL_Delay(16);
		ListButton[6].state = 0; }
	if (ListButton[7].state == 1) {
		LoadMap(ListCase,NumberLine,"map/Planeur2.txt");
		PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
		SDL_Delay(16);
		ListButton[7].state = 0; }
	if (ListButton[8].state == 1) {
		LoadMap(ListCase,NumberLine,"map/Grenouille.txt");
		PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
		SDL_Delay(16);
		ListButton[8].state = 0; }
	if (ListButton[9].state == 1) {
		LoadMap(ListCase,NumberLine,"map/Clignotant.txt");
		PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
		SDL_Delay(16);
		ListButton[9].state = 0; }
	if (ListButton[10].state == 1) {
		LoadMap(ListCase,NumberLine,"map/Canon.txt");
		PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
		SDL_Delay(16);
		ListButton[10].state = 0; }


	return NumberLine;

}

/*
void CallThread(Case **ListCase, int NumberLine, location loc, SDL_Event event) {
	pthread_t Listhread[8];
	for (int i=0; i<8; i++) {
		pthread_create(&Listhread[i], NULL, myThreadFun, NULL);

	}
}

couple ThreadFunc1(Case **ListCase, int NumberLine, location loc, SDL_Event event, int NumberThread) {
	for (int i=0; i<NumberLine/8; i++) {
		for (int j=0; j<NumberLine/8; j++) {
			if ((ListCase[i][j].posx+loc.locx)*(loc.scale+1) <= event.button.x
			&& (ListCase[i][j].posx+loc.locx)*(loc.scale+1)+loc.scale >= event.button.x
			&& (ListCase[i][j].posy+loc.locy)*(loc.scale+1) <= event.button.y
			&& (ListCase[i][j].posy+loc.locy)*(loc.scale+1)+loc.scale >= event.button.y) {
				couple ret = {i,j};
				return ret;
			}
			else {
				couple ret = {-1,1};
				return ret;
			}
		}
	}
}
*/

