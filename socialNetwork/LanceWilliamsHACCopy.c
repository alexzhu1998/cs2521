// Lance-Williams Algorithm for Hierarchical Agglomerative Clustering
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "LanceWilliamsHAC.h"

double weight(Graph g, Vertex i, Vertex j) {
    AdjList adjEdge = GraphOutIncident(g,i);
    AdjList search = adjEdge; 
    while (search != NULL) {
        if (search->v == j) {
            break;
        }
        search = search->next;
    }

    adjEdge = GraphInIncident(g,i);
    AdjList search2 = adjEdge;
    while (search2 != NULL) {
        if (search2->v == j){
            break;
        }
        search2 = search2->next;
    }
    if (search == NULL && search2 == NULL) {
        printf("ERROR cannot find vertex\n");
        return 0;
    } else if (search == NULL) {
        return search2->weight;
    } else if (search2 == NULL) {
        return search->weight;
    } else {
        return (search->weight > search2->weight)
         ? search->weight :search2->weight;
    }

}

void distArr(double **dist, Graph g, int n) {
    int i,j;
    double w;
    for (i = 0; i < n; i++) {
        dist[i] = calloc(n,sizeof(double));
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++){
            if (i == j) continue;
            if (GraphIsAdjacent(g,i,j) || GraphIsAdjacent(g,j,i)) {
                w = weight(g,i,j);
                dist[i][j] = 1/w;
            } else {
                dist[i][j] = 99999;
            }
            
            printf("i %d j %d %lf\n",i,j,dist[i][j]);
        }
    }
}

void freeDist (double **dist, int n) {
    for (int i = 0 ;i < n; i++) free(dist[i]);
    free(dist);
}

double minmax(double a, double b, int method){
    if (method == 1) {
        return (b < a) ? b : a;
    } else {
        return (a < b) ? b : a;
    }
}

void mergeClusters (Dendrogram *dendA, double **dist, int n, int method) {
    int i,j,x,y;
    //locate minimum
    double minDist = __DBL_MAX__;
    for (i = 0; i < n; i++) {
        // ensures j > i, which means y > x
        for (j = i; j < n; j++){
            if (i == j) continue;
            if (dist[i][j] < minDist) {
                minDist = dist[i][j];
                x = i;
                y = j;
            }
            
        }
    }

    
    Dendrogram cluster = calloc(1,sizeof(DNode));
    cluster->left = dendA[x];
    cluster->right = dendA[y];
    for (i = x; i < y; i++) {
        dendA[i] = dendA[i+1];
    }
    for (i = y; i < n; i++) {
        dendA[i-1] = dendA[i+1];
    }
    dendA[n-2] = cluster;
    printf("%d, %d\n", x,y);

}

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
    double **dist = calloc(n*n, sizeof(double**));
    distArr(dist, g, n);


    
    Dendrogram *dendA = calloc(n,sizeof(Dendrogram));

    for (int i = 0; i < n; i++) {
        dendA[i] = calloc(1,sizeof(DNode));
        dendA[i]->vertex = i;
        dendA[i]->left = dendA[i]->right = NULL;
    }

    mergeClusters(dendA,dist,n, 1);

    for (int i = 0; i < n; i++){
        freeDendrogram(dendA[i]);
    }
    free(dendA);
    freeDist(dist, n);
    return NULL;
}

/**
 * Frees all memory associated with the given Dendrogram structure.
 */
void freeDendrogram(Dendrogram d) {
    if (d == NULL) return;
    freeDendrogram(d->left);
    freeDendrogram(d->right);
    free(d);
}

