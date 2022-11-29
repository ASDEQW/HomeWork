#pragma once

#include <vector>
#include <set>
#include <queue>
#include <time.h>
#include <chrono>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

struct Edge
{
	int InitialPoint;
	int TerminalPoint;
	int Weight;
};

class Graph
{
public:
	int NumVertices;
	vector<vector<int>> WeightMatrix;
	vector<Edge> VectStructEdge;
	vector<vector<pair<int, int>>> IncidenceMatrixWithWeight;
	Graph(vector<Edge>& VectStructEdge, int NumVertices);
};

void ShowGraph(Graph& SomeGraph);

