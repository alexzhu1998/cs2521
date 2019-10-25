
#include "list.h"

int listDeleteLargest(List l) {
    int temp;
    if (l->head == NULL) {
        return 0;
    } else if (l->head->next == NULL) {
        temp = l->head->value;
        free(l->head);
        l->head = NULL;
        return temp;
    }
    Node curr = l->head;
    Node prev = curr;
    int largest = curr->value;
    for (curr = l->head; curr!= NULL; curr= curr->next) {
        if (curr->value > largest) {
            largest = curr->value;
        }
    }
    
    curr = l->head;

    while (curr != NULL) {
        if (curr->value == largest) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }
    
    if (curr == l->head) {
        l->head = curr->next;
        curr->next = NULL;
        temp = curr->value;
        free(curr);
    } else if (curr->next == NULL) {
        prev->next = NULL;
        temp = curr->value;
        free(curr);
    } else {
        prev->next = curr->next;
        temp = curr->value;
        free(curr);
    }
	return temp;
}

