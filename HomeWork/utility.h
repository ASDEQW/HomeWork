#pragma once
#include <vector>
#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>

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

vector <vector<bool>> form_matrix_bool(int n)
{
	vector <vector<bool>> a;

	switch (n)
	{
	case 5:
	{
		a = {
			{0, 1, 0, 0, 1},
			{0, 0, 1, 1, 1},
			{0, 0, 0, 1, 0},
			{1, 1, 1, 0, 0},
			{0, 1, 0, 1, 0}
		};
		break;
	}
	case 10:
	{
		a = {
			{0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
			{0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
			{0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
			{1, 1, 1, 0, 0, 1, 1, 0, 1, 0},
			{0, 1, 0, 1, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 1, 0, 1, 0, 0, 0},
			{0, 0, 1, 1, 0, 1, 0, 1, 0, 0},
			{0, 0, 1, 0, 0, 0, 1, 0, 1, 0},
			{0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		};
		break;
	}
	default:
	{
		for (int i = 0; i < n; i++)
		{
			vector<bool> v;
			for (int j = 0; j < n; j++)
			{
				v.push_back(rand() % 2);
			}
			a.push_back(v);
		}
	}
	break;
	}


	return a;

}

vector <vector<int>> form_matrix_int(int n)
{
	vector <vector<int>> a;

	switch (n)
	{
	case 5:
	{
		a = {
			{0, -3, 0, 0, 2},
			{0, 0, -5, 15, 12},
			{0, 0, 0, 8, 0},
			{6, 15, 8, 0, 0},
			{0, 12, 0, -7, 0}
		};
		break;
	}
	case 10:
	{
		a = {
			{0, -3, 0, 0, 2, 0, 0, 0, 0, 0},
			{0, 0, -5, 15, 12, 0, 0, 0, 0, 0},
			{0, 0, 0, 8, 0, 0, 0, 24, 0, 0},
			{6, 15, 8, 0, 0, 18, 4, 0, 11, 0},
			{0, 12, 0, -7, 0, 20, 0, 0, 0, 0},
			{0, 0, 0, 0, 20, 0, 9, 0, 0, 0},
			{0, 0, -10, 4, 0, 9, 0, 16, 0, 0},
			{0, 0, 24, 0, 0, 0, 16, 0, 22, 0},
			{0, 0, 0, 11, 0, -13, 0, 0, 0, 4},
			{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		};
		break;
	}
	default:
	{
		for (int i = 0; i < n; i++)
		{
			vector<int> v;
			for (int j = 0; j < n; j++)
			{
				v.push_back(rand() % 10 - 5);
			}
			a.push_back(v);
		}
		break;
	}
	}

	return a;

}

vector <int> Johnson(const Graph& CurrentGraph);
 
Graph form_graph_for_djonson(int n)
{
	vector<Edge> VectEdges;
	int Vertices = 0;
	vector <vector<int>> matrix = form_matrix_int(n);
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

	const Graph CurrentGraph(VectEdges, matrix.size());
	return CurrentGraph;
}

void Run_Floyd(int n)
{
	vector <vector<int>> a_int = form_matrix_int(n);
	vector <int> b;
	auto start = system_clock::now();
	b = algoritm_floyda(a_int);
	auto finish = system_clock::now();

	auto duration = duration_cast<microseconds>(finish - start).count();

	cout << duration << " mcs" << endl;
}

void Run_Li(int n)
{
	vector <vector<bool>> a_bool = form_matrix_bool(n);
	vector <int> b;
	auto start = system_clock::now();
	b = algoritm_li(a_bool);
	auto finish = system_clock::now();

	auto duration = duration_cast<microseconds>(finish - start).count();

	cout << duration << " mcs" << endl;
}

void Run_AStar(int n)
{
	vector <vector<int>> a_int = form_matrix_int(n);
	vector <int> b;
	auto start = system_clock::now();
	b = AStar_Algo(a_int);
	auto finish = system_clock::now();

	auto duration = duration_cast<microseconds>(finish - start).count();

	cout << duration << " mcs" << endl;
}


void Run_Djonson(int n)
{
	const Graph g = form_graph_for_djonson(n);
	vector <int> b;
	auto start = system_clock::now();
	b = Johnson(g);
	auto finish = system_clock::now();

	auto duration = duration_cast<microseconds>(finish - start).count();

	cout << duration << " mcs" << endl;
}

void Run_Ford(int n)
{
	vector <vector<int>> a_int = form_matrix_int(n);
	vector <int> b;
	auto start = system_clock::now();
	b = algoritm_forda_belmana(a_int);
	auto finish = system_clock::now();

	auto duration = duration_cast<microseconds>(finish - start).count();

	cout << duration << " mcs" << endl;
}

void Run_Deikstra(int n)
{
	vector <vector<int>> a_int = form_matrix_int(n);
	vector <int> b;
	auto start = system_clock::now();
	b = Dijkstra(a_int);
	auto finish = system_clock::now();

	auto duration = duration_cast<microseconds>(finish - start).count();

	cout << duration << " mcs" << endl;
}

void menu()
{
	cout << "Меню: " << endl;
	cout << "1 - Алгоритм Флойда" << endl;
	cout << "2 - Алгоритм Ли" << endl;
	cout << "3 - Алгоритм А*" << endl;
	cout << "4 - Алгоритм Джонсона" << endl;
	cout << "5 - Алгоритм Форда" << endl;
	cout << "6 - Алгоритм Дейкстры" << endl;
	cout << "Введите номер алгоритма: ";
}

void Run(int method_number, int n)
{
	cout << "N = " << n << ": ";
	switch (method_number)
	{
	case 1:
	{
		Run_Floyd(n);
		break;
	}
	case 2:
	{
		Run_Li(n);
		break;
	}
	case 3:
	{
		Run_AStar(n);
		break;
	}
	case 4:
	{
		Run_Djonson(n);
		break;
	}
	case 5:
	{
		Run_Ford(n);
		break;
	}
	case 6:
	{
		Run_Deikstra(n);
		break;
	}
	}
}