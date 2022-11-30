#include <iostream>
#include <chrono>
#include <vector>

using namespace std::chrono;
using namespace std;

vector <int> algoritm_forda_belmana(vector <vector<int>>& a)
{
	int n = a.size();
	vector <int> b(n);
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

	for (int i = 0; i < n; i++)
	{
		b[i] = f[0][i];
	}

	return b;

}