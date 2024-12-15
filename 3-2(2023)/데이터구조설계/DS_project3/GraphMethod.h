#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"

bool BFS(Graph* graph, char option, int vertex, ofstream* fout);     
bool DFS(Graph* graph, char option,  int vertex, ofstream* fout);     
bool KWANGWOON(Graph* graph, int vertex, ofstream* fout);  
bool Kruskal(Graph* graph, ofstream* fout);
bool Dijkstra(Graph* graph, char option, int vertex, ofstream* fout);    //Dijkstra
bool Bellmanford(Graph* graph, char option, int s_vertex, int e_vertex, ofstream* fout); //Bellman - Ford
bool FLOYD(Graph* graph, char option, ofstream* fout);   //FLoyd

void quicksort(int array[], int leftIndex, int rightIndex);
void insertionsort(int array[], int startIndex, int endIndex);
void insertion(int element, int array[], int size);
void unionset(int vertexA, int vertexB, int parent[]);
int findset(int vertex, int parent[]);

#endif
