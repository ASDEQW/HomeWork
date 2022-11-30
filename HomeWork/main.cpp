#include <iostream>
#include <chrono>
#include <vector>
#include "Header.h"
#include "utility.h"

using namespace std::chrono;
using namespace std;


int main()
{
	int method_number;
	setlocale(LC_ALL, "Russian");

	int N[3] = { 5, 10, 100 };
	
	while (1)
	{
		menu();

		cin >> method_number;
		for (int n : N)
		{
			Run(method_number, n);
		}
	}
}