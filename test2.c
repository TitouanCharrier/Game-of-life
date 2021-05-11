#include "test2.h"

void myfunc(int* Coucou) {
	printf("Salut je suis la %d\n",*Coucou);
	int *Nouille = NULL;
	Nouille = malloc(100);
	printf("hello\n");
	*Coucou += 1;
}