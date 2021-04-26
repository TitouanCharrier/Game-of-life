#include "mainfunc.h"

Case **LoadCase(Grid *NumberOf) {
    Case **ListCase = malloc(NumberOf->Lines*sizeof (*ListCase));
    assert(ListCase);
    for (int i = 0; i < NumberOf->Lines; i++) {
        ListCase[i] = malloc(sizeof *ListCase[i] * NumberOf->Cols);
        assert(ListCase[i]);
        for (int j = 0; j < NumberOf->Cols; j++) {
            ListCase[i][j].posx = j;
            ListCase[i][j].posy = i;
            //ListCase[i][j].state = rand()%2;
            ListCase[i][j].state = 0;
            ListCase[i][j].nextstate = 0;
        }
    }
    return ListCase;
}

void LoadButton(Button *ListButton, int RESX, int RESY, Grid *NumberOf) {

    strcpy(ListButton[0].text, "Quitter (echap)");
    strcpy(ListButton[1].text, "Nettoyer (r)");
    strcpy(ListButton[2].text, "Copier (k)");
    strcpy(ListButton[3].text, "Coller (l)");
    strcpy(ListButton[4].text, " Thorique ");
    strcpy(ListButton[5].text, " Ferme ");
    strcpy(ListButton[6].text, " Planeur 1 ");
    strcpy(ListButton[7].text, " Planeur 2 ");
    strcpy(ListButton[8].text, " Grenouille ");
    strcpy(ListButton[9].text, " Clignotant ");
    strcpy(ListButton[10].text, " Canon ");
    strcpy(ListButton[11].text, " Lancer ");

    for (int i=0; i<NumberOf->Buttons; i++) {
        ListButton[i].state = 0;
        ListButton[i].sizex = 150;
        ListButton[i].sizey = 50;
        ListButton[i].resx = RESX;
        ListButton[i].resy = RESY;
    }
    ListButton[5].state = 1;
}

void LoadDirection(Button *ListDirection, int RESX, int RESY, Grid *NumberOf) {

    strcpy(ListDirection[0].text, "Up");
    strcpy(ListDirection[1].text, "Down");
    strcpy(ListDirection[2].text, "Right");
    strcpy(ListDirection[3].text, "Left");
    strcpy(ListDirection[4].text, "+");
    strcpy(ListDirection[5].text, "-");

    for (int i=0; i<NumberOf->Direction; i++) {
        ListDirection[i].state = 0;
        ListDirection[i].sizex = 50;
        ListDirection[i].sizey = 50;
        ListDirection[i].resx = RESX;
        ListDirection[i].resy = RESY;
        strcpy(ListDirection[i].img, "rsc/arrow.bmp");
    }
    ListDirection[4].sizey = 25;
    strcpy(ListDirection[4].img, "rsc/_plus.bmp");
    ListDirection[5].sizey = 25;
    strcpy(ListDirection[5].img, "rsc/minus.bmp");

    ListDirection[0].cornx = RESX-150;
    ListDirection[0].corny = RESY-250;

    ListDirection[1].cornx = RESX-150;
    ListDirection[1].corny = RESY-150;

    ListDirection[2].cornx = RESX-100;
    ListDirection[2].corny = RESY-200;

    ListDirection[3].cornx = RESX-200;
    ListDirection[3].corny = RESY-200;

    ListDirection[4].cornx = RESX-237;
    ListDirection[4].corny = RESY-200;

    ListDirection[5].cornx = RESX-237;
    ListDirection[5].corny = RESY-175;


}

Couple CompareChunk(Case **ListCase, Grid *NumberOf, location loc, int sourx, int soury) {
	int i = NumberOf->Lines/2;
	int j = NumberOf->Lines;
	int k = NumberOf->Cols/2;
	int l = NumberOf->Cols;
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

void PrintScene(SDL_Renderer *renderer, Case **ListCase, Button *ListDirection, Button *ListButton, location loc, Grid *NumberOf, int *timer, TTF_Font *police) {
	
	//SDL_Delay(16);

	SDL_SetRenderDrawColor(renderer, 100,100,100,255);
	SDL_RenderClear(renderer);
    //Print Cases
	for (int i=0; i<NumberOf->Lines; i++) {
		for (int j=0; j<NumberOf->Cols; j++) {
			ListCase[i][j].state = ListCase[i][j].nextstate;
			if (ListCase[i][j].state == 1 && *timer != 0) {
				SDL_SetRenderDrawColor(renderer, 255,80,0,255);
			}
			else if (ListCase[i][j].state == 1 && *timer == 0) {
				SDL_SetRenderDrawColor(renderer,0,150,255,255);
			}
			else SDL_SetRenderDrawColor(renderer, 40,40,40,255);

			SDL_Rect RectCase = {(ListCase[i][j].posx+loc.locx)*(loc.scale+1)+(2560/2-loc.scale*NumberOf->Cols/2),
                                 (ListCase[i][j].posy+loc.locy)*(loc.scale+1)+(1080/2-loc.scale*NumberOf->Lines/2),
                                  loc.scale,loc.scale};
			SDL_RenderFillRect(renderer,&RectCase);
		}
	}

	SDL_Color White = {255,255,255};

	//Print Buttons
	//int cornx = (ListCase[0][NumberOf->Cols-1].posx+loc.locx)*(loc.scale+1)+loc.scale+10;
	//int corny = (ListCase[0][0].posy+loc.locy)*(loc.scale+1);
	for (int i=0; i<NumberOf->Buttons; i++) {
        if (i==11 && ListButton[i].state == 0) SDL_SetRenderDrawColor(renderer,0,150,255,255);
		else if (ListButton[i].state == 1) SDL_SetRenderDrawColor(renderer,255,80,0,255);
		else SDL_SetRenderDrawColor(renderer,60,60,60,255);
        SDL_Rect RectButton = {ListButton[i].resx-ListButton[i].sizex-10,10 + i*50+i,ListButton[i].sizex, ListButton[i].sizey};
        SDL_Rect RectText = {ListButton[i].resx-ListButton[i].sizex,20 + i*50+i,ListButton[i].sizex-20, ListButton[i].sizey-20};
        SDL_RenderFillRect(renderer,&RectButton);
        SDL_Surface *surface = TTF_RenderText_Blended(police,ListButton[i].text,White);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &RectText);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

	}
	
	//variables for flipping
	SDL_RendererFlip FlipNone = SDL_FLIP_NONE;
    SDL_RendererFlip FlipHor = SDL_FLIP_HORIZONTAL;
    SDL_RendererFlip FlipVer = SDL_FLIP_VERTICAL;

    //print Directions
	for (int i=0; i<NumberOf->Direction-2; i++) {

		SDL_Rect RectImage;

		if (ListDirection[i].state == 0) {
			SDL_Rect RectImage = {ListDirection[i].cornx, ListDirection[i].corny, ListDirection[i].sizex, ListDirection[i].sizey};
		}
		else {
			SDL_Rect RectImage = {ListDirection[i].cornx-5, ListDirection[i].corny-5, ListDirection[i].sizex+5, ListDirection[i].sizey+5};
		}
        SDL_Surface *surface = SDL_LoadBMP(ListDirection[i].img);
        if (surface == NULL) printf("failed to open a texture %s\n", ListDirection[i].img);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        switch (i) {
        	case 0 :
        		SDL_RenderCopyEx(renderer, texture, NULL, &RectImage,-90,NULL,FlipNone);
        		break;
        	case 1 :
        		SDL_RenderCopyEx(renderer, texture, NULL, &RectImage,90,NULL,FlipNone);
        		break;
        	case 2 :
        		SDL_RenderCopyEx(renderer, texture, NULL, &RectImage,0,NULL,FlipNone);
        		break;
        	case 3 :
        		SDL_RenderCopyEx(renderer, texture, NULL, &RectImage,180,NULL,FlipNone);
        		break;
        	case 4 :
        		SDL_RenderCopyEx(renderer, texture, NULL, &RectImage,0,NULL,FlipNone);
        		break;
        	case 5 :
        		SDL_RenderCopyEx(renderer, texture, NULL, &RectImage,0,NULL,FlipNone);
        		break;
        }

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
	}
	SDL_RenderPresent(renderer);
}

void LifeThor(Case **LC, Grid *NumberOf) {

	int Neib;
	int ColSup;
	int ColInf;
	int RowSup;
	int Rowinf;

	for (int i=0; i<NumberOf->Lines; i++) {
		for (int j=0; j<NumberOf->Cols; j++) {

            //Columns
            if (i==0) {
                ColInf = NumberOf->Lines-1;
                ColSup = i+1;
            }
            else if (i==NumberOf->Lines-1) {
                ColInf = i-1;
                ColSup = 0;
            }
            else {
                ColInf = i-1;
                ColSup = i+1;
            }

            //Rows
            if (j==0) {
                Rowinf = NumberOf->Cols-1;
                RowSup = j+1;
            }
            else if (j==NumberOf->Cols-1) {
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

void LifeClosed(Case **LC, Grid *NumberOf) {

	int Neib;
	for (int i=1; i<NumberOf->Lines-1; i++) {
		for (int j=1; j<NumberOf->Cols-1; j++) {

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

void SaveMap(Case **ListCase, Grid *NumberOf, char name[]) {
    FILE* MapFile = NULL;

    MapFile = fopen(name, "r+");
    if (MapFile == NULL) printf("ERROR : failed to open map file for saving\n");

    fseek(MapFile,0,SEEK_SET);

    fprintf(MapFile,"%d %d\n", NumberOf->Lines, NumberOf->Cols);
    for (int i=0; i<NumberOf->Lines; i++) {
        for (int j=0; j<NumberOf->Cols; j++) {
            fprintf(MapFile, "%d ", ListCase[i][j].state);
        }
        fprintf(MapFile,"\n");
    }

}

void LoadMap(Case **ListCase, Grid *NumberOf, char name[]) {
    FILE* MapFile = NULL;
    int FileLines;
    int FileCols;

    MapFile = fopen(name, "r+");
    if (MapFile == NULL) printf("ERROR : failed to open map file for load\n");

    fscanf(MapFile,"%d %d\n", &FileLines, &FileCols);

    if (FileCols > NumberOf->Cols || FileLines > NumberOf->Lines) {
        printf("ERROR : Load map failed please increase your main map size\n");
    }
    else {
        //load
        for (int i=0; i<FileLines; i++) {
            for (int j=0; j<FileCols; j++) {
                fscanf(MapFile, "%d ", &ListCase[i][j].nextstate);
            }
        }
    }
}

/*WIP
void LoadRle(Case **ListCase, Grid *NumberOf, char name[]) {
    FILE* MapFile = NULL;
    int FileLines;
    int FileCols;
    char BuffChar;
    int BuffInt;

    MapFile = fopen(name, "r+");
    if (MapFile == NULL) printf("ERROR : failed to open map file for load\n");

    fscanf(MapFile,"x = %d, y = %d rule = B3/S23\n", &FileCols, &FileLines);

    if (FileCols > NumberOf->Cols || FileLines > NumberOf->Lines) {
        printf("ERROR : Load map failed please increase your main map size\n");
    }
    else {
        //load
        BuffChar = fgetc(MapFile);
        while (BuffChar != '!') {

        }
    }
}*/

void Clean(Case **ListCase, Grid *NumberOf) {
    for (int i=0; i<NumberOf->Lines; i++) {
        for (int j=0; j<NumberOf->Cols; j++) {
            ListCase[i][j].nextstate = 0;
        }
    }
}

void ButtonFunc(SDL_Renderer *renderer, Button *ListDirection, Button *ListButton, Case **ListCase, Grid *NumberOf, int *MapState, location loc, int *timer, TTF_Font *police, Disp *DispVar) {
	if (ListButton[1].state == 1) {
		Clean(ListCase,NumberOf);
		PrintScene(renderer,ListCase, ListDirection, ListButton,loc,NumberOf,timer,police);
		SDL_Delay(16);
		ListButton[1].state = 0; }

	if (ListButton[2].state == 1) {
		SaveMap(ListCase,NumberOf,"map/buffer.ins");
		PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,timer,police);
		SDL_Delay(16);
		ListButton[2].state = 0; }

	if (ListButton[3].state == 1) {
		LoadMap(ListCase,NumberOf,"map/buffer.ins");
		PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,timer,police);
		SDL_Delay(16);
		ListButton[3].state = 0; }

	if (ListButton[5].state == 1 && *MapState == 0) {
		*MapState = 1;
		ListButton[4].state = 0; }

	if (ListButton[4].state == 1 && *MapState == 1) {
		*MapState = 0;
		ListButton[5].state = 0; }

	if (ListButton[6].state == 1) {
        Clean(ListCase,NumberOf);
		LoadMap(ListCase,NumberOf,"map/Planeur1.ins");
		PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,timer,police);
		SDL_Delay(16);
		ListButton[6].state = 0; }

	if (ListButton[7].state == 1) {
        Clean(ListCase,NumberOf);
		LoadMap(ListCase,NumberOf,"map/Planeur2.ins");
		PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,timer,police);
		SDL_Delay(16);
		ListButton[7].state = 0; }

	if (ListButton[8].state == 1) {
        Clean(ListCase,NumberOf);
		LoadMap(ListCase,NumberOf,"map/Grenouille.ins");
		PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,timer,police);
		SDL_Delay(16);
		ListButton[8].state = 0; }

	if (ListButton[9].state == 1) {
        Clean(ListCase,NumberOf);
		LoadMap(ListCase,NumberOf,"map/Clignotant.ins");
		PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,timer,police);
		SDL_Delay(16);
		ListButton[9].state = 0; }

	if (ListButton[10].state == 1) {
        Clean(ListCase,NumberOf);
		LoadMap(ListCase,NumberOf,"map/Canon.ins");
		PrintScene(renderer,ListCase,ListDirection,ListButton,loc,NumberOf,timer,police);
		SDL_Delay(16);
		ListButton[10].state = 0; }

    if (ListButton[11].state == 1 && *timer == 0) {
		*timer = 1;
		strcpy(ListButton[11].text,"Arreter");
		//ListButton[11].state = 0;
		}

    if (ListButton[11].state == 0 && *timer >= 1) {
		*timer = 0;
		strcpy(ListButton[11].text,"Lancer");
		}

	if (ListDirection[0].state == 1) {
		DispVar->Vtc = 1;
	}
	if (ListDirection[1].state == 1) {
		DispVar->Vtc = -1;
	}
	if (ListDirection[2].state == 1) {
		DispVar->Hzt = -1;
	}
	if (ListDirection[3].state == 1) {
		DispVar->Hzt = 1;
	}


	return NumberOf;

}

//WIP
void FreeCase(Case **ListCase,Grid *NumberOf) {
    for (int i=0; i<NumberOf->Lines; i++) {
        free(ListCase[i]);
    }

}

/*
void CallThread(Case **ListCase, Grid *NumberOf, location loc, SDL_Event event) {
	pthread_t Listhread[8];
	for (int i=0; i<8; i++) {
		pthread_create(&Listhread[i], NULL, myThreadFun, NULL);

	}
}

couple ThreadFunc1(Case **ListCase, Grid *NumberOf, location loc, SDL_Event event, int NumberThread) {
	for (int i=0; i<NumberOf->Lines/8; i++) {
		for (int j=0; j<NumberOf->Cols/8; j++) {
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

