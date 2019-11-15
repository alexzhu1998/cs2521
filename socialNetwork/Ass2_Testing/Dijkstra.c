// Dijkstra ADT implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dijkstra.h"
#include "PQ.h"

#define HIGH_WEIGHT 99999

Vertex minArr(int dist[], Vertex vSet[]) {
	int min = HIGH_WEIGHT;
	Vertex minV;

	for (int i = 0; i < (sizeof(dist)/ sizeof(int)); i++) {
		if (min >= dist[i] && vSet[i] == -1){
			min = dist[i];
			minV = i;
		}
	}
	return minV;
}

ShortestPaths dijkstra(Graph g, Vertex src) {
	// initialise graph vertices
	int nV = GraphNumVertices(g);
	// initialise distance and predecessor array
	int dist[nV];
	int pred[nV];
	Vertex vSet[nV];
	// assign initial values for both loops
	for (int i = 0; i < nV; i++) {
		dist[i] = HIGH_WEIGHT;
		pred[i] = -1;
		vSet[i] = -1;
	}

	dist[src] = 0;

	for (int i = 0; i < nV - 1; i++) {
		Vertex v = minArr(dist,vSet);
		// int u
	}

	ShortestPaths sps = {0};

	return sps;
}

void showShortestPaths(ShortestPaths sps) {
	// for (int i = 0; i < )
	// printf("")
}

void freeShortestPaths(ShortestPaths sps) {

}
