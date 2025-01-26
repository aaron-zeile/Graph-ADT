# INTRODUCTION
- Name: Aaron Zeile
- This program creates a graph ADT utilizing functions from a previously created list ADT
# INPUT FORMAT
Input files to be utilized by the program are formatted as such:
- The first line will be a single integer indicating the number of vertices in the graph. 
- The following lines will consist of two integers (separated by a space), each representing a vertex, which indicates an edge connecting the two given vertices. For example, a line "2 9" would indicate an edge connecting vertices 2 and 9.
- Beneath these edge lines, there is a dummy line "0 0." When the program reaches this dummy line, it knows to stop creating edges.
- Following the dummy line, there will be more 2-integer lines which indicate a shortest path to be found between two vertices. For example, a line "1 5," would indicate that the program must find a shortest path from vertex 1 to vertex 5. These paths will be found using BFS.
- Finally, the file is terminated with another dummy line "0 0," letting the program know to stop reading.
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
