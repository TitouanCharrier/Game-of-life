#ifndef CHAINED
#define CHAINED

typedef struct element {
	struct element *previous;
	int content;
	struct element *next;
}element;


element *ch_insert(element *previous, int content, element *next);

void ch_print(element *Buffer);

#endif