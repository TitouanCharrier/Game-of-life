#ifndef STRUCT
#define STRUCT
#include "SDL2/SDL_ttf.h"

typedef struct Case {
	int posx;
	int posy;
	int state;
	int nextstate;
}Case;

typedef struct Button {
	int resx;
	int resy;
	int cornx;
	int corny;
	int sizex;
	int sizey;
	char text[100];
	int state;
	char img[14];
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
}St_List;

typedef struct St_Var {
	location loc;
	TTF_Font *police;
	TTF_Font *police40;
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
}St_Var;

#endif
