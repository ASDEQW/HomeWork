#pragma once
#include "graph.h"

using namespace chrono;

void OutPath(vector<int>& parent, int TermPoint, fstream& outing, vector<vector<pair<int, int>>> OverPastGraph);
void Dijkstra(vector<vector<pair<int, int>>> VectEdgesWithWeight, int NumVertices, fstream& outing, vector<vector<pair<int, int>>> OverpastGraph,
	high_resolution_clock::time_point& StartTime, high_resolution_clock::time_point& EndTime);
void Dijkstra_begin(const Graph& CurrentGraph, int CurrentNumGraph, fstream& outing);
