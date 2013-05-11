/*
ID: ryan luo
PROG: nocows
LANG: C++
*/
//´ËÌâbug£¬ÕæÀ¬»ø
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

#define NODEMAX    200
#define HEIGHTMAX  100
#define MODULO    9901
ifstream fin ("nocows.in" );
ofstream fout("nocows.out");
unsigned int pedigree[NODEMAX+1][HEIGHTMAX+1] = {0};

unsigned long long FindPed(int n, int h)
{
	if (n % 2 == 0)
		return 0;

	pedigree[1][1] = 1;

	for (int k = 3; k <= n; k += 2)
		for (int m = 1; m <= h && m < k; ++m)
		{
			if (k > pow(2, (double)m) - 1)
			{
				pedigree[k][m] = 0;
				continue;
			}
			if (k == pow(2, (double)m) - 1)
			{
				pedigree[k][m] = 1;
				continue;
			}

			unsigned int total = 0;
			for (int i = 1; i < k; i += 2)
			{	
				unsigned long long right = 0;
				if (pedigree[i][m-1] != 0)
				{
					for (int j = 1; j < m - 1; ++j)
						right += pedigree[k-1-i][j];
				}
				total = total + (pedigree[i][m-1] * right);
			}

			unsigned long long mm = 0;
			for (int i = 1; i < k; i += 2)
			{
				if (pedigree[i][m-1] != 0 && pedigree[k-1-i][m-1] != 0)
					mm += pedigree[i][m-1] * pedigree[k-1-i][m-1];
			}
			
			pedigree[k][m] =  (2 * total + mm) % MODULO;
			//int i = 0;
		}
	
		/*for (int i = 0; i <= n; ++i)
			for (int j = 0; j <= h; ++j)
			{
				if (pedigree[i][j] != 0)
					fout << i << "," << j << "	" << pedigree[i][j] << endl;  
			}*/

	return pedigree[n][h];
}

int main()
{	
	ifstream fin ("nocows.in" );
	ofstream fout("nocows.out");
	
	int N, K;
	fin >> N >> K;

	fout << FindPed(N, K) << endl;
	
	fin.close();
	fout.close();
	return 0;
}
