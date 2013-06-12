/*
ID: ryan luo
PROG: rockers
LANG: C++
*/

#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

int N, T, M;
char songs[20];
char s[20];

int Check (int n)
{
	int fit = 0;
	int remt = T, m = M;
	for (int i = 0; i != N; ++i)
	{
		if (n & (1 << i))
		{
			if (m == 0)
				return fit;
			
			if (songs[i] <= remt)
			{
				++fit;
				remt -= songs[i];
			}
			else
			{
				--m;				
				--i;
				remt = T;
			}
		}
	}
	return fit;
}

int main()
{
	ifstream fin ("rockers.in" );
	ofstream fout("rockers.out");

	fin >> N >> T >> M;
	for (int i = 0; i != N; ++i)
	{
		int t;
		fin >> t;
		songs[i] = t;
	}

	int maxfit = 0;
	for (int i = (1 << N) - 1; i > 0; --i)
	{
		int fit = Check(i);
		if (maxfit < fit)
			maxfit = fit;
	}

	fout << maxfit << endl;

	fin.close();
	fout.close();
	return 0;
}
