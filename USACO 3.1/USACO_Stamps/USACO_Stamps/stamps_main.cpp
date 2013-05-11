/*
ID: ryan luo
PROG: stamps
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstring>
#include <climits>
using namespace std;

#define MAXK 200
#define MAXN 50
#define MAXV 10000

int stamps[MAXN];
unsigned char dp[MAXV * MAXK];

unsigned char Min(unsigned char a, unsigned char b)
{
	return a < b ? a : b;
}

int main()
{
	ifstream fin ("stamps.in" );
	ofstream fout("stamps.out");
	
	memset(dp, UCHAR_MAX, MAXV * MAXK);

	int K, N;
	fin >> K >> N;
	for (int i = 0; i != N; ++i)
	{
		int temp;
		fin >> temp;
		stamps[i] = temp;
		dp[temp] = 1;
	}
	sort(stamps, stamps + N);

	int index = 1;
	while (dp[index])
	{
		++index;
		if (dp[index] == 1)
			continue;
		for (int i = 0; i != N; ++i)
		{
			if (index < stamps[i])
				break;
			dp[index] = Min(dp[index], dp[index - stamps[i]] + 1);
		}
		if (dp[index] > K)
			dp[index] = 0;
	}

	fout << index - 1 << endl;
	fin.close();
	fout.close();
	return 0;
}
