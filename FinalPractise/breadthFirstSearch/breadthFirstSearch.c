
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"


void breadthFirstSearch(Graph g, int src) {
	// TODO
	int nV = GraphNumVertices(g);
	// initiate src node 
	int distArr[nV];
	for (int i = 0; i < nV; i++) {
		if (i != src) distArr[i] = __INT_MAX__;	
	}

	distArr[src] = 0;
	
	

	// while loop, push into queue
}

