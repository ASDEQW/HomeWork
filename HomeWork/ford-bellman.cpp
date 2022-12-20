#include <iostream>
#include <chrono>
#include <vector>

using namespace std::chrono;
using namespace std;



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