// Dijkstra ADT implementation
// COMP2521 Assignment 2

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "Dijkstra.h"
#include "PQ.h"

//////////////////////
/* HELPER FUNCTIONS */
//////////////////////

// Update the Shortest path (called inside Update)
void updateShortestPaths (ShortestPaths sps, AdjList adjEdge,ItemPQ s, int c);

// Update the PQ and Shortest Path
void update (ShortestPaths sps, PQ pq, ItemPQ s, AdjList adjEdge);

////////////////////
/* MAIN FUNCTIONS */
////////////////////

// Main Dijkstra Algorithm
ShortestPaths dijkstra(Graph g, Vertex src) {
	if (g == NULL) {
		printf("NULL graph, abort");
		abort();
	}

	if (src < 0) {
		printf("Invalid source node, abort");
		abort();
	}

	int nV = GraphNumVertices(g);
	ShortestPaths sps = {0};
	sps.numNodes = nV;
	sps.src = src;
	sps.dist = calloc(nV, sizeof(int));
	sps.pred = calloc(nV, sizeof(PredNode));
	
	// No Memory
	if (sps.pred == NULL || sps.dist == NULL) {
		printf("Insufficient Memory, abort");
		abort();
	}

	for (int i = 0; i < nV; i++) {
		sps.dist[i] = INT_MAX;
		sps.pred[i] = NULL;
	}

	PQ pq = PQNew();

	ItemPQ item;
	item.key = src;
	// weight from source
	item.value = 0;

	// Only add the initial item
	PQAdd(pq,item);


	sps.dist[src] = 0;

	// Initiate the PQ list
	while (!PQIsEmpty(pq)) {
		ItemPQ s = PQDequeue(pq);
		AdjList adjEdge = GraphOutIncident(g,s.key);
		for (;adjEdge != NULL;adjEdge = adjEdge->next) {
			// update distance, predecessor, PQ,
			update(sps,pq,s,adjEdge);
		}
	}

	for (int i = 0; i <nV; i++) {
		if(sps.dist[i]==INT_MAX){
			sps.dist[i]=0;
		}
	}

	PQFree(pq);
	return sps;

}

void showShortestPaths(ShortestPaths sps) {
	int i = 0;
	printf("Node %d\n", sps.src);
	printf("  Distance\n");
	for (i = 0; i < sps.numNodes; i++) {
		if (i == sps.src)
			printf("    %d : X\n", i);
		else
			printf("    %d : %d\n", i, sps.dist[i]);
	}
	
	printf("  Preds\n");
	for (i = 0; i < sps.numNodes; i++) {
		int numPreds = 0;
		int preds[sps.numNodes];
		printf("    %d : ",i);
		PredNode *curr = sps.pred[i];
		while (curr != NULL && numPreds < sps.numNodes) {
			preds[numPreds++] = curr->v;
			curr = curr->next;
		}
		
		// Insertion sort
		for (int j = 1; j < numPreds; j++) {
			int temp = preds[j];
			int k = j;
			while (k > 0 && preds[k - 1] > temp) {
				preds[k] = preds[k - 1];
				k--;
			}
			preds[k] = temp;
		}
		
		for (int j = 0; j < numPreds; j++) {
			printf("[%d]->", preds[j]);
		}
		printf("NULL\n");
	}
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

//////////////////////
/* HELPER FUNCTIONS */
//////////////////////

void updateShortestPaths (ShortestPaths sps, AdjList adjEdge,ItemPQ s, int c) {
	if (c == 1) {
		// free entire predecessor linked list 
		// if there is a shortest path that is strictly 
		// smaller previous shortest path
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
		// if there is a shortest path that is equal 
		// to previous shortest path,
		// add to the predecessor array 
		PredNode *head = sps.pred[adjEdge->v];
		// loop through linked list to find last element
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