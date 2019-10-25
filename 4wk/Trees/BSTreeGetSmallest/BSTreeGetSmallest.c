
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	// TODO
	if (t == NULL) {
	    return NULL;
	}
	BSTree curr = t;
	while (curr->left != NULL) {
	    curr=curr->left;
	}
	return curr;
}

