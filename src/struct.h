#ifndef STRUCT
#define STRUCT
#include "SDL2/SDL_ttf.h"

typedef struct Case {
	int posx;
	int posy;
	int state;
	int nextstate;
}Case;


typedef struct St_Color {
	int r;
	int g;
	int b;
	int a;
}St_Color;


typedef struct Button {
	int resx;
	int resy;
	int cornx;
	int corny;
	int sizex;
	int sizey;
	char text[100];
	int state;
	int visual;
	char img[14];
	St_Color Color;
	SDL_Rect Rect;
	SDL_Texture *Texture;
	SDL_Rect RectText;
}Button;

typedef struct location {
	float scale;
	float locx;
	float locy;
}location;

typedef struct Couple {
	int x;
	int y;
}Couple;

typedef struct Grid {
	int Lines;
	int Cols;
	int Buttons;
	int Direction;
	int ButtonLeft;
	int ButtonSize;
	int Time;
	int Error;
	long long int Gen;
}Grid;

typedef struct Disp {
	float Hzt;
	float Vtc;
	float Zm;
}Disp;

typedef struct St_State {
	int Map;
	int Draw;
}St_State;

typedef struct St_List {
	Case **Cases;
	Button *Buttons;
	Button *Direction;
	Button *Error;
	Button *ButtonSize;
}St_List;

typedef struct St_Var {
	location loc;
	TTF_Font *police;
	TTF_Font *police40;
	TTF_Font *policeNbr;
	int timer;
	int run;
	int space;
	int click;
	int pressed;
	int ctrl;
	int shift;
	int resx;
	int resy;
	int limite;
	int begin;
	int ButtonChanged;
	int Ruled;
	SDL_Texture *TexBack;
	SDL_Rect RectBack;
}St_Var;

typedef struct St_Thread {
	SDL_Renderer *renderer;
	St_List *List;
	St_Var *MainVar;
	Grid *NumberOf;
	int tid;
}St_Thread;

#endif
