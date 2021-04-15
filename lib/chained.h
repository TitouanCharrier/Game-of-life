#ifndef CHAINED
#define CHAINED

typedef struct element {
	struct element *previous;
	int content;
	struct element *next;
}element;


element *ch_builder(element *previous, int content, element *next);

#endif