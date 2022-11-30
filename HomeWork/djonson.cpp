#include <vector>
#include <set>
#include <queue>
#include <time.h>
#include <chrono>
#include <string>
#include <iostream>

using namespace std;
using namespace chrono;

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

Graph::Graph(vector<Edge>& VectStructEdge, int NumVertices)
{
	WeightMatrix.resize(NumVertices, vector<int>(NumVertices, INT_MAX));
	IncidenceMatrixWithWeight.resize(NumVertices);
	this->NumVertices = NumVertices;
	this->VectStructEdge = VectStructEdge;

	for (auto& iterEdge : VectStructEdge)
	{
		IncidenceMatrixWithWeight[iterEdge.InitialPoint].push_back(make_pair(iterEdge.TerminalPoint, iterEdge.Weight));
		WeightMatrix[iterEdge.InitialPoint][iterEdge.TerminalPoint] = iterEdge.Weight;
	}

	for (int i = 0; i < NumVertices; i++)
		WeightMatrix[i][i] = 0;
}



void OutPath(vector<int>& parent, int TermPoint, vector<vector<pair<int, int>>> OverPastGraph)
{
	vector<int> ShortPath;
	while (TermPoint != -1)
	{
		ShortPath.push_back(TermPoint);
		TermPoint = parent[TermPoint];
	}
	reverse(ShortPath.begin(), ShortPath.end());


	int Weight = 0;
	for (int CurrentShortPath = 0; CurrentShortPath < (int)ShortPath.size() - 1; CurrentShortPath++)
		for (auto& TermPoint : OverPastGraph[ShortPath[CurrentShortPath]])
			if (TermPoint.first == ShortPath[CurrentShortPath + 1])
				Weight += TermPoint.second;
}


vector<int> FordBellman(vector<Edge> VectStructEdge, int NumVertices)
{

	vector<int> TerminalPoint(NumVertices + 1, INT_MAX);
	TerminalPoint[NumVertices] = 0;

	for (int CurrentNumVertices = 0; CurrentNumVertices < NumVertices; CurrentNumVertices++)
	{
		Edge CurrentEdge;
		CurrentEdge.InitialPoint = NumVertices;
		CurrentEdge.TerminalPoint = CurrentNumVertices;
		CurrentEdge.Weight = 0;
		VectStructEdge.push_back(CurrentEdge);
	}

	for (int CurrentNumVertices = 0; CurrentNumVertices < NumVertices; CurrentNumVertices++)
	{
		bool Mark = false;
		for (auto& IterVectStructEdge : VectStructEdge)
		{
			int IniPoint = IterVectStructEdge.InitialPoint;
			int TermPoint = IterVectStructEdge.TerminalPoint;
			int Weight = IterVectStructEdge.Weight;
			if (TerminalPoint[IniPoint] != INT_MAX && TerminalPoint[TermPoint] > TerminalPoint[IniPoint] + Weight)
			{
				TerminalPoint[TermPoint] = TerminalPoint[IniPoint] + Weight;
				Mark = true;
			}
		}
		if (Mark == false)
		{
			break;
		}
	}

	for (auto& IterVectStructEdge : VectStructEdge)
	{
		int IniPoint = IterVectStructEdge.InitialPoint;
		int TermPoint = IterVectStructEdge.TerminalPoint;
		int Weight = IterVectStructEdge.Weight;
		if (TerminalPoint[IniPoint] != INT_MAX && TerminalPoint[TermPoint] > TerminalPoint[IniPoint] + Weight)
		{
			return {};
		}
	}

	vector<int> Answer(TerminalPoint.begin(), TerminalPoint.end() - 1);

	return Answer;

}

void Dijkstra(vector<vector<pair<int, int>>> VectEdgesWithWeight, int NumVertices, vector<vector<pair<int, int>>> OverpastGraph,
	high_resolution_clock::time_point& StartTime, high_resolution_clock::time_point& EndTime)
{
	StartTime = high_resolution_clock::now();

	int NumEdges = VectEdgesWithWeight.size();

	vector<int> SourceEdges(NumEdges);
	SourceEdges[NumVertices] = -1;

	vector<int> VectTermPoint(NumEdges, INT_MAX);
	VectTermPoint[NumVertices] = 0;

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> QueueVector;
	QueueVector.push(make_pair(0, NumVertices));

	while (!QueueVector.empty())
	{
		pair<int, int> Vertex = QueueVector.top();
		QueueVector.pop();

		if (Vertex.first > VectTermPoint[Vertex.second])
			continue;

		for (auto CurrentNumEdge : VectEdgesWithWeight[Vertex.second])
		{
			int IniPoint = Vertex.second;
			int TermPoint = CurrentNumEdge.first;
			int Weight = CurrentNumEdge.second;
			if (VectTermPoint[TermPoint] > VectTermPoint[IniPoint] + Weight)
			{
				VectTermPoint[TermPoint] = VectTermPoint[IniPoint] + Weight;
				QueueVector.push(make_pair(VectTermPoint[TermPoint], TermPoint));
				SourceEdges[TermPoint] = IniPoint;
			}
		}
	}

	EndTime = high_resolution_clock::now();

	for (int CurrentNumEdge = 0; CurrentNumEdge < NumEdges; CurrentNumEdge++)
	{
		if (VectTermPoint[CurrentNumEdge] == INT_MAX) continue;

		OutPath(SourceEdges, CurrentNumEdge, OverpastGraph);
	}
}

vector <int> Johnson(const Graph& CurrentGraph)
{
	vector <int> b = {};
	vector<int> UsedFordBellman = FordBellman(CurrentGraph.VectStructEdge, CurrentGraph.NumVertices);

	if (UsedFordBellman.empty())
	{
		return b;
	}

	vector<vector<pair<int, int>>> UsedDijkstra = CurrentGraph.IncidenceMatrixWithWeight;

	for (int InitialPoint = 0; InitialPoint < CurrentGraph.NumVertices; InitialPoint++)
	{
		for (auto& TerminalPoint : UsedDijkstra[InitialPoint])
		{
			TerminalPoint.second = TerminalPoint.second + UsedFordBellman[InitialPoint] - UsedFordBellman[TerminalPoint.first];
			b.push_back(TerminalPoint.second);
		}
	}


	return b;
}
