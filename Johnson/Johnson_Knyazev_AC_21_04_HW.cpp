#include "utility.h"

using namespace std;

int main()
{
	while (1)
	{
		Help();

		switch (Checker(0, 4))
		{

		case 0:
		{
			return(0);
		}
		case 1:
		{
			CreateDefaultGraph();
			break;
		}
		case 2:
		{
			CreateRandomGraphs();
			break;
		}

		case 3:
		{
			CreateGraphsByHand();
			break;
		}

		case 4:
		{
			FindAPSPwithJA();
			break;
		}

		default:
		{
			break;
		}

		}
	}
}
