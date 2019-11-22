// Lance-Williams Algorithm for Hierarchical Agglomerative Clustering
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "LanceWilliamsHAC.h"

//////////////////////
/* HELPER FUNCTIONS */
//////////////////////

// Calculate the first set of weights based on condition
double weight(Graph g, Vertex i, Vertex j);

// Create the first distance array
void distArr(double **dist, Graph g, int n);

// Free distance array of a given size
void freeDist (double **dist, int n);

// Returns Minimum or Maximum
double minmax(double a, double b, int method);

// Function that merges one pair of clusters and distance arrays
Dendrogram* mergeClusters (Dendrogram *dendA, double **dist, int n, int method);

////////////////////
/* MAIN FUNCTIONS */
////////////////////

/**
 * Generates  a Dendrogram using the Lance-Williams algorithm (discussed
 * in the spec) for the given graph  g  and  the  specified  method  for
 * agglomerative  clustering. The method can be either SINGLE_LINKAGE or
 * COMPLETE_LINKAGE (you only need to implement these two methods).
 * 
 * The function returns a 'Dendrogram' structure.
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {
    int n = GraphNumVertices(g);
    double **dist = calloc(n*n, sizeof(double*));
    distArr(dist, g, n);

    // Initiate an array of pointers
    Dendrogram *dendA = calloc(n,sizeof(Dendrogram));

    // Initiate node for each pointer
    for (int i = 0; i < n; i++) {
        dendA[i] = calloc(1,sizeof(DNode));
        dendA[i]->vertex = i;
        dendA[i]->left = dendA[i]->right = NULL;
    }

    // A recursive function to merge all clusters
    for (int i = 0; i < n-1; i++) {
        dendA = mergeClusters(dendA,dist,n, method);
    }   
    
    
    // We can assume that there is always only one cluster
    // remaining
    Dendrogram sol = dendA[0];
    for (int i = 1; i < n; i++){
        freeDendrogram(dendA[i]);
    }
    free(dendA);
    freeDist(dist,n);
    return sol;
}

/**
 * Frees all memory associated with the given Dendrogram structure.
 */
void freeDendrogram(Dendrogram d) {
    // Recursive function returns null if dendrogram
    // hits leaves or contains nothing
    if (d == NULL) return;
    freeDendrogram(d->left);
    freeDendrogram(d->right);
    free(d);
}

double weight(Graph g, Vertex i, Vertex j) {
    // Search through all outgoing edge and find 
    // the edge i to j
    AdjList adjEdge = GraphOutIncident(g,i);
    AdjList search = adjEdge; 
    while (search != NULL) {
        if (search->v == j) {
            break;
        }
        search = search->next;
    }
    //  Search through all incoming edge and find
    //  the edge j to i
    adjEdge = GraphInIncident(g,i);
    AdjList search2 = adjEdge;
    while (search2 != NULL) {
        if (search2->v == j){
            break;
        }
        search2 = search2->next;
    }
    // Compares incoming and outgoing weights
    if (search == NULL && search2 == NULL) {
        printf("ERROR cannot find vertex\n");
        return 0;
    } else if (search == NULL) {
        return search2->weight;
    } else if (search2 == NULL) {
        return search->weight;
    } else {
        // Returns minimum of the two if both exists 
        return (search->weight > search2->weight)
         ? search->weight :search2->weight;
    }

}

//////////////////////
/* HELPER FUNCTIONS */
//////////////////////


void distArr(double **dist, Graph g, int n) {
    int i,j;
    double w;
    for (i = 0; i < n; i++) {
        dist[i] = calloc(n,sizeof(double));
    }
    // If two nodes are adjacent, calculate distance
    // otherwise return max_double - 1, to indicate cluster
    // can still be formed
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++){
            if (i == j) continue;
            if (GraphIsAdjacent(g,i,j) || GraphIsAdjacent(g,j,i)) {
                w = weight(g,i,j);
                dist[i][j] = 1/w;
            } else {
                // DBL_MAX-1 is used to distinguish for the edge
                // case where no nodes are connected to each other
                dist[i][j] = __DBL_MAX__-1;
            }
            
        }
    }
}



// Free individual 2D array through two steps
void freeDist (double **dist, int n) {
    if (dist == NULL) return;
    for (int i = 0 ;i < n; i++) free(dist[i]);
    free(dist);
}

double minmax(double a, double b, int method){
    // method == 1 is minimum
    if (method == 1) {
        return (b < a) ? b : a;
    } else {
        return (a < b) ? b : a;
    }
}

// A function that merges clusters and tables
Dendrogram* mergeClusters (Dendrogram *dendA, double **dist, int n, int method) 
{
    // Checking if inputs are valid
    if (method != SINGLE_LINKAGE && method != COMPLETE_LINKAGE) {
        printf("No Valid Method, Program Terminated\n");
        abort();
    }

    // Create inaccessible value
    double inacc = -1;

    int i,j,x,y;
    double minMaxDist;
    //locates minimum or maximum
    if (method == SINGLE_LINKAGE) {
        minMaxDist = __DBL_MAX__;
    } else {
        minMaxDist = 0;
    }

    for (i = 0; i < n; i++) {
        // ensures j > i, which ensures y > x
        for (j = i; j < n; j++){
            if (i == j) continue;
            // method can only either be 1 or 2
            if (method == SINGLE_LINKAGE) {
                if (dist[i][j] < minMaxDist && dist[i][j] != inacc) {
                    minMaxDist = dist[i][j];
                    x = i;
                    y = j;
                }
            } else {
                if (dist[i][j] > minMaxDist && dist[i][j] != inacc) {
                    minMaxDist = dist[i][j];
                    x = i;
                    y = j;
                }
            }
        }
    }
    
    // Change the distance array by applying appropriate
    // linkage method. First, y will be resetted to DBL_MAX
    // to indicate node is inaccessible. As opposed to 
    // initially initiated DBL_MAX - 1 
    dist[x][y] = inacc;
    dist[y][x] = inacc;
    for (i = 0; i < n; i++) {
        if (i == x || i == y) continue;
        dist[i][x] = minmax(dist[i][x],dist[i][y],method);
        // render y unaccessible
        dist[i][y] = inacc;
        // symmetry in the array
        dist[x][i] = dist[i][x];
        dist[y][i] = dist[i][y];
    }
    
    // Create cluster for dendA
    Dendrogram cluster = calloc(1,sizeof(DNode));
    cluster->vertex = -1;
    cluster->left = dendA[x];
    cluster->right = dendA[y];

    // Lower value (x) will point to cluster
    dendA[x] = cluster;
    dendA[y] = NULL;

    return dendA;
}