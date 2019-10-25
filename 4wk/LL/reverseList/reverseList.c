
#include "list.h"

void listReverse(List l) {
	if (l == NULL) {
	    return;
	} else if (l->head == NULL) {
	    return;
	} else if (l->head->next == NULL) {
	    return;
	}
	Node curr = l->head;
	Node prev = NULL;
	Node after = l->head->next;
	
	while (curr != NULL) {
	    
	    /*curr->next = prev;
	    prev = curr;
	    curr = after;
	    after = after->next;*/
	    
	    after = curr->next;
	    curr->next = prev;
	    prev = curr;
	    curr = after;
	}
	l->head = prev;
	
}

