
#include <stdlib.h>

#include "BSTree.h"


int BSTreeNodeDepth(BSTree t, int key) {
    if (t == NULL) return -1;
    if (t->value == key) {
        return 0;
    } else if (key < t->value) {
        int ldepth = BSTreeNodeDepth(t->left,key);
        if (ldepth == -1) return -1;
        return ldepth +1;
    } else {
        int rdepth = BSTreeNodeDepth(t->right,key);
        if (rdepth == -1) return -1;
        return rdepth +1;
    }
}

