/*
ID: ryan luo
PROG: agrinet
LANG: C++
*/

#include <fstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;

#define MAXN 100

int main()
{
	ifstream fin ("agrinet.in" );
	ofstream fout("agrinet.out");

	int N;
	fin >> N;
	int matrix[MAXN][MAXN];
	for (int i = 0; i != MAXN; ++i)
		fill(matrix[i], matrix[i] + MAXN, -1);

	istream_iterator<int> fin_it(fin);
	for (int i = 0; i != N; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			matrix[i][j] = *fin_it++;
		}
	}

	set<int> X, Y;
	int C1[MAXN];
	int C2[MAXN];
	fill(C1, C1 + MAXN, 0);
	fill(C2, C2 + MAXN, INT_MAX);

	for (int i = 1; i != N; ++i)
		Y.insert(i);
	
	int min = 0; int x = 0;
	while (!Y.empty())
	{
		int yy = INT_MAX; set<int>::iterator yi = Y.begin();
		for (set<int>::iterator i = Y.begin(); i != Y.end(); ++i)
		{
			int y = *i;
			if (matrix[y][x] != -1 && matrix[y][x] < C2[y])
			{
				C1[y] = x;
				C2[y] = matrix[x][y];
			}
		}

		for (set<int>::iterator i = Y.begin(); i != Y.end(); ++i)
		{
			if (C2[*i] < yy)
			{
				yy = C2[*i];
				yi = i;
			}
		}

		min += yy;
		C2[*yi] = INT_MAX;
		x = *yi;
		Y.erase(yi);
	}

	fout << min << endl;
	fin.close();
	fout.close();
	return 0;
}
