
#include "list.h"

void reverseDLList(List l) {
	if (l == NULL) {
	    return;
	} else if (l->first == NULL) {
	    return;
	} else if (l->first->next == NULL) {
	    return;
	}
	
	Node curr = l->first;
	Node prev = NULL;
	Node after = l->first;
	l->last = curr;
	while (curr != NULL) {
	    after = curr->next;
	    curr->next = prev;
	    curr->prev = after;
	    
	    prev = curr;
	    curr = after;
	}
	l->first = prev;
}

