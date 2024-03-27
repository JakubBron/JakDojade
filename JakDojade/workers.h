#pragma once
#include "constants.hpp"
#include "helpers.h"
#include "Vector.h"
#include <utility>
#include "Queue.h"
#include "PriorityQueue.h"

void BFS(int markerVisited, pairInt start, Vector<graphNode>* graph, int** visited, char** map, int* miasta, int m, int n, city* cities);
void Dijkstra(int start, int end, int printPath, Vector<graphNode>* graph, bool visited[], int size, int marker, city* cities, bool flag);