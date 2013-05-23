/*
ID: ryan luo
PROG: game1
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <list>
using namespace std;

#define MAXN 100

int N;
int seq[MAXN];
int sum[MAXN][MAXN]  = {0};
int best[MAXN][MAXN] = {0};

int main()
{
	ifstream fin ("game1.in" );
	ofstream fout("game1.out");

	fin >> N;
	for (int i = 0; i != N; ++i)
	{
		fin >> seq[i];
	}

	for (int i = 0; i != N; ++i)
	{
		for (int j = i; j != N; ++j)
		{
			if (i == j)
				sum[i][j] = seq[i];
			else
				sum[i][j] = sum[i][j - 1] + seq[j];
		}
	}	

	for (int len = 2; len <= N; ++len)
	{
		for (int i = 0; i <= N - len; ++i)
		{
			int j = i + len - 1;

			if (len == 2)
				best[i][j] = seq[i] > seq[j] ? seq[i] : seq[j];
			else
				best[i][j] = sum[i][j] - min(best[i][j-1], best[i+1][j]);
		}
	}
	
	fout << best[0][N-1] << " " << sum[0][N - 1] - best[0][N - 1] << endl;

	fin.close();
	fout.close();
	return 0;
}
