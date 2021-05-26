#include "game_of_life_gui.h"

/*
Loading / Saving : -------------------------------------------------------------
*/

void LoadCase(St_List *List, Grid *NumberOf) {
	List->Cases = malloc(sizeof *List->Cases * NumberOf->Lines);
	assert(List->Cases);

	for (int i = 0; i < NumberOf->Lines; i++) {
		List->Cases[i] = malloc(sizeof *List->Cases[i] * NumberOf->Cols);
		assert(List->Cases[i]);
		for (int j = 0; j < NumberOf->Cols; j++) {
			List->Cases[i][j].posx = j;
			List->Cases[i][j].posy = i;
			List->Cases[i][j].nextstate = 0;
			List->Cases[i][j].state = 0;
		}
	}
}

void ReLoadCase(St_List *List, Grid *NumberOf) {
	Case **ListTmp;
	Case *Tmp;
	ListTmp = List->Cases;
	List->Cases = realloc(ListTmp, sizeof *List->Cases * NumberOf->Lines);
	assert(List->Cases);

	for (int i = 0; i < NumberOf->Lines; i++) {
		List->Cases[i] = Tmp;
		List->Cases[i] = realloc(Tmp, sizeof *List->Cases[i] * NumberOf->Cols);
		assert(List->Cases[i]);
		for (int j = 0; j < NumberOf->Cols; j++) {
			List->Cases[i][j].posx = j;
			List->Cases[i][j].posy = i;
			List->Cases[i][j].nextstate = 0;
			List->Cases[i][j].state = 0;
		}
	}
}

void SaveMap(St_List *List, Grid *NumberOf, char name[]) {
	FILE* MapFile = NULL;

	//open file
	MapFile = fopen(name, "w");

	if (MapFile == NULL) {
		List->Error[0].state = 1;
		strcpy(List->Error[0].text,"Fichier tampon manquant pour la sauvegarde");
		return;
	} 

	fseek(MapFile,0,SEEK_SET);

	fprintf(MapFile,"%d %d\n", NumberOf->Lines, NumberOf->Cols);
	for (int i=0; i<NumberOf->Lines; i++) {
		for (int j=0; j<NumberOf->Cols; j++) {
			fprintf(MapFile, "%d ", List->Cases[i][j].nextstate);
		}
	}
	fclose(MapFile);
}

void LoadMap(St_List *List, Grid *NumberOf, char name[]) {
	FILE* MapFile = NULL;
	int FileLines;
	int FileCols;
	int Resisx;
	int Resisy;

	Clean(List,NumberOf);    

	MapFile = fopen(name, "r+");
	if (MapFile == NULL) {
		List->Error[0].state = 1;
		strcpy(List->Error[0].text,"Fichier carte manquant");
		return;
	}
	fscanf(MapFile,"%d %d\n", &FileLines, &FileCols);

	if (FileCols > NumberOf->Cols || FileLines > NumberOf->Lines) {
		List->Error[0].state = 1;
		sprintf(List->Error[0].text,
			"Vous essayez d'ouvrir une carte de %d par %d, modifiez les param?res de votre carte principale",
			FileLines,
			FileCols);
	}
	else {
			Resisy = (NumberOf->Lines - FileLines)/2;
			Resisx = (NumberOf->Cols - FileCols)/2;
		//load
		for (int i=Resisy; i<FileLines+Resisy; i++) {
			for (int j=Resisx; j<FileCols+Resisx; j++) {
				fscanf(MapFile, "%d ", &List->Cases[i][j].nextstate);
			}
		}
	}
	fclose(MapFile);
}

void LoadButton(St_List *List, St_Var *MainVar, Grid *NumberOf) {

	strcpy(List->Buttons[0].text, "Quitter");
	strcpy(List->Buttons[1].text, "Nettoyer (r)");
	strcpy(List->Buttons[2].text, "Copier (k)");
	strcpy(List->Buttons[3].text, "Coller (l)");
	strcpy(List->Buttons[4].text, "Thorique ");
	strcpy(List->Buttons[5].text, "Fermee ");
	strcpy(List->Buttons[6].text, "Plus Vite (p)");
	strcpy(List->Buttons[7].text, "Moins Vite (m)");
	strcpy(List->Buttons[8].text, "Lancer ");
	strcpy(List->Buttons[9].text, "Planeur ");
	strcpy(List->Buttons[10].text, "Cercle de Feu");
	strcpy(List->Buttons[11].text, "Grenouille ");
	strcpy(List->Buttons[12].text, "Clignotant ");
	strcpy(List->Buttons[13].text, "Canon ");
	strcpy(List->Buttons[14].text, "Pulsar ");
	strcpy(List->Buttons[15].text, "JSP    ");
	strcpy(List->Buttons[16].text, "Sharingan");
	strcpy(List->Buttons[17].text, "Drift");
	strcpy(List->Buttons[18].text, "Scorpion");
	strcpy(List->Buttons[19].text, "Scarabee");
	strcpy(List->Buttons[20].text, "LightSpeed");
	strcpy(List->Buttons[21].text, "Spirale");
	strcpy(List->Buttons[22].text, "Expantion");
	strcpy(List->Buttons[23].text, "Loop");
	strcpy(List->Buttons[24].text, "Load rle");
	strcpy(List->ButtonSize[0].text, "500x500");
	strcpy(List->ButtonSize[1].text, "400x400");
	strcpy(List->ButtonSize[2].text, "200x200");
	strcpy(List->ButtonSize[3].text, "100x100");
	strcpy(List->ButtonSize[4].text, " 50x50 ");
	strcpy(List->ButtonSize[5].text, " 10x10 ");
	strcpy(List->ButtonSize[6].text, "Manuel");
	strcpy(List->ButtonSize[7].text, "Grille");

	strcpy(List->Error[0].text, "Augmentez la taille de votre carte dans les parametres");
	strcpy(List->Error[1].text, "X");

	for (int i=0; i<NumberOf->Buttons; i++) {
		List->Buttons[i].state = 0;
		List->Buttons[i].sizex = MainVar->resx/9;
		List->Buttons[i].sizey = MainVar->resy/20;
		List->Buttons[i].resx = MainVar->resx;
		List->Buttons[i].resy = MainVar->resy;
		List->Buttons[i].cornx = MainVar->resx-List->Buttons[i].sizex-10;
		List->Buttons[i].corny = 10 + i*MainVar->resy/20+i;
	}

	for (int i=NumberOf->Buttons; i<NumberOf->Buttons+NumberOf->ButtonLeft; i++) {
		List->Buttons[i].state = 0;
		List->Buttons[i].sizex = MainVar->resx/9;
		List->Buttons[i].sizey = MainVar->resy/20;
		List->Buttons[i].resx = MainVar->resx;
		List->Buttons[i].resy = MainVar->resy;
		List->Buttons[i].cornx = 10;
		List->Buttons[i].corny = 10 + (i-NumberOf->Buttons)*MainVar->resy/20+(i-NumberOf->Buttons);
	}

	for (int i=0; i<NumberOf->ButtonSize; i++) {
		List->ButtonSize[i].state = 0;
		List->ButtonSize[i].sizex = MainVar->resx/9;
		List->ButtonSize[i].sizey = MainVar->resy/20;
		List->ButtonSize[i].resx = MainVar->resx;
		List->ButtonSize[i].resy = MainVar->resy;
		List->ButtonSize[i].cornx = MainVar->resx-MainVar->resx/9-10;
		List->ButtonSize[i].corny = MainVar->resy-(30+(i+1) * MainVar->resy/20 +i);
		List->ButtonSize[i].visual = 0;

	}

	List->ButtonSize[6].cornx = 10;
	List->ButtonSize[6].corny = MainVar->resy-(20+MainVar->resy/20);

	List->ButtonSize[7].cornx = MainVar->resx-List->ButtonSize[7].sizex-10;
	List->ButtonSize[7].corny = List->Buttons[8].corny + (List->ButtonSize[5].corny - List->Buttons[8].corny)/2;

	List->Buttons[4].state = 1;

	//popup error
	List->Error[0].state = 0;
	List->Error[0].sizex = MainVar->resx-20;
	List->Error[0].sizey = 50;
	List->Error[0].cornx = 10;
	List->Error[0].corny = MainVar->resy-50-10;

	//close error
	List->Error[1].state = 0;
	List->Error[1].sizex = 50;
	List->Error[1].sizey = 50;
	List->Error[1].cornx = MainVar->resx-60;
	List->Error[1].corny = MainVar->resy-60;
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
	if (MapFile == NULL) {
		List->Error[0].state = 1;
		strcpy(List->Error[0].text,"Fichier carte manquant");
		return;
	}

	//load
	BuffChar1 = fgetc(MapFile);
	while (BuffChar1 != EOF) {
		//printf("%c",BuffChar1 );
		if (BuffChar1 == 'x' || BuffChar1 == '#') {
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
	
	if (FileCols > NumberOf->Cols || FileLines > NumberOf->Lines) {
	List->Error[0].state = 1;
	sprintf(List->Error[0].text,
		"Vous essayez d'ouvrir une carte de %d par %d, modifiez les parametres de votre carte principale",
		FileLines,
		FileCols);
	}
	fclose(MapFile);
}

void LoadBackground(SDL_Renderer *renderer, St_Var *MainVar) {

	int diffx = MainVar->resx-MainVar->resy;
	SDL_Rect RectBack = {diffx/2,0,MainVar->resy,MainVar->resy};
	MainVar->RectBack = RectBack;
	SDL_Surface *surface = SDL_LoadBMP("rsc/CyLogo.bmp");
	if (surface == NULL) printf("error loading texture");
	MainVar->TexBack = SDL_CreateTextureFromSurface(renderer,surface);
}

/*
Interact : ---------------------------------------------------------------------
*/

int FindButton(SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar) {

	//find button pressed
	for (int j=0; j<NumberOf->Buttons+NumberOf->ButtonLeft; j++) {
		if (List->Buttons[j].cornx <= event->button.x && event->button.x <= List->Buttons[j].cornx + List->Buttons[j].sizex
		&& List->Buttons[j].corny <= event->button.y && event->button.y <= List->Buttons[j].corny+List->Buttons[j].sizey) {
			if (List->Buttons[j].state == 0) List->Buttons[j].state = 1;
			else if (j!= 4 && j!=5) List->Buttons[j].state = 0;
			MainVar->click = 1;
			MainVar->ButtonChanged = 1;
			return 1;
		}
	}

	for (int j=0; j<NumberOf->ButtonSize; j++) {
		if (List->ButtonSize[j].cornx <= event->button.x && event->button.x <= List->ButtonSize[j].cornx + List->ButtonSize[j].sizex
		&& List->ButtonSize[j].corny <= event->button.y && event->button.y <= List->ButtonSize[j].corny+List->ButtonSize[j].sizey) {
			if (List->ButtonSize[j].state == 0) List->ButtonSize[j].state = 1;
			else if (j!= 4 && j!=5) List->ButtonSize[j].state = 0;
			MainVar->click = 1;
			MainVar->ButtonChanged = 1;
			return 1;
		}
	}

	if (List->Error[1].cornx <= event->button.x && event->button.x <= List->Error[1].cornx + List->Error[1].sizex
	&& List->Error[1].corny <= event->button.y && event->button.y <= List->Error[1].corny+List->Error[1].sizey) {
		if (List->Error[0].state == 0) List->Error[0].state = 1;
		else List->Error[0].state = 0;
		MainVar->click = 1;
		MainVar->ButtonChanged = 1;
		return 1;
	}


	return 0;
}

void PlaceCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar) {
	/*/methode 1 (WIP) for cells
	Couple Compare;
	Compare = CompareChunk(List,NumberOf, MainVar, event->button.x,event->button.y);
	if (Compare.x != -1) {
		List->Cases[Compare.y][Compare.x].nextstate = 1;
		MainVar->timer = 0;
		PrintScene(renderer,List,MainVar,NumberOf);
	}/*/

	//methode 2 for placing cells
	while(event->type != SDL_MOUSEBUTTONUP) {
		for (int i=0; i<NumberOf->Lines; i++) {
			for (int j=0; j<NumberOf->Cols; j++) {
				if ((List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+(MainVar->resx/2-(MainVar->loc.scale+1)*NumberOf->Cols/2) <= event->button.x
				&& (List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale +(MainVar->resx/2-(MainVar->loc.scale+1)*NumberOf->Cols/2) >= event->button.x
				&& (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1) +(MainVar->resy/2-(MainVar->loc.scale+1)*NumberOf->Lines/2) <= event->button.y
				&& (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+MainVar->loc.scale +(MainVar->resy/2-(MainVar->loc.scale+1)*NumberOf->Lines/2) >= event->button.y) {
					List->Cases[i][j].nextstate = 1;
					MainVar->timer =0;
					PrintScene(renderer,List,MainVar,NumberOf);
				}
			}
		}
		SDL_PollEvent(event);
	}//
}

void RemoveCell(SDL_Renderer *renderer, SDL_Event *event, St_List *List, Grid *NumberOf, St_Var *MainVar) {
	while(event->type != SDL_MOUSEBUTTONUP) {
		for (int i=0; i<NumberOf->Lines; i++) {
			for (int j=0; j<NumberOf->Cols; j++) {
				if ((List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+(MainVar->resx/2-(MainVar->loc.scale+1)*NumberOf->Cols/2) <= event->button.x
				&& (List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+MainVar->loc.scale +(MainVar->resx/2-(MainVar->loc.scale+1)*NumberOf->Cols/2) >= event->button.x
				&& (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1) +(MainVar->resy/2-(MainVar->loc.scale+1)*NumberOf->Lines/2) <= event->button.y
				&& (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+MainVar->loc.scale +(MainVar->resy/2-(MainVar->loc.scale+1)*NumberOf->Lines/2) >= event->button.y) {
					List->Cases[i][j].nextstate = 0;
					MainVar->timer =0;
					PrintScene(renderer,List,MainVar,NumberOf);
				}
			}
		}
		SDL_PollEvent(event);
	}
}

void ButtonFunc(SDL_Renderer *renderer, St_List *List, Grid *NumberOf, St_State *State, St_Var *MainVar) {
	if (List->Buttons[1].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		MainVar->ButtonChanged = 1;
		SDL_Delay(16);
		NumberOf->Gen = 0;
		List->Buttons[1].state = 0; }

	if (List->Buttons[2].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		SaveMap(List,NumberOf,"map/buffer.ins");
		MainVar->ButtonChanged = 1;
		SDL_Delay(16);
		List->Buttons[2].state = 0; }

	if (List->Buttons[3].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		LoadMap(List,NumberOf,"map/buffer.ins");
		MainVar->ButtonChanged = 1;
		SDL_Delay(16);
		List->Buttons[3].state = 0; }

	if (List->Buttons[4].state == 1 && State->Map == 1) {
		State->Map = 0;
		List->Buttons[5].state = 0; }

	if (List->Buttons[5].state == 1 && State->Map == 0) {
		State->Map = 1;
		List->Buttons[4].state = 0; }

	if (List->Buttons[6].state == 1 && NumberOf->Time > 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		NumberOf->Time -= 1;
		MainVar->ButtonChanged = 1;
		SDL_Delay(16);
		List->Buttons[6].state = 0; }

	if (List->Buttons[7].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		NumberOf->Time += 1;
		MainVar->ButtonChanged = 1;
		SDL_Delay(16);
		List->Buttons[6].state = 0;
		List->Buttons[7].state = 0; }

	if (List->Buttons[8].state == 1 && MainVar->timer == 0) {
		MainVar->timer = 1;
		strcpy(List->Buttons[8].text,"Arreter");
		}

	if (List->Buttons[8].state == 0 && MainVar->timer >= 1) {
		MainVar->timer = 0;
		strcpy(List->Buttons[8].text,"Lancer");
		}

	if (List->Buttons[9].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Planeur1.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[9].state = 0; }

	if (List->Buttons[10].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Planeur2.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[10].state = 0; }

	if (List->Buttons[11].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Grenouille.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[11].state = 0; }

	if (List->Buttons[12].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Clignotant.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[12].state = 0; }

	if (List->Buttons[13].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Canon.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[13].state = 0; }

	if (List->Buttons[14].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Pulsar.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[14].state = 0; }

	if (List->Buttons[15].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/JSP.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[15].state = 0; }

	if (List->Buttons[16].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Sharingan.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[16].state = 0; }

	if (List->Buttons[17].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Drift.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[17].state = 0; }

	if (List->Buttons[18].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Scorpion.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[18].state = 0; }

	if (List->Buttons[19].state == 1) {
		MainVar->ButtonChanged = 1;
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Scarabee.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[19].state = 0; }

	if (List->Buttons[20].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/LightSpeed.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[20].state = 0; }

	if (List->Buttons[21].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Spiral.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[21].state = 0; }

	if (List->Buttons[22].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Expansion.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[22].state = 0; }

	if (List->Buttons[23].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadMap(List,NumberOf,"map/Loop.ins");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[23].state = 0; }

	if (List->Buttons[24].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		LoadRle(List,NumberOf,"map/Load.rle");
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		List->Buttons[24].state = 0; }

	if (List->ButtonSize[0].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		ChangeMapSize(List,NumberOf,500,500);
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		for (int i=0; i<NumberOf->ButtonSize-1; i++) {
			List->ButtonSize[i].visual = 0;
		}
		List->ButtonSize[0].visual = 1;
		List->ButtonSize[0].state = 0; }

	if (List->ButtonSize[1].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		ChangeMapSize(List,NumberOf,400,400);
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		for (int i=0; i<NumberOf->ButtonSize-1; i++) {
			List->ButtonSize[i].visual = 0;
		}
		List->ButtonSize[1].visual = 1;
		List->ButtonSize[1].state = 0; }

	if (List->ButtonSize[2].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		ChangeMapSize(List,NumberOf,200,200);
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		for (int i=0; i<NumberOf->ButtonSize-1; i++) {
			List->ButtonSize[i].visual = 0;
		}
		List->ButtonSize[2].visual = 1;
		List->ButtonSize[2].state = 0; }

	if (List->ButtonSize[3].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		ChangeMapSize(List,NumberOf,100,100);
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		for (int i=0; i<NumberOf->ButtonSize-1; i++) {
			List->ButtonSize[i].visual = 0;
		}
		List->ButtonSize[3].visual = 1;
		List->ButtonSize[3].state = 0; }

	if (List->ButtonSize[4].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		ChangeMapSize(List,NumberOf,50,50);
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		for (int i=0; i<NumberOf->ButtonSize-1; i++) {
			List->ButtonSize[i].visual = 0;
		}
		List->ButtonSize[4].visual = 1;
		List->ButtonSize[4].state = 0; }

	if (List->ButtonSize[5].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		ChangeMapSize(List,NumberOf,10,10);
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		for (int i=0; i<NumberOf->ButtonSize-1; i++) {
			List->ButtonSize[i].visual = 0;
		}
		List->ButtonSize[5].visual = 1;
		List->ButtonSize[5].state = 0; }

	if (List->ButtonSize[6].state == 1) {
		PrintScene(renderer,List,MainVar,NumberOf);
		Clean(List,NumberOf);
		ChangeMapSize(List,NumberOf,500,500);
		LoadMap(List,NumberOf,"map/MenuHV2.ins");
		MainVar->loc.scale = MainVar->resy/NumberOf->Lines;
		MainVar->loc.locx = 0;
		MainVar->loc.locy = 0;
		MainVar->timer = 0;
		List->ButtonSize[8].state = 0;
		MainVar->ButtonChanged = 1;
		NumberOf->Gen = 0;
		SDL_Delay(16);
		for (int i=0; i<NumberOf->ButtonSize-1; i++) {
			List->ButtonSize[i].visual = 0;
		}
		List->ButtonSize[1].visual = 1;
		List->ButtonSize[6].state = 0; }

	if (List->ButtonSize[7].state == 1) {
		MainVar->Ruled = 0;
		List->ButtonSize[7].visual = 1;
	}
	else {
		MainVar->Ruled = 1;
		List->ButtonSize[7].visual = 0;
	}
}

int HandleKeyDown(SDL_Renderer *renderer, St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar) {
	
	//Quit
	if (event->key.keysym.sym == SDLK_ESCAPE) MainVar->run = 0;

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
		return 1;
	}

	//reload
	if (event->key.keysym.sym == SDLK_r) {
		Clean(List,NumberOf);
		PrintScene(renderer,List,MainVar,NumberOf);
		SDL_Delay(16);
		NumberOf->Gen = 0;
		List->Buttons[1].state = 0;
		return 1;
	}

	//Save map
	if (event->key.keysym.sym == SDLK_k) {
		SaveMap(List, NumberOf,"map/buffer.ins");
		return 1;
	}

	//Load map
	if (event->key.keysym.sym == SDLK_l) {
		LoadMap(List, NumberOf,"map/buffer.ins");
		PrintScene(renderer,List,MainVar,NumberOf);
		return 1;
	}

	// MainVar timer
	if (event->key.keysym.sym == SDLK_m && MainVar->ctrl == 0) {
		List->Buttons[7].state = 1;
		MainVar->ctrl = 1;
		return 1;
	}

	if (event->key.keysym.sym == SDLK_p && NumberOf->Time > 1 && MainVar->shift == 0) {
		List->Buttons[6].state = 1;
		MainVar->shift = 1;
		return 1;
	}

	//arrows
	if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_q) {
		DispVar->Hzt = 1/MainVar->loc.scale;
		MainVar->pressed = 1;
		return 1;
	}
	else if (event->key.keysym.sym == SDLK_RIGHT || event->key.keysym.sym == SDLK_d) {
		DispVar->Hzt = -1/MainVar->loc.scale;
		MainVar->pressed = 1;
		return 1;
	}
	if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_z) {
		DispVar->Vtc = 1/MainVar->loc.scale;
		MainVar->pressed = 1;
		return 1;
	}
	else if (event->key.keysym.sym == SDLK_DOWN || event->key.keysym.sym == SDLK_s) {
		DispVar->Vtc = -1/MainVar->loc.scale;
		MainVar->pressed = 1;
		return 1;
	}
}

void HandleKeyUp(St_List *List, St_Var *MainVar, Grid *NumberOf, SDL_Event *event, Disp *DispVar) {
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
}

int ChangeMapSize(St_List *List, Grid *NumberOf, int NewLines, int NewCols) {
	
		NumberOf->Lines = NewLines;
		NumberOf->Cols = NewCols;
		ReLoadCase(List,NumberOf);
}

int concat(int x, int y) {
	int buff = 10;
	while(y >= buff)
		buff *= 10;
	return x * buff + y;
}

/*
Printing : ---------------------------------------------------------------------
*/

void PrintScene(SDL_Renderer *renderer,St_List *List, St_Var *MainVar, Grid *NumberOf) {

	
	SDL_SetRenderDrawColor(renderer, 80,80,80,255);
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer,MainVar->TexBack,NULL,&MainVar->RectBack);
	PrintCases(renderer,List,MainVar,NumberOf);
	if (MainVar->ButtonChanged) RefreshButtons(renderer,List,MainVar,NumberOf);
	PrintButtons(renderer,List,MainVar,NumberOf);
	PrintCount(renderer,List,MainVar,NumberOf);
	PrintError(renderer,List,MainVar,NumberOf);

	SDL_RenderPresent(renderer);
}

void PrintCases(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf) {
	
	for (int i=0; i<NumberOf->Lines; i++) {
		for (int j=0; j<NumberOf->Cols; j++) {
			List->Cases[i][j].state = List->Cases[i][j].nextstate;
			if (List->Cases[i][j].state == 1 && MainVar->timer != 0) {
				SDL_SetRenderDrawColor(renderer, MainVar->MainColor.r,MainVar->MainColor.g,MainVar->MainColor.b,255);
			}
			else if (List->Cases[i][j].state == 1 && MainVar->timer == 0) {
				SDL_SetRenderDrawColor(renderer,MainVar->SecondColor.r,MainVar->SecondColor.g,MainVar->SecondColor.b,255);
			}
			else SDL_SetRenderDrawColor(renderer, 40,40,40,255);

			SDL_Rect RectCase = {(List->Cases[i][j].posx+MainVar->loc.locx)*(MainVar->loc.scale+1)+(MainVar->resx/2-(MainVar->loc.scale+1)*NumberOf->Cols/2),
								 (List->Cases[i][j].posy+MainVar->loc.locy)*(MainVar->loc.scale+1)+(MainVar->resy/2-(MainVar->loc.scale+1)*NumberOf->Lines/2),
								  MainVar->loc.scale+2*MainVar->Ruled,MainVar->loc.scale+2*MainVar->Ruled};
			SDL_RenderFillRect(renderer,&RectCase);
		}
	}
}

void RefreshButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf) {

	int w;
	int h;
	SDL_Color White = {255,255,255,255};

	//refresh button right
	for (int i=0; i<NumberOf->Buttons; i++) {
		if (i==8 && List->Buttons[i].state == 0) {
			List->Buttons[i].Color.r = MainVar->SecondColor.r;
			List->Buttons[i].Color.g = MainVar->SecondColor.g;
			List->Buttons[i].Color.b = MainVar->SecondColor.b;
			List->Buttons[i].Color.a = 255;
		}
		else if (List->Buttons[i].state == 1) { 
			List->Buttons[i].Color.r = MainVar->MainColor.r;
			List->Buttons[i].Color.g = MainVar->MainColor.g;
			List->Buttons[i].Color.b = MainVar->MainColor.b;
			List->Buttons[i].Color.a = 255;
		}
		else {
			List->Buttons[i].Color.r = 60;
			List->Buttons[i].Color.g = 60;
			List->Buttons[i].Color.b = 60;
			List->Buttons[i].Color.a = 255;
		}
		SDL_Rect RectButton = {List->Buttons[i].cornx,List->Buttons[i].corny,List->Buttons[i].sizex, List->Buttons[i].sizey};
		TTF_SizeText(MainVar->police,List->Buttons[i].text,&w,&h);
		SDL_Rect RectText = {List->Buttons[i].cornx+10,List->Buttons[i].corny+10,w,h};
		SDL_Surface *surface = TTF_RenderText_Blended(MainVar->police,List->Buttons[i].text,White);
		List->Buttons[i].Texture = SDL_CreateTextureFromSurface(renderer, surface);
		List->Buttons[i].Rect = RectButton;
		List->Buttons[i].RectText = RectText;		
		SDL_FreeSurface(surface);
	}

	//refresh button left
	for (int i=NumberOf->Buttons; i<NumberOf->Buttons+NumberOf->ButtonLeft; i++) {
		if (List->Buttons[i].state == 1) {
			List->Buttons[i].Color.r = MainVar->SecondColor.r;
			List->Buttons[i].Color.g = MainVar->SecondColor.g;
			List->Buttons[i].Color.b = MainVar->SecondColor.b;
			List->Buttons[i].Color.a = 255;
		}

		else {
			List->Buttons[i].Color.r = 60;
			List->Buttons[i].Color.g = 60;
			List->Buttons[i].Color.b = 60;
			List->Buttons[i].Color.a = 255;
		}
		SDL_Rect RectButton = {List->Buttons[i].cornx,List->Buttons[i].corny,List->Buttons[i].sizex, List->Buttons[i].sizey};
		TTF_SizeText(MainVar->police,List->Buttons[i].text,&w,&h);
		SDL_Rect RectText = {List->Buttons[i].cornx+10,List->Buttons[i].corny+10,w,h};
		SDL_Surface *surface = TTF_RenderText_Blended(MainVar->police,List->Buttons[i].text,White);
		List->Buttons[i].Texture = SDL_CreateTextureFromSurface(renderer, surface);
		List->Buttons[i].Rect = RectButton;
		List->Buttons[i].RectText = RectText;
		SDL_FreeSurface(surface);
	}

	//refresh button Size
	for (int i=0; i<NumberOf->ButtonSize; i++) {
		if (List->ButtonSize[i].visual == 1) {
			List->ButtonSize[i].Color.r = MainVar->MainColor.r;
			List->ButtonSize[i].Color.g = MainVar->MainColor.g;
			List->ButtonSize[i].Color.b = MainVar->MainColor.b;
			List->ButtonSize[i].Color.a = 255;
		}

		else {
			List->ButtonSize[i].Color.r = 60;
			List->ButtonSize[i].Color.g = 60;
			List->ButtonSize[i].Color.b = 60;
			List->ButtonSize[i].Color.a = 255;
		}
		SDL_Rect RectButton = {List->ButtonSize[i].cornx,List->ButtonSize[i].corny,List->ButtonSize[i].sizex, List->ButtonSize[i].sizey};
		TTF_SizeText(MainVar->police,List->ButtonSize[i].text,&w,&h);
		SDL_Rect RectText = {List->ButtonSize[i].cornx+10,List->ButtonSize[i].corny+10,w,h};
		SDL_Surface *surface = TTF_RenderText_Blended(MainVar->police,List->ButtonSize[i].text,White);
		List->ButtonSize[i].Texture = SDL_CreateTextureFromSurface(renderer, surface);
		List->ButtonSize[i].Rect = RectButton;
		List->ButtonSize[i].RectText = RectText;
		SDL_FreeSurface(surface);
	}

	MainVar->ButtonChanged = 0;

}

void PrintButtons(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf) {

	//define text color
	SDL_Color White = {255,255,255,255};

	//Print Buttons part 1
	for (int i=0; i<NumberOf->Buttons+NumberOf->ButtonLeft; i++) {
		SDL_SetRenderDrawColor(renderer,List->Buttons[i].Color.r,List->Buttons[i].Color.g,List->Buttons[i].Color.b,List->Buttons[i].Color.a);
		SDL_RenderFillRect(renderer,&List->Buttons[i].Rect);
		SDL_RenderCopy(renderer, List->Buttons[i].Texture, NULL, &List->Buttons[i].RectText);
	}
	
	for (int i=0; i<NumberOf->ButtonSize; i++) {
		SDL_SetRenderDrawColor(renderer,List->ButtonSize[i].Color.r,List->ButtonSize[i].Color.g,List->ButtonSize[i].Color.b,List->ButtonSize[i].Color.a);
		SDL_RenderFillRect(renderer,&List->ButtonSize[i].Rect);
		SDL_RenderCopy(renderer, List->ButtonSize[i].Texture, NULL, &List->ButtonSize[i].RectText);
	}
}

void PrintCount(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf){
	
	SDL_Color White = {255,255,255,255};

	//Print Count Generations
	char CharGen[30];
	sprintf(CharGen, "%d", NumberOf->Gen);
	int w;
	int h;

	TTF_SizeText(MainVar->police40,CharGen,&w,&h);
	SDL_Surface *surface = TTF_RenderText_Blended(MainVar->police40,CharGen,White);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect RectButton = {List->Buttons[0].resx/2-w/2,10,w,h};
	SDL_RenderCopy(renderer, texture, NULL, &RectButton);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void PrintError(SDL_Renderer *renderer, St_List *List,St_Var *MainVar, Grid *NumberOf) {
	
	SDL_Color White = {255,255,255,255};

	int w;
	int h;

	// Print Error
	if (List->Error[0].state == 1) {
		SDL_SetRenderDrawColor(renderer,155,0,0,255);
		SDL_Rect RectError = {List->Error[0].cornx,List->Error[0].corny,List->Error[0].sizex, List->Error[0].sizey};
		TTF_SizeText(MainVar->police,List->Error[0].text,&w,&h);
		SDL_Rect RectText = {List->Error[0].cornx+10,List->Error[0].corny+10,w,h};
		SDL_RenderFillRect(renderer,&RectError);
		SDL_Surface *surface = TTF_RenderText_Blended(MainVar->police,List->Error[0].text,White);
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, &RectText);

		SDL_Rect RectClose = {List->Error[1].cornx,List->Error[1].corny,List->Error[1].sizex, List->Error[1].sizey};
		surface = SDL_LoadBMP("rsc/Close.bmp");
		if (surface == NULL) printf("failed to open a texture %s\n", List->Error[1].img);
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_RenderCopy(renderer, texture, NULL, &RectClose);

		SDL_DestroyTexture(texture);
		SDL_FreeSurface(surface);
	}
}

/*
//Cleaning : -------------------------------------------------------------------
*/

void Clean(St_List *List, Grid *NumberOf) {
	for (int i=0; i<NumberOf->Lines; i++) {
		for (int j=0; j<NumberOf->Cols; j++) {
			List->Cases[i][j].nextstate = 0;
		}
	}
}

/*
//Work In Progress : -----------------------------------------------------------
*/

Couple CompareChunk(St_List *List, Grid *NumberOf, St_Var *MainVar, int sourx, int soury) {
	
    int cornx = MainVar->loc.locx*(MainVar->loc.scale+1)+(MainVar->resx/2-MainVar->loc.scale*NumberOf->Cols/2);
    int corny = MainVar->loc.locy*(MainVar->loc.scale+1)+(MainVar->resy/2-MainVar->loc.scale*NumberOf->Lines/2);
    int dCol = NumberOf->Cols/2-1;
    int dLine = NumberOf->Lines/2-1;
    int i = dCol;
    int j = dLine;
    int io = 0;
    int jo = 0;
    int countchunk = 0;

    Couple Ret;
	Ret.x = -2;
	Ret.y = -2;

	START:
    printf(" io %d, i %d, jo %d, j %d\n",io, i, jo, j );
	printf("chunk 1\n");
    if ((List->Cases[j][i].posx+cornx) <= sourx
    && (List->Cases[j][i].posx+cornx+MainVar->loc.scale) >= sourx
    && (List->Cases[j][i].posy+corny) <= soury
    && (List->Cases[j][i].posy+corny+MainVar->loc.scale) >= soury) {
        Ret.x = i;
        Ret.y = j;
        printf("terminada ------------------\n");
        return Ret;
    }
	if ((List->Cases[jo][io].posx+cornx) <= sourx
	&& (List->Cases[jo][i].posx+cornx+MainVar->loc.scale) >= sourx
    && (List->Cases[jo][io].posy+corny) <= soury
    && (List->Cases[j][io].posy+corny+MainVar->loc.scale) >= soury) {
		i/=2;
		j/=2;
        countchunk = 0;
        printf("trouvé\n");
        goto START;
	}
    else {
        if (countchunk == 4) {
            Ret.x = -1;
            Ret.y = -1;
            printf("pas trouvé ------------------\n");
            return Ret;
        }
        else countchunk ++;
    }

    if (countchunk == 1) {
        io += i;
        i+= i;
        
        printf("chunk 1\n");
        goto START;
    }
    else if (countchunk == 2) {
        jo += j;
        j+= j;
        
        printf("chunk 2\n");
        goto START;
    }
    else if (countchunk == 3) {
        i/=2;
        io -= i;
        printf("chunk 3\n");
        goto START;
    }


	else goto START;
}

