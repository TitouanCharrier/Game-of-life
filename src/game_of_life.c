#include "game_of_life.h"

void LoadSettings(Grid *NumberOf,St_Var *MainVar) {

	FILE* MapFile = NULL;
	MapFile = fopen("settings.txt", "r+");
	if (MapFile == NULL) printf("ERROR : failed to open settings file\n");

	fscanf(MapFile,"Lignes : %d\n",&NumberOf->Lines);
	fscanf(MapFile,"Colonnes : %d\n",&NumberOf->Cols);
	fscanf(MapFile,"Couleur dominante rouge : %d\n",&MainVar->MainColor.r);
	fscanf(MapFile,"Couleur dominante vert : %d\n",&MainVar->MainColor.g);
	fscanf(MapFile,"Couleur dominante bleu : %d\n",&MainVar->MainColor.b);
	fscanf(MapFile,"Couleur secondaire rouge : %d\n",&MainVar->SecondColor.r);
	fscanf(MapFile,"Couleur secondaire vert : %d\n",&MainVar->SecondColor.g);
	fscanf(MapFile,"Couleur secondaire bleu : %d\n",&MainVar->SecondColor.b);

	fclose(MapFile);
}

int LoadStdin(St_List *List, Grid *NumberOf, St_Var *MainVar) {

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
	scanf("%d",&MainVar->limite);
	int mat;
	scanf("%d",&mat);
	if (mat) return 1;
	else return 0;
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

            //Rows
            if (i==0) {
                Rowinf = NumberOf->Lines-1;
                RowSup = i+1;
            }
            else if (i==NumberOf->Lines-1) {
                Rowinf = i-1;
                RowSup = 0;
            }
            else {
                Rowinf = i-1;
                RowSup = i+1;
            }

            //Columns
            if (j==0) {
                ColInf = NumberOf->Cols-1;
                ColSup = j+1;
            }
            else if (j==NumberOf->Cols-1) {
                ColInf = j-1;
                ColSup = 0;
            }
            else {
                ColInf = j-1;
                ColSup = j+1;
            }

            //Neighbours
            Neib = LC[i][ColSup].state+LC[i][ColInf].state
            +LC[RowSup][j].state+LC[Rowinf][j].state+LC[RowSup][ColSup].state
            +LC[Rowinf][ColSup].state+LC[RowSup][ColInf].state+LC[Rowinf][ColInf].state;


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