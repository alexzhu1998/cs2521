// Centrality Measures ADT implementation
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"

//////////////////////
/* HELPER FUNCTIONS */
//////////////////////


// Count number of shortest paths 
static double numSP(
	ShortestPaths paths, PredNode * node ,Vertex start ,Vertex end
);

// Count number of shortest paths that passes through a particular node
static double checkVinSP (
	ShortestPaths paths, PredNode *node, Vertex start ,Vertex target, Vertex end
);

////////////////////
/* MAIN FUNCTIONS */
////////////////////


NodeValues closenessCentrality(Graph g) {
	// initialising variables
	NodeValues nvs = {0};
	nvs.numNodes = GraphNumVertices(g);
	nvs.values = calloc(nvs.numNodes, sizeof(double));
	
	if (nvs.values == NULL) {
		printf("Insufficient memory, abort\n");
		abort();
	}

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
		// initiate shortest path
		ShortestPaths paths = dijkstra(g, s);
		for (int v = 0; v < nV; v++) {
			if (s == v) continue;
			for (int t = 0; t < nV; t++){
				if (s == t||v == t) continue;
				double numSPaths = 0;
				double numVinSPaths = 0;
				// Calculate number of shortest paths and passing through
				// particular node using recursion
				numSPaths = numSP(paths,paths.pred[t], s,t);
				// Calculate number of shortest paths using recursion
				numVinSPaths = checkVinSP(paths, paths.pred[t],s,v,t);
				if (numSPaths != 0) nvs.values[v] += numVinSPaths/numSPaths;
				
			}
		}
		// showShortestPaths(paths);
		freeShortestPaths(paths);
	}

	return nvs;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	// using betweenessCentrality and dividing it by the factor
	NodeValues nvs = {0};
	nvs = betweennessCentrality(g);
	nvs.numNodes = GraphNumVertices(g);
	double denom = (nvs.numNodes-1)*(nvs.numNodes-2);
	for (int i = 0; i < nvs.numNodes; i++)
		nvs.values[i] = nvs.values[i]/denom;
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

//////////////////////
/* HELPER FUNCTIONS */
//////////////////////

static double numSP(
	ShortestPaths paths, PredNode * node ,Vertex start ,Vertex end
) {
	// if NULL was visited
	if (node == NULL) {
		return 0;
	// if start was visited
	} else if (node->v == start) {
		return 1 + numSP(paths,node->next,start,end);
	// if no special nodes were visited
 	} else {
		return numSP(paths,paths.pred[node->v],start,end) 
		+ numSP(paths,node->next,start,end);
	}
}

static double checkVinSP (
	ShortestPaths paths, PredNode *node, Vertex start ,Vertex target, Vertex end
) {
	// if null returns nothing
	if (node == NULL) {
		return 0;
	// if it reaches to the source node
	} else if (node->v == start) {
		// if there are more nodes in the predecessor LL to be checked
		return checkVinSP(paths,node->next,start,target,end);
	// if target was reached 
	} else if (node->v == target) {
		return numSP(paths,paths.pred[node->v],start,end) 
		+ checkVinSP(paths,node->next,start,target,end);
	// if no special nodes were visited
	} else {
		return checkVinSP(paths,paths.pred[node->v],start,target,end) 
		+ checkVinSP(paths,node->next,start,target,end);
	}

}