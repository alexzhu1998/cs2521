
/* hasPath.c
   Written by Ashesh Mahidadia, October 2017
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Graph.h"



/*
    You will submit only this one file.

    Implement the function "hasPath" below. Read the exam paper for
    detailed specification and description of your task.

    - You can add helper functions in this file, if required.

    - DO NOT modify code in the file BSTree.h .
    - DO NOT add "main" function in this file.
*/


int *visited;  // array of visited


int hasPath(Graph g, Vertex src, Vertex dest) {
    visited = (int *) malloc(g->nV * sizeof(int));
    Vertex v;
    for (v = 0; v < g->nV; v++) {
        visited[v] = -1;
    }
    return checkPath(g, src, dest);
	// Implement this function,
	// also change the return value below!
}

int checkPath(Graph g, Vertex src, Vertex dest) {
    Vertex w;
    for (w = 0; w < g->nV; w++) {
        if (adjacent(g, src, w) && visited[w] == -1) {
            if (w == dest) return 1;
            visited[w] = 1;
            return checkPath(g, w, dest);
        }
    }
    return 0;
}
