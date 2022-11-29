#include "utility.h"

using namespace std;

void Help()
{
	string DelimeterScreen = "******************************************************************************************************************";
	cout << endl << DelimeterScreen << endl
		<< " Johnson's algorithm ( Dijkstra's + Bellman-Ford's algorithm ) = JA . All Pairs Shortest Path = APSP" << endl
		<< " 0. Exit" << endl
		<< " 1. Create default graphs " << endl
		<< " 2. Create random graphs " << endl
		<< " 3. Create graph by hand" << endl
		<< " 4. Find APSP with JA" << endl << endl
		<< DelimeterScreen << endl
		<< " Enter command: ";
}

bool checker_bool() // Проверка на булевое значение
{
	bool in;
	while (1) {
		if (cin >> in)
		{
			cin.ignore(1024, '\n'); // Отсекать всё, что дальше пробела
			return(in);
		}
		else
		{
			cout << "\n Incorrect input. Try again. Enter 0 or 1: ";
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
};

int Checker() // Проверка на положительное число 
{
	int in;
	while (1) {
		if ((cin >> in) && (in >= 0))
		{
			cin.ignore(1024, '\n');
			return(in);
		}
		else
		{
			cout << "\n Incorrect input. Try again. Enter positive number: ";
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}
}

int Checker(int LeftInterval, int RightInterval) // Проверка на число в интервале от a до b включительно
{
	int in;
	while (1) {

		if ((cin >> in) && (in >= LeftInterval) && (in <= RightInterval))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			return(in);
		}
		else
		{
			cout << "\n Incorrect input. Try again. Enter number from [" << LeftInterval << "] till [" << RightInterval << "]: ";
			cin.clear();
			cin.ignore(1024, '\n');
		}

	}
}

void CreateDefaultGraph()
{
	vector <vector<int>> matrix5, matrix10;

	matrix5 = {
			{0, -3, 0, 0, 2},
			{0, 0, -5, 15, 12},
			{0, 0, 0, 8, 0},
			{6, 15, 8, 0, 0},
			{0, 12, 0, -7, 0}
	};

	matrix10 = {
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

	fstream outing1("a5.txt", ios::out | ios::trunc);

	int num_edges = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (matrix5[i][j] != 0) {
				num_edges++;
			}
		}
	}

	outing1 << 1 << endl;
	outing1 << 5 << " " << num_edges << endl;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (matrix5[i][j] != 0) {
				outing1 << i << " " << j << " " << abs(matrix5[i][j]) << endl;
			}
		}
	}
	outing1 << endl;
	outing1.close();

	fstream outing2("a10.txt", ios::out | ios::trunc);

	num_edges = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (matrix10[i][j] != 0) {
				num_edges++;
			}
		}
	}

	outing2 << 1 << endl;
	outing2 << 10 << " " << num_edges << endl;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (matrix10[i][j] != 0) {
				outing2 << i << " " << j << " " << abs(matrix10[i][j]) << endl;
			}
		}
	}
	outing2 << endl;
	outing2.close();
}

bool checker_exist_file(const string& name_file)
{
	ifstream exist(name_file + ".txt"); // Проверка существования файла
	bool file_exist;
	exist.is_open() ? file_exist = 1 : file_exist = 0;
	exist.close();
	return(file_exist);
}

void CreateRandomGraphs()
{
	string name_file;
	do {
		cout << "\n Enter the name of file, using for saving data: ";
		getline(cin, name_file);
		if (checker_exist_file(name_file))
			cout << " This file is already exist. Rewrite file ? Yes 1 / No 0: ";
		else
			break;
	} while (!checker_bool());

	fstream outing(name_file + ".txt", ios::out | ios::trunc);

	if (outing.is_open()) {
		cout << " Enter number of vertices: ";
		int Vertices = Checker();
		cout << " Enter number of edges : ";
		int Edge = Checker();
		cout << " Enter max weight: ";
		int MaxWeight = Checker();

		cout << " Enter number of graph: ";
		int NumberOfGraphs = Checker(0, 100);
		outing << NumberOfGraphs << endl;
		srand((unsigned)time(NULL));

		for (int CurrentGraph = 0; CurrentGraph < NumberOfGraphs; CurrentGraph++)
		{
			while (Edge > Vertices * (Vertices - 1) / 2)
				Edge = 4 + rand() % (Edge - 4 + 1);

			outing << Vertices << " " << Edge << endl;

			set<pair<int, int>> SetPairEdges;

			for (int CurrentNumEdge = 1; CurrentNumEdge <= Edge; CurrentNumEdge++)
			{
				int IniPoint = rand() % Vertices;
				int TermPoint = rand() % Vertices;

				if (IniPoint == TermPoint)
				{
					CurrentNumEdge--;
					continue;
				}

				pair<int, int> edge = make_pair(IniPoint, TermPoint);
				pair<int, int> reverse_edge = make_pair(TermPoint, IniPoint);

				while (SetPairEdges.find(edge) != SetPairEdges.end() || SetPairEdges.find(reverse_edge) != SetPairEdges.end())
				{
					IniPoint = rand() % Vertices;
					TermPoint = rand() % Vertices;

					if (IniPoint == TermPoint) continue;

					edge = make_pair(IniPoint, TermPoint);
					reverse_edge = make_pair(TermPoint, IniPoint);
				}
				SetPairEdges.insert(edge);
			}

			for (auto iterSetPairEdges = SetPairEdges.begin(); iterSetPairEdges != SetPairEdges.end(); ++iterSetPairEdges)
			{
				int Weight = -30 + rand() % MaxWeight;
				outing << abs(iterSetPairEdges->first) << " " << abs(iterSetPairEdges->second) << " " << abs(Weight) << endl;
			}

			outing << endl;
		}

		outing.close();
	}
}

void CreateGraphsByHand()
{
	string name_file;
	do {
		cout << "\n Enter the name of file, using for saving data: ";
		getline(cin, name_file);
		if (checker_exist_file(name_file))
			cout << " This file is already exist. Rewrite file ? Yes 1 / No 0: ";
		else
			break;
	} while (!checker_bool());

	fstream outing(name_file + ".txt", ios::out | ios::trunc);

	if (outing.is_open()) {
		int NumberOfGraphs = 0;

		while (1)
		{
			NumberOfGraphs++;
			vector<Edge> VectEdges;
			int Vertices, Edges;
			cout << "Number of vertices: " << endl;
			cin >> Vertices;
			cout << "Number of edges: " << endl;
			cin >> Edges;
			outing << Vertices << " " << Edges << endl;

			cout << " Enter edge (Initial Point, Terminal Point, Weight) " << endl;
			for (int CurrentGraph = 0; CurrentGraph < Edges; CurrentGraph++)
			{
				Edge StructEdge;
				string s;
				cin >> StructEdge.InitialPoint;
				cin >> StructEdge.TerminalPoint;
				cin >> StructEdge.Weight;
				outing << StructEdge.InitialPoint << " " << StructEdge.TerminalPoint << " " << StructEdge.Weight << endl;
				VectEdges.push_back(StructEdge);
			}

			Graph NewGraph(VectEdges, Vertices);

			outing << endl;
			cout << endl << " Add else 1/0 ? ";
			if (!Checker(0, 1))
				break;
		}
		outing.seekg(0);
		outing << NumberOfGraphs << endl;
		outing.close();
	}
}

void FindAPSPwithDijkstra()
{
	string name_file_load;
	while (1) {
		cout << "\n Enter the name of file, using for loading data: ";
		getline(cin, name_file_load);
		if (checker_exist_file(name_file_load))
		{
			cout << "\n This file has been find ";
			break;
		}
		else
		{
			cout << " We cannot find this file. Try again ? Yes 1/ No 0: ";
			if (checker_bool() == false)
				break;
		}
	}
	fstream ining(name_file_load + ".txt", ios::in);

	fstream outing(name_file_load + "_result.txt", ios::out | ios::trunc);

	if (ining.is_open() && outing.is_open()) {
		int NumOfGraphs;
		ining >> NumOfGraphs;
		cout << endl << NumOfGraphs;
		for (int NumCurrentGraph = 0; NumCurrentGraph < NumOfGraphs; NumCurrentGraph++)
		{

			vector<Edge> VectEdges;
			int Vertices, Edges;

			ining >> Vertices >> Edges;

			for (int CurrentNumEdge = 0; CurrentNumEdge < Edges; CurrentNumEdge++)
			{
				Edge StructEdge;
				ining >> StructEdge.InitialPoint;
				ining >> StructEdge.TerminalPoint;
				ining >> StructEdge.Weight;
				VectEdges.push_back(StructEdge);
			}
			Graph CurrentGraph(VectEdges, Vertices);
			cout << "\n\n\n------------------------------------------------------Graph [" << NumCurrentGraph << "]---------------------------------------------------" << endl;
			cout << "	[WAYS AT GRAPH]" << endl;
			ShowGraph(CurrentGraph);
			cout << endl;
			cout << "	[ALL PAIRS SHORTEST PATH]" << endl;
			Dijkstra_begin(CurrentGraph, NumCurrentGraph, outing);
			cout << "------------------------------------------------------------------------------------------------------------------" << endl;
		}

		ining.close();
		outing.close();
	}
}