#include <iostream>
#include <chrono>
#include <vector>
#include "Header.h"
using namespace std;


vector <int> AStar_Algo(vector<vector<int>> graph) {
	int n = graph.size();
	vector <int> heu;
	for (int i = 0; i < n; i++)
	{
		heu.push_back(rand() % 10 - 5);
	}
	int start = 0;
	int goal = 1;
	vector <int> expanded = {};
	vector <int> path;
	vector <int> parents(graph.size(), -1);
	priority_queue<vector <int>, vector <vector <int>>, greater<vector <int>>> frontier;
	frontier.push({ heu[start], start, -1 });
	vector <int> temp;
	int gChild, hChild, fChild, node;

	while (!frontier.empty())
	{
		temp = frontier.top();
		frontier.pop();
		//printPQ(frontier);
		//cout << "Temp: ";
		//printVec(temp);
		if (expanded.empty() || find(expanded.begin(), expanded.end(), temp[1]) == expanded.end()) {
			expanded.push_back(temp[1]);
			parents[temp[1]] = temp[2];

			if (temp[1] == goal) {
				node = temp[1];
				while (parents[node] != -1) {
					path.push_back(node);
					node = parents[node];
				}

				path.push_back(start);
				reverse(path.begin(), path.end());
				return path;
			}
			//printVec(graph[temp[1]]);
			for (int child = 0; child < graph[temp[1]].size(); child++) {
				if (find(expanded.begin(), expanded.end(), child) == expanded.end() && graph[temp[1]][child] != 0) {
					gChild = temp[0] + graph[temp[1]][child];
					hChild = heu[child];
					fChild = gChild + hChild - heu[temp[1]];
					frontier.push({ fChild, child, temp[1] });
				}
			}
		}
	}

	return {};
}

vector<vector <int>> readTheFile(string input, vector <int>& Heuristic, int& start, int& goal) {
	vector <vector <int>> Graph;
	int numberOfVertices;
	ifstream openFile;
	openFile.open(input);
	if (!openFile.is_open()) cout << "Unable to open file.\n";
	else
	{
		string line;
		getline(openFile, line);
		numberOfVertices = stoi(line);
		Graph = vector <vector <int>>(numberOfVertices);
		Heuristic = vector <int>(numberOfVertices);
		vector <int> row(numberOfVertices);
		getline(openFile, line);
		stringstream ss(line);
		ss >> start;
		ss >> goal;
		int rowIdx = 0, index = 0;
		//Array = vector <int>(stoi(line));
		//getline(openFile, line);
		string num;
		while (getline(openFile, line) && rowIdx < numberOfVertices)
		{
			istringstream ss(line);
			while (ss >> num) {
				row[index] = stoi(num);
				index++;
			}
			Graph[rowIdx] = row;
			row.clear();
			row = vector <int>(numberOfVertices);
			index = 0;
			rowIdx++;
		}
		index = 0;
		getline(openFile, line);
		istringstream sh(line);
		while (sh >> num) {
			Heuristic[index] = stoi(num);
			index++;
		}
	}
	return Graph;
}