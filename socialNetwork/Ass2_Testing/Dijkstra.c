// Dijkstra ADT implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Dijkstra.h"
#include "PQ.h"

void updateShortestPaths (ShortestPaths sps, AdjList adjEdge,ItemPQ s, int c) {
	if (c == 1) {
		if (sps.pred[adjEdge->v] != NULL) {
			PredNode *head = sps.pred[adjEdge->v];
			PredNode *ptr = head;
			while (ptr != NULL) {
				PredNode *prevptr = ptr;
				ptr = ptr->next;
				free(prevptr);
			}
		}
		PredNode *head = calloc(sps.numNodes,sizeof(PredNode));
		head->v = s.key;
		head->next = NULL;
		sps.pred[adjEdge->v] = head;
	} else if (c == 0) {
		PredNode *head = sps.pred[adjEdge->v];
		// loop through linked list find last element
		PredNode *ptr = head;
		while (ptr != NULL) {
			if (ptr->next == NULL) {
				PredNode *new = calloc(sps.numNodes, sizeof(PredNode));
				new->v = s.key;
				new->next = NULL;
				ptr->next = new;
				break;
			}
			ptr = ptr->next;
		}
		// sps.pred[adjEdge->v] = s.key;
	}
}

void update (ShortestPaths sps, PQ pq, ItemPQ s, AdjList adjEdge) {
	// if new distance is less than existing
	//relaxation condition
	if (s.value + adjEdge->weight <= sps.dist[adjEdge->v]) {

		// adjEdge->v
		ItemPQ node;
		node.key = adjEdge->v;
		node.value = s.value + adjEdge->weight;
		// Update priority queue
		PQAdd(pq,node);

		// update shortest path
		if (s.value + adjEdge->weight < sps.dist[adjEdge->v]) {
			updateShortestPaths(sps,adjEdge,s ,1);
		} else if (s.value + adjEdge->weight == sps.dist[adjEdge->v]) {
			updateShortestPaths(sps,adjEdge,s ,0);
		}
		sps.dist[adjEdge->v] = s.value + adjEdge->weight;
	}

}


ShortestPaths dijkstra(Graph g, Vertex src) {
	int nV = GraphNumVertices(g);
	// ShortestPaths *sps = calloc(nV,sizeof(ShortestPaths));
	ShortestPaths sps = {0};
	sps.numNodes = nV;
	sps.src = src;
	sps.dist = calloc(nV, sizeof(int));
	sps.pred = calloc(nV, sizeof(PredNode));

	for (int i = 0; i < nV; i++) {
		sps.dist[i] = INT_MAX;
		sps.pred[i] = NULL;
	}

	PQ pq = PQNew();

	ItemPQ item;
	item.key = src;
	// weight from source
	item.value = 0;


	PQAdd(pq,item);


	sps.dist[src] = 0;

	while (!PQIsEmpty(pq)) {
		ItemPQ s = PQDequeue(pq);
		AdjList adjEdge = GraphOutIncident(g,s.key);
		for (;adjEdge != NULL;adjEdge = adjEdge->next) {
			// update distance, predecessor, PQ,
			update(sps,pq,s,adjEdge);
		}
	}

	for (int i =0; i <nV; i++) {
		if(sps.dist[i]==INT_MAX){
			sps.dist[i]=0;
		}
	}

	PQFree(pq);
	return sps;

}

void showShortestPaths(ShortestPaths sps) {

}

void freeShortestPaths(ShortestPaths sps) {
	free(sps.dist);
	for (int i = 0; i < sps.numNodes; i++) {
		PredNode *curr = sps.pred[i];
		while (curr != NULL) {
			PredNode *prev = curr;
			curr = curr->next;
			free(prev);
		}
	}
	free(sps.pred);
}
