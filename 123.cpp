#include <iostream>
#include <chrono>
#include <vector>

using namespace std::chrono;
using namespace std;

vector <vector<int>> form_matrix(int n)
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
				v.push_back(rand() % 2);
			}
			a.push_back(v);
		}
		break;
	}
	}


	return a;

}

int min(int x, int y)
{
	if (x > y) return y;
	else return x;
}

vector <vector<int>> algoritm_floyda(int n)
{
	vector <vector<int>> a;

	int error = 0;
	a = form_matrix(n);

	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; k++)
			for (int j = 0; j < n; j++)
				a[i][j] = min(a[i][j], a[i][k] + a[k][j]);


	return a;

}

int main()
{
	vector <vector<int>> a;
	int n = 5;

	setlocale(LC_ALL, "Russian");


	auto start = system_clock::now();
	a = algoritm_floyda(n);
	auto finish = system_clock::now();

	auto duration = duration_cast<microseconds>(finish - start).count();

	cout << duration << " mcs" << endl;
}
