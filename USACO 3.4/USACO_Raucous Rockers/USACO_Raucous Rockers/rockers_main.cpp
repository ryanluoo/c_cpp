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
int cmp (const void* a, const void* b)
{
	return *(char*)a - *(char*)b;
}

bool Check(int n)
{
	int start = 0, end = n - 1;
	for (int m = 0; m != M; ++m)
	{
		if (start > end)
			break;

		int remt = T;
		while (remt > 0 && end >= start)
		{
			if (s[end] <= remt)
				remt -= s[end--];
			else
				break;
		}

		while (remt > 0 && end >= start)
		{
			if (s[start] <= remt)
				remt -= s[start++];
			else
				break;
		}
	}
	if (start <= end)
		return false;
	else
		return true;
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

	int maxfit = N;
	while (maxfit > 0)
	{
		char flag = 0;
		for (int i = 0; i + maxfit <= N; ++i)
		{
			memcpy(s, songs + i, maxfit);
			qsort(s, maxfit, sizeof(char), cmp);
			if (Check(maxfit))
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
			--maxfit;
		else
			break;
	}
	fout << maxfit << endl;

	fin.close();
	fout.close();
	return 0;
}
