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
vector <int> algoritm_li(int n)
{
	vector <vector<bool>> a;
	vector <int> b(n);

	int k = 1;
	int error = 0;
	a = form_matrix(n);


	
	for (int j = 0; j < n; j++)
	{
		if (a[0][j] == 1) b[j] = k;
	}

	for (int l = 0; l < n; l++)
	{
		while (b[l] == 0)
		{
			for (int j = 0; j < n; j++)
			{
				if ((b[j] == k))
				{
					for (int i = 0; i < n; i++)
					{
						if ((a[j][i] == 1) && (b[i] == 0))
						{
							b[i] = k + 1;
						}
					}
				}
			}
			k = k + 1;
			error = error + 1;
			if (error > n * n) {
				cout << "Кратчайший путь не найден" << endl;
				b = {};
				return b;
			}
		}
	}


	return b;

}
