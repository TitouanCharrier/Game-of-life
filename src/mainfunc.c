#include "mainfunc.h"

void LoadCase(St_List *List, Grid *NumberOf) {
    List->Cases = malloc(NumberOf->Lines*sizeof (*List->Cases));
    assert(List->Cases);
    time_t t;
    srand((unsigned) time(&t));

    for (int i = 0; i < NumberOf->Lines; i++) {
        List->Cases[i] = malloc(sizeof *List->Cases[i] * NumberOf->Cols);
        assert(List->Cases[i]);
        for (int j = 0; j < NumberOf->Cols; j++) {
            List->Cases[i][j].posx = j;
            List->Cases[i][j].posy = i;
            //List->Cases[i][j].nextstate = rand()%2;
            List->Cases[i][j].nextstate = 0;
            List->Cases[i][j].state = 0;
        }
    }
}

void LoadButton(St_List *List, St_Var *MainVar, Grid *NumberOf) {

    strcpy(List->Buttons[0].text, "Quitter (echap)");
    strcpy(List->Buttons[1].text, "Nettoyer (r)");
    strcpy(List->Buttons[2].text, "Copier (k)");
    strcpy(List->Buttons[3].text, "Coller (l)");
    strcpy(List->Buttons[4].text, " Thorique ");
    strcpy(List->Buttons[5].text, " Ferme ");
    strcpy(List->Buttons[6].text, " Plus Vite ");
    strcpy(List->Buttons[7].text, " Moins Vite ");
    strcpy(List->Buttons[8].text, " Lancer ");
    strcpy(List->Buttons[9].text, " Planeur 1 ");
    strcpy(List->Buttons[10].text, "Cercle de Feu");
    strcpy(List->Buttons[11].text, " Grenouille ");
    strcpy(List->Buttons[12].text, " Clignotant ");
    strcpy(List->Buttons[13].text, " Canon ");
    strcpy(List->Buttons[14].text, " Pulsar ");
    strcpy(List->Buttons[15].text, "    JSP    ");
    strcpy(List->Buttons[16].text, "Sharingan");
    strcpy(List->Buttons[17].text, "Load rle");

    for (int i=0; i<NumberOf->Buttons+NumberOf->ButtonLeft; i++) {
        List->Buttons[i].state = 0;
        List->Buttons[i].sizex = 150;
        List->Buttons[i].sizey = 50;
        List->Buttons[i].resx = MainVar->resx;
        List->Buttons[i].resy = MainVar->resy;
        List->Buttons[i].cornx = MainVar->resx-List->Buttons[i].sizex-10;
        List->Buttons[i].corny = 10 + i*50+i,List->Buttons[i].sizex;
    }

    for (int i=NumberOf->Buttons; i<NumberOf->Buttons+NumberOf->ButtonLeft; i++) {
        List->Buttons[i].state = 0;
        List->Buttons[i].sizex = 150;
        List->Buttons[i].sizey = 50;
        List->Buttons[i].resx = MainVar->resx;
        List->Buttons[i].resy = MainVar->resy;
        List->Buttons[i].cornx = 10;
        List->Buttons[i].corny = 10 + (i-NumberOf->Buttons)*50+(i-NumberOf->Buttons),List->Buttons[i].sizex;
    }

    List->Buttons[4].state = 1;

}

void LoadDirection(St_List *List, St_Var *MainVar, Grid *NumberOf) {

    strcpy(List->Direction[0].text, "Up");
    strcpy(List->Direction[1].text, "Down");
    strcpy(List->Direction[2].text, "Right");
    strcpy(List->Direction[3].text, "Left");
    strcpy(List->Direction[4].text, "+");
    strcpy(List->Direction[5].text, "-");

    for (int i=0; i<NumberOf->Direction; i++) {
        List->Direction[i].state = 0;
        List->Direction[i].sizex = 50;
        List->Direction[i].sizey = 50;
        List->Direction[i].resx = MainVar->resx;
        List->Direction[i].resy = MainVar->resy;
        strcpy(List->Direction[i].img, "rsc/arrow.bmp");
    }
    List->Direction[4].sizey = 25;
    strcpy(List->Direction[4].img, "rsc/_plus.bmp");
    List->Direction[5].sizey = 25;
    strcpy(List->Direction[5].img, "rsc/minus.bmp");

    List->Direction[0].cornx = MainVar->resx-150;
    List->Direction[0].corny = MainVar->resy-250;

    List->Direction[1].cornx = MainVar->resx-150;
    List->Direction[1].corny = MainVar->resy-150;

    List->Direction[2].cornx = MainVar->resx-100;
    List->Direction[2].corny = MainVar->resy-200;

    List->Direction[3].cornx = MainVar->resx-200;
    List->Direction[3].corny = MainVar->resy-200;

    List->Direction[4].cornx = MainVar->resx-237;
    List->Direction[4].corny = MainVar->resy-200;

    List->Direction[5].cornx = MainVar->resx-237;
    List->Direction[5].corny = MainVar->resy-175;


}

Couple CompareChunk(St_List *List, Grid *NumberOf, St_Var *MainVar, int sourx, int soury) {
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
	if ((List->Cases[y][x].posx+MainVar->loc.locx)*(MainVar->loc.scale+1) <= sourx
	&& (List->Cases[y][i].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale >= sourx) {
		j = i;
		i = (i-x)/2;
	}

	//second chunk X
	else if ((List->Cases[y][i].posx+MainVar->loc.locx)*(MainVar->loc.scale+1) <= sourx
	&& (List->Cases[y][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale >= sourx) {
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
	if ((List->Cases[y][x].posy+MainVar->loc.locy)*(MainVar->loc.scale+1) <= soury
	&& (List->Cases[k][x].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+MainVar->loc.scale >= soury) {
		l = k;
		k = (k-y)/2;
	}
	else if ((List->Cases[k][x].posy+MainVar->loc.locy)*(MainVar->loc.scale+1) <= soury
	&& (List->Cases[l][x].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+MainVar->loc.scale >= soury) {
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
		if ((List->Cases[y][i].posx+MainVar->loc.locx)*(MainVar->loc.scale+1) <= sourx
		&& (List->Cases[y][i].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale >= sourx) {
			Ret.x = i;
		}

		else if ((List->Cases[y][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1) <= sourx
		&& (List->Cases[y][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale >= sourx) {
			Ret.x = j;
		}

		else if ((List->Cases[y][x].posx+MainVar->loc.locx)*(MainVar->loc.scale+1) <= sourx
		&& (List->Cases[y][x].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale >= sourx) {
			Ret.x = x;
		}

		else Ret.x=-1;

		if ((List->Cases[k][x].posy+MainVar->loc.locy)*(MainVar->loc.scale+1) <= soury
		&& (List->Cases[k][x].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+MainVar->loc.scale >= soury) {
			Ret.y = k;
		}

		else if ((List->Cases[l][x].posy+MainVar->loc.locx)*(MainVar->loc.scale+1) <= soury
		&& (List->Cases[l][x].posy+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale >= soury) {
			Ret.y = l;
		}

		else if ((List->Cases[y][x].posy+MainVar->loc.locy)*(MainVar->loc.scale+1) <= soury
		&& (List->Cases[y][x].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+MainVar->loc.scale >= soury) {
			Ret.y = y;
		}

		else Ret.y = -1;

		return Ret;
	}

	else goto START;

}

void PrintScene(SDL_Renderer *renderer,St_List *List, St_Var *MainVar, Grid *NumberOf) {

	//SDL_Delay(16);
	SDL_SetRenderDrawColor(renderer, 100,100,100,255);
	SDL_RenderClear(renderer);
    //Print Cases
	for (int i=0; i<NumberOf->Lines; i++) {
		for (int j=0; j<NumberOf->Cols; j++) {
			List->Cases[i][j].state = List->Cases[i][j].nextstate;
			if (List->Cases[i][j].state == 1 && MainVar->timer != 0) {
				SDL_SetRenderDrawColor(renderer, 255,80,0,255);
			}
			else if (List->Cases[i][j].state == 1 && MainVar->timer == 0) {
				SDL_SetRenderDrawColor(renderer,0,150,255,255);
			}
			else SDL_SetRenderDrawColor(renderer, 40,40,40,255);

			SDL_Rect RectCase = {(List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+(List->Buttons[0].resx/2-MainVar->loc.scale*NumberOf->Cols/2),
                                 (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+(List->Buttons[0].resy/2-MainVar->loc.scale*NumberOf->Lines/2),
                                  MainVar->loc.scale,MainVar->loc.scale};
			SDL_RenderFillRect(renderer,&RectCase);
		}
	}
	SDL_Color White = {255,255,255};

	//Print Buttons part 1
	//int cornx = (List->Cases[0][NumberOf->Cols-1].posx+MainVar->loc.locx)*(loc.scale+1)+MainVar->loc.scale+10;
	//int corny = (List->Cases[0][0].posy+MainVar->loc.locy)*(loc.scale+1);
	for (int i=0; i<NumberOf->Buttons; i++) {
        if (i==8 && List->Buttons[i].state == 0) SDL_SetRenderDrawColor(renderer,0,150,255,255);
		else if (List->Buttons[i].state == 1) SDL_SetRenderDrawColor(renderer,255,80,0,255);
		else SDL_SetRenderDrawColor(renderer,60,60,60,255);
        SDL_Rect RectButton = {List->Buttons[i].cornx,List->Buttons[i].corny,List->Buttons[i].sizex, List->Buttons[i].sizey};
        SDL_Rect RectText = {List->Buttons[i].cornx+10,List->Buttons[i].corny+10,List->Buttons[i].sizex-20, List->Buttons[i].sizey-20};
        SDL_RenderFillRect(renderer,&RectButton);
        SDL_Surface *surface = TTF_RenderText_Blended(MainVar->police,List->Buttons[i].text,White);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, texture, NULL, &RectText);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);

	}
    //print buutton left
	for (int i=NumberOf->Buttons; i<NumberOf->Buttons+NumberOf->ButtonLeft; i++) {
		if (List->Buttons[i].state == 1) SDL_SetRenderDrawColor(renderer,255,80,0,255);
		else SDL_SetRenderDrawColor(renderer,60,60,60,255);
        SDL_Rect RectButton = {List->Buttons[i].cornx,List->Buttons[i].corny,List->Buttons[i].sizex, List->Buttons[i].sizey};
        SDL_Rect RectText = {List->Buttons[i].cornx+10,List->Buttons[i].corny+10,List->Buttons[i].sizex-20, List->Buttons[i].sizey-20};
        SDL_RenderFillRect(renderer,&RectButton);
        SDL_Surface *surface = TTF_RenderText_Blended(MainVar->police,List->Buttons[i].text,White);
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

		if (List->Direction[i].state == 0) {
			SDL_Rect RectImage = {List->Direction[i].cornx, List->Direction[i].corny, List->Direction[i].sizex, List->Direction[i].sizey};
		}
		else {
			SDL_Rect RectImage = {List->Direction[i].cornx-5, List->Direction[i].corny-5, List->Direction[i].sizex+5, List->Direction[i].sizey+5};
		}
        SDL_Surface *surface = SDL_LoadBMP(List->Direction[i].img);
        if (surface == NULL) printf("failed to open a texture %s\n", List->Direction[i].img);
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
    //Print Count Generations
  	char CharGen[30];
  	sprintf(CharGen, "%d", NumberOf->Gen);
  	int w;
  	int h;
    TTF_SizeText(MainVar->police,CharGen,&w,&h);
    SDL_Surface *surface = TTF_RenderText_Blended(MainVar->police,CharGen,White);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect RectButton = {List->Buttons[0].resx/2-w/2,10,w,h};
    SDL_RenderCopy(renderer, texture, NULL, &RectButton);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
	SDL_RenderPresent(renderer);
}

void LifeThor(St_List *List, Grid *NumberOf) {
    Case **LC = List->Cases;
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

void LifeClosed(St_List *List, Grid *NumberOf) {
    
    Case **LC = List->Cases;
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

void SaveMap(St_List *List, Grid *NumberOf, char name[]) {
    FILE* MapFile = NULL;

    MapFile = fopen(name, "r+");
    if (MapFile == NULL) printf("ERROR : failed to open map file for saving\n");

    fseek(MapFile,0,SEEK_SET);

    fprintf(MapFile,"%d %d\n", NumberOf->Lines, NumberOf->Cols);
    for (int i=0; i<NumberOf->Lines; i++) {
        for (int j=0; j<NumberOf->Cols; j++) {
            fprintf(MapFile, "%d ", List->Cases[i][j].state);
        }
        fprintf(MapFile,"\n");
    }

}

void LoadMap(St_List *List, Grid *NumberOf, char name[]) {
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
                fscanf(MapFile, "%d ", &List->Cases[i][j].nextstate);
            }
        }
    }
}

void LoadRle(St_List *List, Grid *NumberOf, char name[]) {
    FILE* MapFile = NULL;
    int FileLines = 0;
    int FileCols = 0;
    char BuffChar1;
    int BuffNum1;
    int BuffNumF = 0;
    int Lines = 0;
    int CountCol = 0;

    MapFile = fopen(name, "r+");
    if (MapFile == NULL) printf("ERROR : failed to open map file for load\n");

    fscanf(MapFile,"x = %d, y = %d", &FileCols, &FileLines);

    if (FileCols > NumberOf->Cols || FileLines > NumberOf->Lines) {
        printf("ERROR : Load map failed please increase your main map size\n");
    }
    else {

        //load
        BuffChar1 = fgetc(MapFile);
        while (BuffChar1 != EOF) {
            //printf("%c",BuffChar1 );
            if (BuffChar1 == 'x' || BuffChar1 == 'X' || BuffChar1 == '#') {
                while (BuffChar1 != '\n') {
                    BuffChar1 = fgetc(MapFile);
                }
            }
            
            else if (BuffChar1 == 'o') {
                
                if (BuffNumF == 0) BuffNumF = 1;
                for(int i=0; i<BuffNumF; i++) {
                    List->Cases[Lines][CountCol].nextstate = 1;
                    CountCol+=1;
                }
                BuffNumF = 0;
                BuffNum1 = 0;  

            }
            else if (BuffChar1 == 'b') {
                if (BuffNumF == 0) BuffNumF = 1;
                for(int i=0; i<BuffNumF; i++) {
                    List->Cases[Lines][CountCol].nextstate = 0;
                    CountCol+=1;
                }
                BuffNumF = 0;
                BuffNum1 = 0;
                
            }
            else if (isdigit(BuffChar1)) {
                BuffNum1 = atoi(&BuffChar1);
                BuffNumF = concat(BuffNumF,BuffNum1);
            }
            else if (BuffChar1 == '$') {
                if (BuffNumF == 0) BuffNumF = 1;
                for(int i=0; i<BuffNumF; i++) {
                    Lines++;
                }
                BuffNumF = 0;
                CountCol = 0;
            }
            BuffChar1 = fgetc(MapFile);
        }
    }
}

void Clean(St_List *List, Grid *NumberOf) {
    for (int i=0; i<NumberOf->Lines; i++) {
        for (int j=0; j<NumberOf->Cols; j++) {
            List->Cases[i][j].nextstate = 0;
        }
    }
}

void ButtonFunc(SDL_Renderer *renderer, St_List *List, Grid *NumberOf, St_State *State, St_Var *MainVar, Disp *DispVar) {
	if (List->Buttons[1].state == 1) {
		Clean(List,NumberOf);
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		NumberOf->Gen = 0;
		List->Buttons[1].state = 0; }

	if (List->Buttons[2].state == 1) {
		SaveMap(List,NumberOf,"map/buffer.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[2].state = 0; }

	if (List->Buttons[3].state == 1) {
		LoadMap(List,NumberOf,"map/buffer.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[3].state = 0; }

    if (List->Buttons[4].state == 1 && State->Map == 1) {
		State->Map = 0;
		List->Buttons[5].state = 0; }

	if (List->Buttons[5].state == 1 && State->Map == 0) {
		State->Map = 1;
		List->Buttons[4].state = 0; }

    if (List->Buttons[6].state == 1 && NumberOf->Time > 1) {
		NumberOf->Time -= 1;
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[6].state = 0; }

	if (List->Buttons[7].state == 1) {
		NumberOf->Time += 1;
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[7].state = 0; }

	if (List->Buttons[9].state == 1) {
        Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Planeur1.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[9].state = 0; }

	if (List->Buttons[10].state == 1) {
        Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Planeur2.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[10].state = 0; }

	if (List->Buttons[11].state == 1) {
        Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Grenouille.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[11].state = 0; }

	if (List->Buttons[12].state == 1) {
        Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Clignotant.ins");
        PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[12].state = 0; }

	if (List->Buttons[13].state == 1) {
        Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Canon.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[13].state = 0; }

	if (List->Buttons[14].state == 1) {
        Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Pulsar.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[14].state = 0; }

    if (List->Buttons[15].state == 1) {
        Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/JSP.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[15].state = 0; }

    if (List->Buttons[16].state == 1) {
        Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Sharingan.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		List->Buttons[16].state = 0; }

        if (List->Buttons[17].state == 1) {
        Clean(List,NumberOf);
        LoadRle(List,NumberOf,"map/Load.rle");
        PrintScene(renderer,List,MainVar,NumberOf);
        SDL_Delay(16);
        List->Buttons[17].state = 0; }

    if (List->Buttons[8].state == 1 && MainVar->timer == 0) {
		MainVar->timer = 1;
		strcpy(List->Buttons[8].text,"Arreter");
		//List->Buttons[11].state = 0;
		}

    if (List->Buttons[8].state == 0 && MainVar->timer >= 1) {
		MainVar->timer = 0;
		strcpy(List->Buttons[8].text,"Lancer");
		}

	if (List->Direction[0].state == 1) {
		DispVar->Vtc = 1;
	}
	if (List->Direction[1].state == 1) {
		DispVar->Vtc = -1;
	}
	if (List->Direction[2].state == 1) {
		DispVar->Hzt = -1;
	}
	if (List->Direction[3].state == 1) {
		DispVar->Hzt = 1;
	}

}

void HandleKeyDown(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar) {
    // quit
    if (event->key.keysym.sym == SDLK_ESCAPE) {
        MainVar->run = 0;
    }

    //start / Stop
    if (event->key.keysym.sym == SDLK_SPACE && MainVar->space == 0) {
        if (MainVar->timer == 0) {
            List->Buttons[8].state = 1;
            strcpy(List->Buttons[8].text,"Arreter");
            MainVar->timer = 1 ;
        }
        else {
            MainVar->timer = 0;
            List->Buttons[8].state = 0;
            strcpy(List->Buttons[8].text,"Lancer");
        }
        MainVar->space = 1;
    }

    //reload
    if (event->key.keysym.sym == SDLK_r) {
        Clean(List,NumberOf);
    }

    //Save map
    if (event->key.keysym.sym == SDLK_k) {
        SaveMap(List, NumberOf,"map/buffer.ins");
    }

    //Load map
    if (event->key.keysym.sym == SDLK_l) {
        LoadMap(List, NumberOf,"map/buffer.ins");
        PrintScene(renderer,List,MainVar,NumberOf);
    }

    // MainVar->timer
    if (event->key.keysym.sym == SDLK_m && MainVar->ctrl == 0) {
        NumberOf->Time +=1;
        MainVar->ctrl = 1;
    }

    if (event->key.keysym.sym == SDLK_p && NumberOf->Time > 2 && MainVar->shift == 0) {
        NumberOf->Time -=1;
        MainVar->shift = 1;
    }

    //arrows
    if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_q) {
        DispVar->Hzt = 1;
        MainVar->pressed = 1;
    }
    else if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d) {
        DispVar->Hzt = -1;
        MainVar->pressed = 1;
    }
    if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_z) {
        DispVar->Vtc = 1;
        MainVar->pressed = 1;
    }
    else if (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s) {
        DispVar->Vtc = -1;
        MainVar->pressed = 1;
    }
    //zoom
    if (event->key.keysym.sym == SDLK_LSHIFT) {
        DispVar->Zm = 0.1;
        MainVar->pressed = 1;
        //Hzt = -0.4;
        //Vtc = -0.4;
    }
    else if (event->key.keysym.sym == SDLK_LCTRL) {
        DispVar->Zm = -0.1;
        MainVar->pressed = 1;
        //Hzt = -0.1;
        //Vtc = -0.1;
    }
}

void HandleKeyUp(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar) {
    //start stop
    if (event->key.keysym.sym == SDLK_SPACE) MainVar->space = 0;

    if (event->key.keysym.sym == SDLK_c) {
        MainVar->loc.scale = MainVar->resy/NumberOf->Lines;
        MainVar->loc.locx = 0;
        MainVar->loc.locy = 0;
    }

    //Timer
    if (event->key.keysym.sym == SDLK_m) {
        MainVar->ctrl = 0;
    }

    if (event->key.keysym.sym == SDLK_p) {
        MainVar->shift = 0;
    }

    //arrows
    if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_q) {
        DispVar->Hzt = 0;
        MainVar->pressed = 0;
    }
    if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d) {
        DispVar->Hzt = 0;
        MainVar->pressed = 0;
    }
    if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_z) {
        DispVar->Vtc = 0;
        MainVar->pressed = 0;
    }
    if (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s) {
        DispVar->Vtc = 0;
        MainVar->pressed = 0;
    }

    //zoom
    if (event->key.keysym.sym == SDLK_LSHIFT) {
        DispVar->Zm = 0;
        DispVar->Hzt = 0;
        DispVar->Vtc = 0;
        MainVar->pressed = 0;

    }
    if (event->key.keysym.sym == SDLK_LCTRL) {
        DispVar->Zm = 0;
        DispVar->Hzt = 0;
        DispVar->Vtc = 0;
        MainVar->pressed = 0;

    }
}

void FindCase(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar) {
    /*methode 1 (WIP) for cases
    Compare = CompareChunk(List->Cases,NumberOf, loc, event->button.x,event->button.y);
    if (Compare.x != -1) {
        if (List->Cases[Compare.y][Compare.x].state == 0) List->Cases[Compare.y][Compare.x].nextstate = 1;
        else List->Cases[Compare.y][Compare.x].nextstate = 0;
        click = 1;
    }*/

    //methode 2 for cases
    for (int j=0; j<NumberOf->Buttons+NumberOf->ButtonLeft; j++) {
        if (List->Buttons[j].cornx <= event->button.x && event->button.x <= List->Buttons[j].cornx + List->Buttons[j].sizex
        && List->Buttons[j].corny <= event->button.y && event->button.y <= List->Buttons[j].corny+List->Buttons[j].sizey) {
            if (List->Buttons[j].state == 0) List->Buttons[j].state = 1;
            else List->Buttons[j].state = 0;
            MainVar->click = 1;
        }
    }
}

void FinDirection(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar) {
    //for directions
    for (int k=0; k<NumberOf->Direction-2; k++) {
        if (List->Direction[k].cornx <= event->button.x
        && event->button.x <= List->Direction[k].cornx + List->Direction[k].sizex
        && List->Direction[k].corny <= event->button.y
        && event->button.y <= List->Direction[k].corny + List->Direction[k].sizey) {
            if (List->Direction[k].state == 0) List->Direction[k].state = 1;
            else List->Direction[k].state = 0;
            MainVar->click = 1;
        }
    }
}

void PlaceCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar) {
    //for placing cells
    while(event->type != SDL_MOUSEBUTTONUP) {
        for (int i=0; i<NumberOf->Lines; i++) {
            for (int j=0; j<NumberOf->Cols; j++) {
                if ((List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+(MainVar->resx/2-MainVar->loc.scale*NumberOf->Cols/2) <= event->button.x
                && (List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale +(MainVar->resx/2-MainVar->loc.scale*NumberOf->Cols/2) >= event->button.x
                && (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1) +(MainVar->resy/2-MainVar->loc.scale*NumberOf->Lines/2) <= event->button.y
                && (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+MainVar->loc.scale +(MainVar->resy/2-MainVar->loc.scale*NumberOf->Lines/2) >= event->button.y) {
                    List->Cases[i][j].nextstate = 1;
                    MainVar->timer =0;
                    PrintScene(renderer,List,MainVar,NumberOf);
                }
            }
        }
        SDL_PollEvent(event);
    }
}

void RemoveCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar) {
    while(event->type != SDL_MOUSEBUTTONUP) {
        for (int i=0; i<NumberOf->Lines; i++) {
            for (int j=0; j<NumberOf->Cols; j++) {
                if ((List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+(MainVar->resx/2-MainVar->loc.scale*NumberOf->Cols/2) <= event->button.x
                && (List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale +(MainVar->resx/2-MainVar->loc.scale*NumberOf->Cols/2) >= event->button.x
                && (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1) +(MainVar->resy/2-MainVar->loc.scale*NumberOf->Lines/2) <= event->button.y
                && (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+MainVar->loc.scale +(MainVar->resy/2-MainVar->loc.scale*NumberOf->Lines/2) >= event->button.y) {
                    List->Cases[i][j].nextstate = 0;
                    MainVar->timer =0;
                    PrintScene(renderer,List,MainVar,NumberOf);
                }
            }
        }
        SDL_PollEvent(event);
    }
}

void LoadStdin(St_List *List, Grid *NumberOf) {

    printf("Pipe detected, load initial map skipped\n");
    int FileLine;
    int FileCol;
    int resizex = 1;
    int resizey = 1;
    scanf("%d",&FileLine);
    scanf("%d",&FileCol);

    if (FileLine > NumberOf->Lines || FileCol > NumberOf->Cols) {
        NumberOf->Lines = FileLine+2;
        NumberOf->Cols = FileCol+2;
    } else {
        resizex = (NumberOf->Cols-FileCol)/2;
        resizey = (NumberOf->Lines-FileLine)/2;
    }

    //init Cases
    LoadCase(List,NumberOf);
    for (int i=resizex; i<FileLine+resizex; i++) {
        for (int j=resizey; j<FileCol+resizey; j++) {
            scanf("%d",&List->Cases[i][j].nextstate);
        }
    }
}

int concat(int x, int y) {
    int buff = 10;
    while(y >= buff)
        buff *= 10;
    return x * buff + y;        
}

/*WIP
void FreeCase(St_List *List,Grid *NumberOf) {
    for (int i=0; i<NumberOf->Lines; i++) {
        free(List->Cases[i]);
    }

}*/

/*
void CallThread(St_List *List, Grid *NumberOf, location loc, SDL_Event *event) {
	pthread_t Listhread[8];
	for (int i=0; i<8; i++) {
		pthread_create(&Listhread[i], NULL, myThreadFun, NULL);

	}
}

couple ThreadFunc1(St_List *List, Grid *NumberOf, location loc, SDL_Event *event, int NumberThread) {
	for (int i=0; i<NumberOf->Lines/8; i++) {
		for (int j=0; j<NumberOf->Cols/8; j++) {
			if ((List->Cases[i][j].posx+MainVar->loc.locx)*(loc.scale+1) <= event->button.x
			&& (List->Cases[i][j].posx+MainVar->loc.locx)*(loc.scale+1)+MainVar->loc.scale >= event->button.x
			&& (List->Cases[i][j].posy+MainVar->loc.locy)*(loc.scale+1) <= event->button.y
			&& (List->Cases[i][j].posy+MainVar->loc.locy)*(loc.scale+1)+MainVar->loc.scale >= event->button.y) {
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

