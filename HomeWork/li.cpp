#include <iostream>
#include <chrono>
#include <vector>


using namespace std;


vector <int> algoritm_li(vector <vector<bool>>& a)
{
	int n = a.size();
	vector <int> b(n);

	int k = 1;
	int count_cycle = 0;


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
			count_cycle = count_cycle + 1;
			if (count_cycle > n * n) {
				cout << "Кратчайший путь не найден" << endl;
				b = {};
				return b;
			}
		}
	}


	return b;

}