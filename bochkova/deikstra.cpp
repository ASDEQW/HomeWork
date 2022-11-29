#include "Dijkstra.h"

void OutPath(vector<int>& parent, int TermPoint, fstream& outing, vector<vector<pair<int, int>>> OverPastGraph)
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
		outing << ShortPath[CurrentShortPath] << " > ";
	}
	cout << ShortPath[ShortPath.size() - 1] << " ";;
	outing << ShortPath[ShortPath.size() - 1] << " ";

	int Weight = 0;
	for (int CurrentShortPath = 0; CurrentShortPath < (int)ShortPath.size() - 1; CurrentShortPath++)
		for (auto& TermPoint : OverPastGraph[ShortPath[CurrentShortPath]])
			if (TermPoint.first == ShortPath[CurrentShortPath + 1])
				Weight += TermPoint.second;
	cout << " WEIGHT WAY : " << Weight;
	outing << " WEIGHT WAY : " << Weight;
}

void Dijkstra(vector<vector<pair<int, int>>> VectEdgesWithWeight, int NumVertices, fstream& outing, vector<vector<pair<int, int>>> OverpastGraph,
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
	outing << "Initial Point : " << NumVertices << endl;
	for (int CurrentNumEdge = 0; CurrentNumEdge < NumEdges; CurrentNumEdge++)
	{
		if (VectTermPoint[CurrentNumEdge] == INT_MAX) continue;
		cout << NumVertices << " >> " << CurrentNumEdge << " WAY: ";
		outing << NumVertices << " >> " << CurrentNumEdge << " WAY: ";
		OutPath(SourceEdges, CurrentNumEdge, outing, OverpastGraph);
		cout << endl;
		outing << endl;
	}
	cout << endl;
	outing << endl;
}

void Dijkstra_begin(const Graph& CurrentGraph, int CurrentNumGraph, fstream& outing)
{
	outing << "____________________________________Graph [" << CurrentNumGraph + 1 << "]___________________________________________" << endl;
	high_resolution_clock::time_point StartTime = high_resolution_clock::now();

	vector<vector<pair<int, int>>> UsedDijkstra = CurrentGraph.IncidenceMatrixWithWeight;


	high_resolution_clock::time_point EndTime = high_resolution_clock::now();
	duration<double, milli> TimeSpent = EndTime - StartTime;

	for (int CurrentNumVertices = 0; CurrentNumVertices < CurrentGraph.NumVertices; CurrentNumVertices++)
	{
		high_resolution_clock::time_point StartIntermediateTime;
		high_resolution_clock::time_point EndIntermediateTime;
		Dijkstra(UsedDijkstra, CurrentNumVertices, outing, CurrentGraph.IncidenceMatrixWithWeight, StartIntermediateTime, EndIntermediateTime);
		duration<double, milli> IntermediateTimeSpent = EndIntermediateTime - StartIntermediateTime;
		TimeSpent += IntermediateTimeSpent;
	}

	cout << "\n Time spent: " << TimeSpent.count() << " ms" << endl;
	outing << " Time spent: " << TimeSpent.count() << " ms" << endl;
}
