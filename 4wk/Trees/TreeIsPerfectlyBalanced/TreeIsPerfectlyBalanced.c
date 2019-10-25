
#include <stdlib.h>

#include "tree.h"

int height (Tree t) {
    if (t == NULL) return 0;
    if (height(t->left) > height(t->right)) {
        return 1 + height(t->left);
    } else {
        return 1 + height(t->right);
    }
}

bool TreeIsPerfectlyBalanced(Tree t) {
	if (t == NULL) return true;
	
	if (height(t->left) > height(t->right) + 1) {
	    return false;
	} else if (height(t->right) > height(t->left) + 1) {
	    return false;
	} else {
	    return TreeIsPerfectlyBalanced(t->left) && TreeIsPerfectlyBalanced(t->right);
	}
}

