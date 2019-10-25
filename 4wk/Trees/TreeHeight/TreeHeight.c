
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    if (t == NULL) return -1;
    if (TreeHeight(t->left)>TreeHeight(t->right)) {
        return 1 + TreeHeight(t->left);
    } else {
        return 1 + TreeHeight(t->right);
    }
}

