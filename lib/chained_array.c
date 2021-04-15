#include "chained.h"
#include <stddef.h>

element *ch_builder(element *previous, int content, element *next) {

	if (previous == NULL) {
		if (next != NULL) {
			previous = next->previous;
		}
	}

	else if (next == NULL) {
		if (previous != NULL) {
			next = previous->next;
		}
	}

	element buffer;
	element *Buffer = &buffer;
	
	buffer.content = content;
	buffer.previous = previous;
	buffer.next = next;

}