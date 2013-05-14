/*
ID: ryan luo
PROG: butter
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstring>
#include <climits>
#include <list>
using namespace std;

#define MAXN 500
#define MAXC 1450
#define MAXP 800

int cow[MAXN] = {0};
int path[MAXP][MAXP];
int d = 0;

int main()
{
	ifstream fin ("butter.in" );
	ofstream fout("butter.out");
	
	for (int i = 0; i != MAXP; ++i)
	{
		fill(path[i], path[i] + MAXP, INT_MAX);
		path[i][i] = 0;
	}

	int N, P, C;
	fin >> N >> P >> C;
	for (int i = 0; i != N; ++i)
	{
		fin >> cow[i];
		--cow[i];
	}
	for (int i = 0; i != C; ++i)
	{
		int p1, p2;
		fin >> p1 >> p2;
		fin >> path[p1 - 1][p2 - 1];
		path[p2 - 1][p1 - 1] = path[p1 - 1][p2 - 1];
	}
	
	for (int i = 0; i != N; ++i)
	{
		int start = cow[i];
		list<int> rec;
		int m = INT_MAX;
		for (int j = 0; j != P; ++j)
		{
			if (j != start)
			{
				if (path[start][j] < m)
				{
					m = path[start][j];
					rec.push_front(j);
				}
				else
					rec.push_back(j);				
			}
		}

		int d = 1;
		list<int>::iterator minlit;
		while (d < P)
		{			
			int n = *rec.begin();
			rec.pop_front();
			
			int m = INT_MAX; 
			for (list<int>::iterator lit = rec.begin(); lit != rec.end(); ++lit)
			{
				if (path[n][*lit] < INT_MAX)
				{
					int ndist = path[n][*lit] + path[start][n];
					if (ndist < path[start][*lit])
						path[start][*lit] = ndist;					
				}
				if (path[start][*lit] < m)
				{
					m = path[start][*lit];
					minlit = lit;
				}
			}
			if (!rec.empty())
			{
				n = *minlit;
				rec.erase(minlit);
				rec.push_front(n);
			}
			++d;
		}		
	}

	int m = INT_MAX;
	for (int ii = 0; ii != P; ++ii)
	{
		int s = 0;
		for (int j = 0; j != N; ++j)
			s += path[cow[j]][ii];
		m = m < s ? m : s;
	}
	fout << m << endl;

	fin.close();
	fout.close();
	return 0;
}
