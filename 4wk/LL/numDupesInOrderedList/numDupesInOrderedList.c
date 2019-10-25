#include "list.h"

int numDupesInOrderedList(List l) {
    if (l == NULL) {
        return 0;
    } else if (l->head == NULL) {
        return 0;
    }
	Node curr = l->head;
	Node prev = curr;
	int count = 0;
	while (curr != NULL) {
	    if (curr->value == prev->value && curr != prev) {
	        count++;
	    }
	    prev = curr;
	    curr = curr->next;
	}
	return count;
}

