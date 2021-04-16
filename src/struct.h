#ifndef STRUCT
#define STRUCT

typedef struct Case {
	int posx;
	int posy;
	int state;
	int nextstate;
}Case;

typedef struct location {
	float scale;
	float locx;
	float locy;
}location;

#endif