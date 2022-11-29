#include "Graph.h"

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

void ShowGraph(Graph& SomeGraph)
{
	for (int IniPoint = 0; IniPoint < SomeGraph.NumVertices; IniPoint++)
	{
		cout << " [" << IniPoint << "] " << ">";
		for (auto& TermPoint : SomeGraph.IncidenceMatrixWithWeight[IniPoint])
			cout << " (" << TermPoint.first << ") " << "W: " << TermPoint.second << ",  ";
		cout << endl;
	}
}


