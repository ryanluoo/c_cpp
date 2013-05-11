/*
ID: ryan luo
PROG: kimbits
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAXN 31

unsigned int com[MAXN+1][MAXN+1];
unsigned int sum[MAXN+1][MAXN+1];
int main()
{
	ifstream fin ("kimbits.in" );
	ofstream fout("kimbits.out");

	unsigned int N, L, I;
	fin >> N >> L >> I;

	//Initialization
	for (int i = 0; i != MAXN + 1; ++i)
	{
		memset(com[i], 0, sizeof(unsigned int) * (MAXN + 1));
		memset(sum[i], 0, sizeof(unsigned int) * (MAXN + 1));
	}
	//Çó×éºÏ
	for (int i = 0; i != MAXN + 1; ++i)
	{
		for (int j = 0; j != MAXN + 1; ++j)
		{
			if (j > i)
				com[i][j] = 0;
			if (j == 0 || j == i)
				com[i][j] = 1;
			else
				com[i][j] = com[i - 1][j] + com[i - 1][j - 1];
		}
	}
	for (int i = 0; i != MAXN + 1; ++i)
	{
		for (int j = 0; j != MAXN + 1; ++j)
		{
			for (int k = j; k >= 0; --k)
			{
				sum[i][j] += com[i][k];
			}
		}
	}

	unsigned int result = 0;
	--I;
	for (int i = N - 1; i >= 0; --i)
	{
		unsigned int rem = I / sum[i][L];
		if (rem != 0)
		{
			result |= (1 << i);			
			I -= sum[i][L];
			--L;
		}
	}
	
	for (int i = N - 1; i >= 0; --i)
		fout << (result & (1 << i) ? "1" : "0");
	fout << endl;
	
	fin.close();
	fout.close();
	return 0;
}
