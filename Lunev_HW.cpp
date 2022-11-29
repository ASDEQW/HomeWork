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
			vector<int> v;
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




void algoritm_forda_belmana()
{
	auto st = chrono::high_resolution_clock::now();
	int n;
	n = 5;
	cout << "Размерность: " << n << endl;
	vector <vector<int>> a;
	a = form_matrix(n);
	const int INF = 1e9;
	vector <vector<int> > f(n, vector<int>(10000, INF));
	f[0][0] = 0;
	for (int k = 1; k < n; k++) {
		for (int i = 0; i < n; i++) {
			f[k][i] = f[k - 1][i];
			for (int j = 0; j < n; j++) {
				if (f[k - 1][j] + a[j][i] < f[k][i]) {
					f[k][i] = f[k - 1][j] + a[j][i];
				}
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> duration = end - st;
	cout << "vremya" << duration.count();
}
void main()
{
	setlocale(LC_ALL, "Rus");
	algoritm_forda_belmana();
}