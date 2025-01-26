# INTRODUCTION
- Name: Aaron Zeile
- This program creates a graph ADT utilizing functions from a previously created list ADT
# INPUT FORMAT
Input files to be utilized by the program are formatted as such:
6
1 2
1 3
2 4
2 5
2 6
3 4
4 5
5 6
0 0
1 5
3 6
2 3
4 4
0 0
The first line indicates the number of vertices in the graph (so, in this case, 6). The following lines indicate an edge connecting the two given vertices, until we reach a dummy line "0 0." Then, the next lines indicate a shortest path to be found between two vertices. For example, the first line after the dummy is "1 5," so the program will find a shortest path from vertex 1 to vertex 5.
# List.h
Contains prototypes for list ADT functions
# List.c
Contains bodies for List ADT functions
# Graph.h
Contains prototypes for Graph ADT functions
# Graph.c
Contains bodies of Graph ADT functions
# FindPath.c
Reads from an input file, comprehends it using the Graph ADT and sends it (formatted) to an output file
# Makefile
Used to quickly compile and test code
