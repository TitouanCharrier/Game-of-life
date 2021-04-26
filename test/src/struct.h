#ifndef STRUCT
#define STRUCT

typedef struct Case {
	int posx;
	int posy;
	int state;
	int nextstate;
}Case;

typedef struct Button {
	int resx;
	int resy;
	int sizex;
	int sizey;
	char text[50];
	int state;
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
}Grid;


#endif
