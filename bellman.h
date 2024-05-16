#ifndef BELLMAN_H
#define BELLMAN_H
#include "main.h"
void BF(int graph[][max_vertices], int num_vertices, char start_vertex, int BFVal[], int BFPrev[]);
string BF_Path(int graph[][max_vertices], int num_vertices, char start_vertex, char goal_vertex);
#endif