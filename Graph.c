/*** Graph.c ***/
/*** Aaron Zeile ***/
/*** ID: azeile ***/
/*** pa2 ***/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "Graph.h"
#include "List.h"

// STRUCTS -------------------------------------------------------------------------

// Graph object struct
typedef struct GraphObj {
	// ints
	int order;
	int size;
	int label;
	// arrays
	List *neighbors;
	char *color;
	int *parent;
	int *distance;
} GraphObj;

// CONSTRUCTOR-DESTRUCTORS -----------------------------------------------------------
// creates a new graph
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	assert(G != NULL);

	G->order = n;
	G->size = NIL;
	G->label = NIL;	

	G->neighbors = calloc(n+1, sizeof(List));	
	G->color = calloc(n+1, sizeof(int));
	G->parent = calloc(n+1, sizeof(int));
	G->distance = calloc(n+1, sizeof(int));

	// fill in default states
	for (int i = 1; i < n+1; i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
		G->neighbors[i] = newList();
	}

	return G;
}

// frees the memory associated with graph
void freeGraph(Graph* pG) {
	if (pG != NULL && *pG != NULL) {
		// free all lists in neighbors array
		for (int i = 1; i < getOrder(*pG)+1; i++) {
			freeList(&(*pG)->neighbors[i]);
		}

		// free all arrays
		free((*pG)->neighbors);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
		(*pG)->neighbors = NULL;
		(*pG)->color = NULL;
		(*pG)->parent = NULL;
		(*pG)->distance = NULL;

		// free graph
		free(*pG);
		*pG = NULL;
	}
}

// ACCESS FUNCTIONS -------------------------------------------------------------------
// returns the order of the graph
int getOrder(Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Error. Trying getOrder of NULL list.\n");
		exit(EXIT_FAILURE);
	}
	return G->order;
}
// returns size of the graph
int getSize(Graph G) {
	if (G == NULL) {
		fprintf(stderr, "Error. Trying getSize of NULL list.\n");
		exit(EXIT_FAILURE);
	}
	return G->size;
}
// returns the most recent source of the graph, as used in BFS
int getSource(Graph G) {
	return G->label;
}
// returns the parent of u
int getParent(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. Trying getParent with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	return G->parent[u];
}
// returns the distance from most recent souce to u
int getDist(Graph G, int u) {
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. Trying getDist with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	return G->distance[u];
}
// appends shortest path from source to u into L
void getPath(List L, Graph G, int u) {
	if (getSource(G) == NIL) {
		printf("No shortest path because source is NIL.\n");
		return;
	}
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. Trying getPath with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}

	// if u is source	
	if (u == getSource(G)) {
		append(L, u);
		return;
	}
	
	// if source is unreachable
	if (G->parent[u] == NIL) {
		if (length(L) > 0) {
			clear(L);
		}
		append(L, NIL);
		return;
	}

	// recursion
	getPath(L, G, G->parent[u]);
	append(L, u);
}
	
// MANIPULATION PROCEDURES --------------------------------------------------------------
void makeNull(Graph G) {
	// go through each vertex and delete edges
	for (int i = 1; i < getOrder(G)+1; i++) {
		List L = G->neighbors[i];
		if (length(L) > 0) {
			clear(L);
			G->color[i] = 'w';
			G->parent[i] = NIL;
			G->distance[i] = INF;
		}
	}
	// reset graph info
	G->size = NIL;
}

// use addArc twice and dec size once
void addEdge(Graph G, int u, int v) {	
// preconditions ------------------------------------
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. trying addarc with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1 || v > getOrder(G)) {
		fprintf(stderr, "Error. trying addarc with v out of bounds.\n");
		exit(EXIT_FAILURE);
	}
// adding to adjacency lists -----------------------
	addArc(G, u, v);
	addArc(G, v, u);
	G->size--;
}

// adds v to u's adjacency list
void addArc(Graph G, int u, int v) {
// preconditions ------------------------------------
	if (u < 1 || u > getOrder(G)) {
		fprintf(stderr, "Error. trying addarc with u out of bounds.\n");
		exit(EXIT_FAILURE);
	}
	if (v < 1 || v > getOrder(G)) {
		fprintf(stderr, "Error. trying addarc with v out of bounds.\n");
		exit(EXIT_FAILURE);
	}	
// adding v to u's adj list -------------------------
	List L = G->neighbors[u];
	// if adj list is empty, simply append
	if (!(length(L) > 0)) {
		append(L, v);
		G->size++;
		return;
	}
	// start at front of list
	moveFront(L);
	// traverse list to correct insertion point
	while (index(L) != -1 && v > get(L)) {
		moveNext(L);
	}
	// if we went past the back
	if (index(L) == -1) {
		append(L, v);
	}
	// if still in list
	else {
		insertBefore(L, v);
	}
	G->size++;
}

// performs BFS algorithm on G with source s
void BFS(Graph G, int s) {
// precondition ------------------------------------
	if (s < 1 || s > getOrder(G)) {
		fprintf(stderr, "Error. Trying BFS with s out of bounds.\n");
		exit(EXIT_FAILURE);
	}
// BFS ---------------------------------------------
	// set default states
	for (int i = 1; i < getOrder(G)+1; i++) {
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}

	// set source of G
	G->label = s;
	G->distance[s] = 0;

	// create queue and append source
	List Q = newList();
	append(Q, s);

	// while queue is not empty
	while (length(Q) > 0) {
		// get first in queue
		int x = front(Q);

		// start at the first neighbor of x
		List L = G->neighbors[x];
		moveFront(L);
		// iterate through the neighbor list
		while (index(L) != -1) {
			// get current neighbor
			int neighbor = get(L);
			// if current neighbor has not been visited,
			// update its information
			if (G->color[neighbor] == 'w') {
				G->color[neighbor] = 'g';
				G->distance[neighbor] = G->distance[x] + 1;
				G->parent[neighbor] = x;
				append(Q, neighbor); // add this neighbor to queue
			}
			// move to the next neighbor
			moveNext(L);
		}
		// after all neighbors have been visited,
		// black out x and delete it from queue
		G->color[x] = 'b';
		deleteFront(Q);
	}
	freeList(&Q);
}

// OTHERS -------------------------------------------------------------------------
void printGraph(FILE* out, Graph G) {
	// print adjacency lists
	for (int i = 1; i < getOrder(G)+1; i++) {
		List L = G->neighbors[i];
		fprintf(out, FORMAT ": ", i);
		if (length(L) > 0) {
			printList(out, L);
		}
		else {
			fprintf(out, "\n");
		}
	}	
}
