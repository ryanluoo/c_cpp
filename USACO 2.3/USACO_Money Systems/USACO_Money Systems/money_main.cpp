/*
ID: ryan luo
PROG: money
LANG: C++
*/

#include <fstream>
#include <climits>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAXV 25
#define MAXN 10000

int cmp(const void * a, const void * b)
{
	return *(int*)a - *(int*)b;
}

int coins[MAXV];
int V, N;
unsigned long long rec[MAXN+1][MAXV] = {0};

unsigned long long FindWay (int n)
{
	for (int i = 1; i <= n; ++i)
	{
		int r = i % coins[0];
		if (r != 0)
			rec[i][0] = 0;
		else
			rec[i][0] = 1;
	}

	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j != V; ++j)
		{
			if (coins[j] > i)
				rec[i][j] = rec[i][j-1];
			else if (coins[j] == i)
				rec[i][j] = rec[i][j-1] + 1;
			else
				rec[i][j] += rec[i-coins[j]][j] + rec[i][j-1];
		}
	}

	return rec[n][V-1];
}

int main()
{
	ifstream fin ("money.in" );
	ofstream fout("money.out");

	fin >> V >> N;
	for (int i = 0; i != V; ++i)
		fin >> coins[i];

	qsort(coins, V, sizeof(int), cmp);

	fout << FindWay(N) << endl;

	fin.close();
	fout.close();
	return 0;
}
