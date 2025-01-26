/*** FindPath.c ***/
/*** Aaron Zeile ***/
/*** ID: azeile ***/
/*** pa2 ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {
	// if not two command line arguments
	if (argc != 3) {
		fprintf(stderr, "Error. Must have exactly 2 command line arguments.\n");
		exit(EXIT_FAILURE);
	}

	char line[MAX_LEN];
	char tokenBuffer[MAX_LEN];
	char *token;
	int token_count = 0;
	int vertex[2];

	// open files for reading and writing
	FILE *in = fopen(argv[1], "r");
	if (!in) {
		fprintf(stderr, "Error. Couldn't open input file.\n");
		exit(EXIT_FAILURE);
	}

	FILE *out = fopen(argv[2], "w");
	if (!out) {
		fprintf(stderr, "Error. Couldn't open output file.\n");
		exit(EXIT_FAILURE);
	}

	// read first line to get n
	int n = atoi(fgets(line, MAX_LEN, in));
	Graph G = newGraph(n);

// load and print adjacency list ---------------------------------------------------------
	while (atoi(fgets(line, MAX_LEN, in)) != 0)  {
	      	// get tokens in this line
	      	tokenBuffer[0] = '\0';
		token_count = 0;

      		// get first token
      		token = strtok(line, " \n");
      
      		while (token) { // we have a token
         		// update token buffer
         		strcat(tokenBuffer, "   ");
         		strcat(tokenBuffer, token);
         		strcat(tokenBuffer, " \n");

         		// get next token
			vertex[token_count] = atoi(token);
			token_count++;
      			token = strtok(NULL, " \n");
      		}

      		// print tokens in this line
		addEdge(G, vertex[0], vertex[1]);
   	}	
	printGraph(out, G);

// find distance and shortest paths -------------------------------------------------------
	List L = newList();
	while (atoi(fgets(line, MAX_LEN, in)) != 0)  {	
	      	// get tokens in this line
	      	tokenBuffer[0] = '\0';
		token_count = 0;

      		// get first token
      		token = strtok(line, " \n");
      
      		while (token) { // we have a token
         		// update token buffer
         		strcat(tokenBuffer, "   ");
         		strcat(tokenBuffer, token);
         		strcat(tokenBuffer, " \n");

         		// get next token
			vertex[token_count] = atoi(token);
			token_count++;
      			token = strtok(NULL, " \n");
      		}
		
		// distance
		BFS(G, vertex[0]);
		if (getDist(G, vertex[1]) == -100) {	
			fprintf(out, "\nThe distance from " FORMAT " to " FORMAT " is infinity \n", 
				vertex[0], vertex[1]);
		}
		else {
			fprintf(out, "\nThe distance from " FORMAT " to " FORMAT " is " FORMAT "\n", 
				vertex[0], vertex[1], getDist(G, vertex[1]));
		}

		// shortest path
		getPath(L, G, vertex[1]);
		if (front(L) == NIL) {
			fprintf(out, "No " FORMAT "-" FORMAT " path exists\n", 
				vertex[0], vertex[1]);
		}
		else {
			fprintf(out, "A shortest " FORMAT "-" FORMAT " path is: ", 
				vertex[0], vertex[1]);
			printList(out, L);
		}

		clear(L);
	}

	fclose(in);
	fclose(out);
	freeList(&L);
	freeGraph(&G);
  return 0;
}
