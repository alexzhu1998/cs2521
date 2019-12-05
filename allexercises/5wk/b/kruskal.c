#include <stdlib.h>
#include <stdbool.h>
#include "WGraph.h"

#define MAX_NODES 1000

bool visited[MAX_NODES];

bool dfsCycleCheck(Graph g, int nV, Vertex v, Vertex u) {
   visited[v] = true;
   Vertex w;
   for (w = 0; w < nV; w++) {
      if (adjacent(g, v, w)) {
         if (!visited[w])
            return dfsCycleCheck(g, nV, w, v);
         else if (w != u)
            return true;
      }
   }
   return false;
}

Graph kruskal(Graph g, Edge sortedEdges[], int nV, int nE) {
   Graph mst = newGraph(nV);
   
   int n = 0;
   int i;
   for (i = 0; i < nE && n < nV-1; i++) {
      Edge e = sortedEdges[i];
      insertEdge(mst, e);
      n++;
      Vertex v;
      for (v = 0; v < nV; v++)
	 visited[v] = false;
      if (dfsCycleCheck(mst, nV, e.v, e.v)) {    // cycle through node e.v?
	 removeEdge(mst, e);
	 n--;
      }
   }
   return mst;
}

int main(void) {
   int nV = 5;
   Graph g = newGraph(nV);

   Edge edges[8];
   edges[0].v = 2; edges[0].w = 3; edges[0].weight = 1;
   edges[1].v = 0; edges[1].w = 2; edges[1].weight = 2;
   edges[2].v = 0; edges[2].w = 1; edges[2].weight = 3;
   edges[3].v = 1; edges[3].w = 2; edges[3].weight = 4;
   edges[4].v = 2; edges[4].w = 4; edges[4].weight = 5;
   edges[5].v = 1; edges[5].w = 4; edges[5].weight = 6;
   edges[6].v = 3; edges[6].w = 4; edges[6].weight = 7;
   edges[7].v = 0; edges[7].w = 3; edges[7].weight = 8;

   int i, nE = 8;
   for (i = 0; i < nE; i++) {
      insertEdge(g, edges[i]);
   }
   showGraph(g);
   
   Graph mst = kruskal(g, edges, nV, nE);
   showGraph(mst);
   freeGraph(mst);
   freeGraph(g);

   return 0;
}
