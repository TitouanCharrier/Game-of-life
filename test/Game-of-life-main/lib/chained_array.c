#include "chained.h"
#include <stddef.h>

element *ch_insert(element *previous, int content, element *next) {
	
	element buffer;
	element *Buffer = &buffer;

	if (previous == NULL && next != NULL) {
		previous = next->previous;
	}

	else if (next == NULL && previous != NULL) {
		next = previous->next;
	}

	buffer.content = content;
	buffer.previous = previous;
	buffer.next = next;
	
	if (previous != NULL) {
		previous->next = Buffer;
	}
	if (next != NULL) {
		next->previous = Buffer;
	}

	return Buffer;

}

void ch_rm(element *Buffer) {

	if (Buffer->previous != NULL) {
		Buffer->previous->next = Buffer->next;
	}

	if (Buffer->next != NULL) {
		Buffer->next->previous = Buffer->previous;
	}
}

void ch_print(element *Buffer) {
	printf("prev : %p\n", Buffer->previous );
	printf("cont : %d\n", Buffer->content );
	printf("next : %p\n", Buffer->next );
	printf("\n");
}