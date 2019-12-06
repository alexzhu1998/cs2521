// Binary Search Tree ADT implementation ... 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BSTree.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)

typedef struct Node {
   int  data;
   Tree left, right;
} Node;

// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   data(new) = it;
   left(new) = right(new) = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(Tree t, int depth) {
   if (t != NULL) {
      showTreeR(right(t), depth+1);
      int i;
      for (i = 0; i < depth; i++)
	 putchar('\t');            // TAB character
      printf("%d\n", data(t));
      showTreeR(left(t), depth+1);
   }
}

void showTree(Tree t) {
   showTreeR(t, 0);
}

// compute height of Tree
int TreeHeight(Tree t) {
   if (t == NULL) return 0;

   int leftHeight = TreeHeight(left(t));
   int rightHeight = TreeHeight(right(t));

   return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// count #nodes in Tree
int TreeNumNodes(Tree t) {
   if (t == NULL)
      return 0;
   else
      return 1 + TreeNumNodes(left(t)) + TreeNumNodes(right(t));
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
   if (t == NULL)
      return false;
   else if (it < data(t))
      return TreeSearch(left(t), it);
   else if (it > data(t))
      return TreeSearch(right(t), it);
   else                                 // it == data(t)
      return true;
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it) {
   if (t == NULL) {
      t = newNode(it);
   } else if (it < data(t)) {
      left(t) = TreeInsert(left(t),it);
   } else if (it > data(t)) {
      right(t) = TreeInsert(right(t),it);
   }
   return t;
}

Tree joinTrees(Tree t1, Tree t2) {
   if (t1 == NULL)
      return t1;
   else if (t2 == NULL)
      return t2;
   else {
      Tree curr = t2;
      Tree parent = NULL;
      while (left(curr) != NULL) {    // find min element in t2
         parent = curr;
         curr = left(curr);
      }
      if (parent != NULL) {
         left(parent) = right(curr);  // unlink min element from parent
         right(curr) = t2;
      }
      left(curr) = t1;
      return curr;                    // min element is new root
   }
}

// delete an item from a Tree
Tree TreeDelete(Tree t, Item it) {
   if (t != NULL) {
      if (it < data(t))
         left(t) = TreeDelete(left(t), it);
      else if (it > data(t))
         right(t) = TreeDelete(right(t), it);
      else {
         Tree new;
         if (left(t) == NULL && right(t) == NULL) 
            new = NULL;
         else if (left(t) == NULL)    // if only right subtree, make it the new root
            new = right(t);
         else if (right(t) == NULL)   // if only left subtree, make it the new root
            new = left(t);
         else                         // left(t) != NULL and right(t) != NULL
            new = joinTrees(left(t), right(t));
         free(t);
         t = new;
      }
   }
   return t;
}

Tree rotateRight(Tree n1) {
   if (n1 == NULL || left(n1) == NULL)
      return n1;
   Tree n2 = left(n1);
   left(n1) = right(n2);
   right(n2) = n1;
   return n2;
}

Tree rotateLeft(Tree n2) {
   if (n2 == NULL || right(n2) == NULL)
      return n2;
   Tree n1 = right(n2);
   right(n2) = left(n1);
   left(n1) = n2;
   return n1;
}

Tree insertAtRoot(Tree t, Item it) {

   if (t == NULL) {
      t = newNode(it);
      return t;
   }
   if (it != data(t) && TreeSearch(t,it) == false){
      Tree newRoot = newNode(it);
      if (it < data(t)) right(newRoot) = t;
      else left(newRoot) = t;
      return newRoot;
   } 
   return t;
}

Tree partition(Tree t, int i) {
   if (t != NULL) {
      assert(0 <= i && i < TreeNumNodes(t));
      int m = TreeNumNodes(left(t));
      if (i < m) {
         left(t) = partition(left(t), i);
         t = rotateRight(t);
      } else if (i > m) {
         right(t) = partition(right(t), i-m-1);
         t = rotateLeft(t);
      }
   }
   return t;
}

Tree rebalance(Tree t) {
   int n = TreeNumNodes(t);
   if (n >= 3) {
      t = partition(t, n/2);           // put node with median key at root
      left(t) = rebalance(left(t));    // then rebalance each subtree
      right(t) = rebalance(right(t));
   }
   return t;
}

// Count number of even nodes
int count (Tree t) {
   if (t == NULL) return 0;
   return count(left(t)) + count(right(t)) + 1;
}

// Count number of even nodes
int countEven (Tree t) {
   if (t == NULL) return 0;
   int addVal = 0;
   if (data(t) % 2 == 0) addVal = 1;
   return countEven(left(t)) + countEven(right(t)) + addVal;
}

// Count number of internal nodes
int countInternal (Tree t) {
   if (t == NULL) return 0;

   int addVal = 0;
   if (left(t) != NULL || right(t) != NULL) {
      addVal = 1;
   }
   return countInternal(left(t)) + countInternal(right(t)) + addVal;
}

// Returns -1 if there is a node whose left and right subtree
// have a difference of geq than 5 else return 1
int myBal5 (Tree t) {
   if (t == NULL) return 1;
   
   int ans = myCount(t);

   if (ans != -1) ans = 1;
   return ans;
}

int myCount (Tree t) {
   
   if (t == NULL) return 0;

   int lansw = myCount(left(t));
   int ransw = myCount(right(t));

   if (lansw == -1 || ransw == -1) return -1;
   if (ransw-lansw >= 5 || ransw - lansw <= -5)
      return -1;
   return lansw + ransw + 1;
}

// If left and right subtree have difference of geq 
// than 5, add to number of nodes. Return the total number
// of nodes satisfying this condition
int countUneqNode (Tree t) {
   if (t == NULL) return 0;

   int lansw = count(left(t));
   int ransw = count(right(t));

   if (ransw-lansw >= 5 || ransw - lansw <= -5)
      return countUneqNode(left(t)) + countUneqNode(right(t)) + 1;
   else 
      return countUneqNode(left(t)) + countUneqNode(right(t));
}