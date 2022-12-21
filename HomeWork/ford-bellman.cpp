#include <iostream>
#include <vector>
#include "utility.h"

using namespace std;



vector <vector<int>> algoritm_forda_belmana(vector <vector<int>>& a)
{
	int n = a.size();
	const int INF = 1e9;
	vector <vector<int> > Mas_rast(n, vector<int>(10000, INF));
	Mas_rast[0][0] = 0;
	for (int k = 1; k < n; k++) {
		for (int i = 0; i < n; i++) {
			Mas_rast[k][i] = Mas_rast[k - 1][i];
			for (int j = 0; j < n; j++) {	
				if (Mas_rast[k - 1][j] + a[j][i] < Mas_rast[k][i]) {
					Mas_rast[k][i] = Mas_rast[k - 1][j] + a[j][i];
				}
			}
		}
	}
	return Mas_rast;
}
