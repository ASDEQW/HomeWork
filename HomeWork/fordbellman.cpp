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
			{0, 0, 0, 1, 0},
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
			{0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
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
	int n;
	cout << "Размерность: ";
	cin >> n;
	auto st = chrono::high_resolution_clock::now();
	vector <vector<int>> a;
	a = form_matrix(n);
	const int INF = 1e9;
	vector <vector<int> > Mas_rast(n, vector<int>(10000, INF));
	Mas_rast[0][0] = 0;
	for (int k = 1; k < n; k++) {
		for (int i = 0; i < n; i++) {
			Mas_rast[k][i] = Mas_rast[k - 1][i];
			for (int j = 0; j < n; j++) {	
				if (Mas_rast[k - 1][j] + a[j][i] < Mas_rast[k][i]) {
					Mas_rast[k][i] = Mas_rast[k - 1][j] + a[j][i];
					if (k != 1) {
						cout << "Расстояние  " << Mas_rast[k][i] << " до вершины " << i << " cодержащего не более " << k << " рёбер" << endl;
					}
					else {
						cout << "Расстояние  " << Mas_rast[k][i] << " до вершины " << i << " cодержащего не более " << k << " ребра" << endl;
					}
				}
			}
		}
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> duration = end - st;
	cout << "Длительность: " << duration.count();
}
void main()
{
	setlocale(LC_ALL, "Rus");
	algoritm_forda_belmana();
}