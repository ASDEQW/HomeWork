#include <iostream>
#include <chrono>
#include <vector>


using namespace std;



int min(int x, int y)
{
	if (x > y) return y;
	else return x;
}

vector <int> algoritm_floyda(vector <vector<int>> &a)
{

	int n = a.size();
	vector <int> b(n);

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
				b[k] = min(a[i][j], a[i][k] + a[k][j]);
			}

	return b;
}
