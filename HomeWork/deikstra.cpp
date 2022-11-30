#include <iostream>
#include <chrono>
#include <vector>
using namespace std;


vector <int> Dijkstra(vector <vector<int>>& a)
{
	int V = a.size();
	int st = a.size() - 1;
	vector <int> b(V);
	int *distance = new int[V], count, index, i, u, m = st + 1;
	bool *visited = new bool[V];
	for (int j = 0; j < V; j++)
	{
		for (i = 0; i < V; i++)
		{
			distance[i] = INT_MAX; visited[i] = false;
		}
		distance[j] = 0;
		for (count = 0; count < V - 1; count++)
		{
			int min = INT_MAX;
			for (i = 0; i < V; i++)
				if (!visited[i] && distance[i] <= min)
				{
					min = distance[i]; index = i;
				}
			u = index;
			visited[u] = true;
			for (i = 0; i < V; i++)
				if (!visited[i] && a[u][i] && distance[u] != INT_MAX &&
					distance[u] + a[u][i] < distance[i])
					distance[i] = distance[u] + a[u][i];
		}
	}

	for (int i = 0; i < V; i++)
	{
		b[i] = distance[i];
	}

	return b;
}
