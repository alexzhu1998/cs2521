
#include <stdio.h>

#include "BSTree.h"

void BSTreePostfix(BSTree t) {
	// TODO
	if (t == NULL) return;
    BSTreePostfix(t->left);
    BSTreePostfix(t->right);
    printf("%d ", t->value);
}

