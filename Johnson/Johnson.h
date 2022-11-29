#pragma once
#include "Graph.h"

using namespace chrono;

void OutPath(vector<int>& parent, int TermPoint, fstream& outing, vector<vector<pair<int, int>>> OverPastGraph);
vector<int> FordBellman(vector<Edge> VectStructEdge, int NumVertices);
void Dijkstra(vector<vector<pair<int, int>>> VectEdgesWithWeight, int NumVertices, fstream& outing, vector<vector<pair<int, int>>> OverpastGraph,
	high_resolution_clock::time_point& StartTime, high_resolution_clock::time_point& EndTime);
void Johnson(const Graph& CurrentGraph, int CurrentNumGraph, fstream& outing);
