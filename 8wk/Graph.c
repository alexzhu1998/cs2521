// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep {
	int nV;		 // #vertices
	int nE;		 // #edges
	int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV (Graph g, Vertex v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
static Edge mkEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	Edge new = {v, w}; // struct assignment
	return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge (Graph g, Vertex v, Vertex w, int wt)
{
	assert (g != NULL && validV (g, v) && validV (g, w));

	if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
		// an edge already exists; do nothing.
		return;

	g->edges[v][w] = wt;
	g->edges[w][v] = wt;
	g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge (Graph g, Vertex v, Vertex w)
{
	assert (g != NULL && validV (g, v) && validV (g, w));
	if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
		// an edge doesn't exist; do nothing.
		return;

	g->edges[v][w] = 0;
	g->edges[w][v] = 0;
	g->nE--;
}

// create an empty graph
Graph newGraph (int nV)
{
	assert (nV > 0);

	GraphRep *new = malloc (sizeof *new);
	assert (new != NULL);
	*new = (GraphRep){ .nV = nV, .nE = 0 };

	new->edges = calloc ((size_t) nV, sizeof (int *));
	assert (new->edges != NULL);
	for (int v = 0; v < nV; v++) {
		new->edges[v] = calloc ((size_t) nV, sizeof (int));
		assert (new->edges[v] != 0);
	}

	return new;
}

// free memory associated with graph
void dropGraph (Graph g)
{
	assert (g != NULL);
	for (int v = 0; v < g->nV; v++)
		free (g->edges[v]);
	free (g->edges);
	free (g);
}

// display graph, using names for vertices
void showGraph (Graph g, char **names)
{
	assert (g != NULL);
	printf ("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		printf ("%d %s\n", v, names[v]);
		for (w = 0; w < g->nV; w++) {
			if (g->edges[v][w]) {
				printf ("\t%s (%d)\n", names[w], g->edges[v][w]);
			}
		}
		printf ("\n");
	}
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath (Graph g, Vertex src, Vertex dest, int max, int *path)
{
	assert (g != NULL);
	Queue Q = newQueue();
	// change path
	// return length of the path
	// if sum of weights is larger than what the plane can hold

	// printf("path %d\n",*path);
	// printf("src %d\n",src);
	// initialise previous array
	int previous[g->nV];
	for (int i = 0; i < g->nV; i++) previous[i] = -1;
	// initialise found
	int found = 0;
	previous[src] = src;

	QueueJoin(Q,src);
	while (QueueIsEmpty(Q) == 0 && found == 0) {
		// showQueue(Q);
		Vertex v = QueueLeave(Q);
		if (v == dest) {
			// printf("found dest %d\n", v);
			found = 1;
		} else {
			for (Vertex w = 0; w < g->nV; w++) {
				if (previous[w] == -1 && g->edges[v][w] != 0 && g->edges[v][w] < max) {
					previous[w] = v;
					QueueJoin(Q,w);
				}
			}
		}
	}

	dropQueue(Q);
	int dist = 0;
	//copying from previous to path
	if (found == 1) {
		// printf("Start Check\n");
		for (int i = dest; i != src; i = previous[i]) {
				// printf("%d\n", i);
				dist++;
		}
		dist++;
		// printf("dist = %d\n", dist);
		int i = dist - 1;
		for (int j = dest; j != src; j = previous[j]) {
			// printf("previous %d\n", previous[j]);
			path[i] = j;
			i--;
		}
		path[0] = src;
	}


	return dist; // never find a path ... you need to fix this
}
