
#include "list.h"

bool listIsOrdered(List l) {
	// TODO
	if (l == NULL) {
	    return true;
	} else if (l->head == NULL) {
	    return true;	
	} else if (l->head->next == NULL) {
	    return true;
	} 
	Node curr = l->head;
	
	for (curr = l->head; curr->next != NULL; curr = curr->next) {
	    if (curr->value > curr->next->value) {
	        break;
	    }
	}
	if (curr->next == NULL) {
	    return true;
	}
	
	for (curr = l->head; curr->next != NULL; curr = curr->next) {
	    if (curr->value < curr->next->value) {
	        break;
	    }
	}
	if (curr->next == NULL) {
	    return true;
	}
	return false;
}

