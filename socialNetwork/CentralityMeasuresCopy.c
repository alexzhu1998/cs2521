// Centrality Measures ADT implementation
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"

static double numSP(ShortestPaths paths, Vertex start ,Vertex end) {
	ItemPQ item;
	item.key = end;
	item.value = 0;
	PQ pq = PQNew();
	PQAdd(pq,item);

	double count = 0;
	while (!PQIsEmpty(pq)) {
		ItemPQ s = PQDequeue(pq);
		PredNode *head = paths.pred[s.key];
		PredNode *search;
		int i = 0;
		
		// bfs to find all possible paths
		for (search = head; search != NULL;search = search->next){
			if (search->v == start) {
				count ++;
				continue;
			}
		
			ItemPQ new;
			new.key = search->v;
			new.value = i;
			PQAdd(pq,new);
			i++;
			
		}
		
	}
	PQFree(pq);
	return count;
}

static double checkVinSP (ShortestPaths paths, Vertex start ,Vertex target, Vertex end) {
	ItemPQ item;
	item.key = end;
	item.value = 0;
	PQ pq = PQNew();
	PQAdd(pq,item);
	// dfs approach, use PQ as a stack
	double count = 0;
	double found = 0;
	int i = 99999;
	while (!PQIsEmpty(pq)) {
		ItemPQ s = PQDequeue(pq);
		PredNode *head = paths.pred[s.key];
		PredNode *search = head;

		for (search = head; search != NULL; search = search->next){
			if (start == search->v) {
				if (found == 1) count++;
				// reset found
				found = 0;
				continue;
			} 
			if (target == search->v) found = 1;
			ItemPQ new;
			new.key = search->v;
			new.value = i;
			PQAdd(pq,new);
			i--;
		}
	}


	PQFree(pq);
	return count;

}

NodeValues closenessCentrality(Graph g) {
	// initialising variables
	NodeValues nvs = {0};
	nvs.numNodes = GraphNumVertices(g);
	nvs.values = calloc(nvs.numNodes, sizeof(double));
	// use Dijkstra to find shortest path from every node to every node.
	for (int i = 0; i < nvs.numNodes; i++) {
		ShortestPaths paths = dijkstra(g, i);
		// sum of reachable nodes
		double sum = 0;
		double isolated = 0;
		for (int j = 0; j < nvs.numNodes; j++) {
			// if dikstra shows 0 on a different node to source, it is isolated
			if (paths.dist[j] == 0 && j != i) isolated++;
			sum += paths.dist[j];
		}
		if (sum != 0){
			if (isolated != 0) {
				double n = nvs.numNodes - isolated;
				double N = nvs.numNodes;
				nvs.values[i] = ((n-1)*(n-1))/((N-1)*sum);
			} else {
				double n = nvs.numNodes;
				nvs.values[i] = (n-1)/sum;
			}
		} else {
			// assigning values of 0 if i is isolated 
			nvs.values[i] = 0;
		}
		freeShortestPaths(paths);
	}
	return nvs;
}

NodeValues betweennessCentrality(Graph g) {
	// initialising variables
	NodeValues nvs = {0};
	nvs.numNodes = GraphNumVertices(g);
	nvs.values = calloc(nvs.numNodes, sizeof(double));
	// use dijkstra to give the heads of the shortest path for destination j
	// if the predecessor nodes contain an element other than i or src
	// then its important
	int nV = nvs.numNodes;
	for (int s = 0; s < nV; s++) {
		// double visitable = 0;
		ShortestPaths paths = dijkstra(g, s);
		for (int v = 0; v < nV; v++) {
			if (s == v) continue;
			for (int t = 0; t < nV; t++){
				if (s == t||v == t) continue;
				double numSPaths = 0;
				double numVinSPaths = 0;

				numSPaths = numSP(paths,s,t);
				numVinSPaths = checkVinSP(paths, s,v,t);
				// printf("s %d v %d t %d SP %lf vSP %lf\n", s,v,t,numSPaths,numVinSPaths);
				if (numSPaths != 0) nvs.values[v] += numVinSPaths/numSPaths;
				
			}
		}
		// showShortestPaths(paths);
		freeShortestPaths(paths);
	}

	return nvs;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	NodeValues nvs = {0};
	return nvs;
}

void showNodeValues(NodeValues nvs) {
	for (int i = 0; i< nvs.numNodes; i++) {
		printf("%d: %lf\n",i,nvs.values[i]);
	}
}

void freeNodeValues(NodeValues nvs) {
	free(nvs.values);
}
