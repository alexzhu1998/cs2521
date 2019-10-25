
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree BSTreeInsert(BSTree t, int val) {
    
    BSTree search = t;
    BSTree new = malloc (sizeof(struct BSTNode));
    new->left = NULL;
    new->right = NULL;
    new->value = val; 
    
    if (search == NULL) {
        return new;
    }
    
    
    while (search != NULL) {
	    if (val < search->value) {
            if (search->left == NULL) {
                search->left = new;
                break;            
            } else {
                search = search->left;
            }
	    } else {
	        if (search->right == NULL) {
                search->right = new;
                break;
            } else {
                search = search->right;
            }

	    }
	}
	return t;
}

