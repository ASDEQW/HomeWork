#include <iostream>
#include <chrono>
#include <vector>

using namespace std::chrono;
using namespace std;

vector <vector<bool>> form_matrix(int n)
{
	vector <vector<bool>> a;

	switch (n)
	{
	case 5:
	{
		a = {
			{1, 0, 0, 1, 0},
			{0, 1, 0, 0, 0},
			{1, 1, 1, 0, 1},
			{0, 0, 1, 1, 1},
			{0, 1, 0, 0, 1},
		};
		break;
	}
	case 10:
	{
		a = {
			{1, 0, 0, 1, 0, 1, 0, 0, 0, 0},
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
			{1, 1, 1, 0, 1, 0, 0, 0, 0, 0},
			{0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
			{0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
			{0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
			{0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
			{0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
			{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
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
	}


	return a;

}

int min(int x, int y)
{
	if (x > y) return y;
	else return x;
}

vector <vector<bool>> algoritm_floyda(int n)
{
	vector <vector<bool>> a;
	
	int error = 0;
	a = form_matrix(n);

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; k++)
			for (int j = 0; j < n; j++)
				a[i][j] = min (a[i][j], a[i][k] + a[k][j]);


	return a;

}
