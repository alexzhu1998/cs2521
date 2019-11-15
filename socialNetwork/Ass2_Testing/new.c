// Dijkstra ADT implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Dijkstra.h"
#include "PQ.h"
#define INFIN 9999999

ShortestPaths dijkstra(Graph g, Vertex src) {

	int nV=GraphNumVertices(g);

	ShortestPaths sps = {0};

	sps.numNodes = nV;
	sps.src = src;
	sps.dist = malloc(nV*sizeof(int));
	sps.pred = malloc(nV*sizeof(PredNode));

	for(int i=0; i<nV; i++){ // initialise dist[] to all ∞, except dist[source]=0
		sps.dist[i] = INFIN; //
		sps.pred[i] = NULL;
	}
	sps.dist[src] = 0;

	PQ Vset = PQNew(); //adding everything to the set
	for(int i = 0; i < nV; i++){
		ItemPQ nitem;
		nitem.key = i;
		nitem.value = sps.dist[i];
		PQAdd(Vset, nitem);
	}

	while(!PQIsEmpty(Vset)){
		ItemPQ item = PQDequeue(Vset);
		int vertice = item.key;
		AdjList neighbour = GraphOutIncident(g, vertice);
		while(neighbour != NULL){

			if(item.value + neighbour->weight < sps.dist[neighbour->v]){
				sps.dist[neighbour->v] = item.value + neighbour->weight;

				ItemPQ newItem = (ItemPQ) {.key = neighbour->v , .value = sps.dist[neighbour->v]};
				PQUpdate(Vset, newItem);
				//if it is empty at that point
			}
			neighbour=neighbour->next;
		}

	}

	for(int i = 0; i < nV; i++){
		if(i != src){
			AdjList neigh = GraphInIncident(g, i);
			while(neigh!=NULL){
				if(sps.dist[neigh->v] + neigh->weight == sps.dist[i]){
					PredNode *nn = malloc(sizeof(PredNode));
					nn->next = NULL;
					nn->v = neigh->v;

					if(sps.pred[i] == NULL){
						sps.pred[i] = nn;
					}
					else {
						PredNode * nextvert = sps.pred[i];
						nn->next = nextvert;
						sps.pred[i] = nn;
					}
				}
				neigh = neigh->next;
			}
		}
		if(sps.dist[i]==INFIN){
			sps.dist[i]=0;
		}
	}

	return sps;
}

void showShortestPaths(ShortestPaths sps) {

}

void freeShortestPaths(ShortestPaths sps) {

}
