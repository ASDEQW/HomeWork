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


void OutPath(vector<int>& parent, int TermPoint, vector<vector<pair<int, int>>> OverPastGraph)
{
	vector<int> ShortPath;
	while (TermPoint != -1)
	{
		ShortPath.push_back(TermPoint);
		TermPoint = parent[TermPoint];
	}
	reverse(ShortPath.begin(), ShortPath.end());

	for (int CurrentShortPath = 0; CurrentShortPath < (int)ShortPath.size() - 1; CurrentShortPath++)
	{
		cout << ShortPath[CurrentShortPath] << " > ";
	}
	cout << ShortPath[ShortPath.size() - 1] << " ";;

	int Weight = 0;
	for (int CurrentShortPath = 0; CurrentShortPath < (int)ShortPath.size() - 1; CurrentShortPath++)
		for (auto& TermPoint : OverPastGraph[ShortPath[CurrentShortPath]])
			if (TermPoint.first == ShortPath[CurrentShortPath + 1])
				Weight += TermPoint.second;
	cout << " WEIGHT WAY : " << Weight;
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

	cout << "Initial Point : " << NumVertices << endl;
	for (int CurrentNumEdge = 0; CurrentNumEdge < NumEdges; CurrentNumEdge++)
	{
		if (VectTermPoint[CurrentNumEdge] == INT_MAX) continue;
		cout << NumVertices << " >> " << CurrentNumEdge << " WAY: ";
		OutPath(SourceEdges, CurrentNumEdge, OverpastGraph);
		cout << endl;
	}
	cout << endl;
}

void Johnson(const Graph& CurrentGraph)
{
	high_resolution_clock::time_point StartTime = high_resolution_clock::now();
	vector<int> UsedFordBellman = FordBellman(CurrentGraph.VectStructEdge, CurrentGraph.NumVertices);

	if (UsedFordBellman.empty())
	{
		high_resolution_clock::time_point EndTime = high_resolution_clock::now();
		duration<double, milli> TimeSpent = EndTime - StartTime;
		cout << " ERORR! Graph has weight cycle less than zero " << endl;
		cout << "\n Time spent: " << TimeSpent.count() << " ms" << endl;
		return;
	}

	vector<vector<pair<int, int>>> UsedDijkstra = CurrentGraph.IncidenceMatrixWithWeight;

	for (int InitialPoint = 0; InitialPoint < CurrentGraph.NumVertices; InitialPoint++)
	{
		for (auto& TerminalPoint : UsedDijkstra[InitialPoint])
		{
			TerminalPoint.second = TerminalPoint.second + UsedFordBellman[InitialPoint] - UsedFordBellman[TerminalPoint.first];
		}
	}

	high_resolution_clock::time_point EndTime = high_resolution_clock::now();
	duration<double, milli> TimeSpent = EndTime - StartTime;

	for (int CurrentNumVertices = 0; CurrentNumVertices < CurrentGraph.NumVertices; CurrentNumVertices++)
	{
		high_resolution_clock::time_point StartIntermediateTime;
		high_resolution_clock::time_point EndIntermediateTime;
		Dijkstra(UsedDijkstra, CurrentNumVertices, CurrentGraph.IncidenceMatrixWithWeight, StartIntermediateTime, EndIntermediateTime);
		duration<double, milli> IntermediateTimeSpent = EndIntermediateTime - StartIntermediateTime;
		TimeSpent += IntermediateTimeSpent;
	}

	cout << "\n Time spent: " << TimeSpent.count() << " ms" << endl;
}

void Run_Johnson(vector <vector<int>> matrix)
{
	vector<Edge> VectEdges;
	int Vertices = 0;

	for (int i = 0; i < matrix.size(); i++)
	{
		for (int j = 0; j < matrix.size(); j++)
		{
			if (matrix[i][j] != 0) {
				Edge StructEdge;
				StructEdge.InitialPoint = i;
				StructEdge.TerminalPoint = j;
				StructEdge.Weight = matrix[i][j];
				VectEdges.push_back(StructEdge);
			}
		}
	}

	Graph CurrentGraph(VectEdges, matrix.size());

	cout << "	[WAYS AT GRAPH]" << endl;
	ShowGraph(CurrentGraph);
	cout << endl;
	cout << "	[ALL PAIRS SHORTEST PATH]" << endl;
	Johnson(CurrentGraph);
	cout << "------------------------------------------------------------------------------------------------------------------" << endl;

}