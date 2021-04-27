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
	int cornx;
	int corny;
	int sizex;
	int sizey;
	char text[50];
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
	long long int Gen;
}Grid;

typedef struct Disp {
	float Hzt;
	float Vtc;
	float Zm;
}Disp;


#endif
