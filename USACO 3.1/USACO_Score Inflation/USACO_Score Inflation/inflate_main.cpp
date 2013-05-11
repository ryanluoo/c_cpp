/*
ID: ryan luo
PROG: inflate
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

#define MAXN 10000

typedef struct  
{
	int points;
	int minutes;
} Category;

int cmp (const void * a, const void * b)
{
	/*double ap = ((Category*)a)->points;
	double am = ((Category*)a)->minutes;
	double bp = ((Category*)b)->points;
	double bm = ((Category*)b)->minutes;
	double x = -(ap / am - bp / bm);

	return x < 0 ? -1 : x == 0 ? 0 : 1;*/
	return ((Category*)a)->minutes - ((Category*)b)->minutes;
}

int main()
{
	ifstream fin ("inflate.in" );
	ofstream fout("inflate.out");

	int M, N;
	fin >> M >> N;
	
	Category c[MAXN];

	for (int i = 0; i != N; ++i)
	{
		fin >> c[i].points >> c[i].minutes;
	}

	qsort(c, N, sizeof(Category), cmp);

	/*for (int i = 0; i != N; ++i)
		fout << c[i].points << " " << c[i].minutes << endl;
	int max = 0;

	for (int i = 0; i != N; ++i)
	{
		int n = M / c[i].minutes;
		max += (n * c[i].points);
		M -= (n * c[i].minutes);
	}*/

	int rec[MAXN+1];
	fill(rec, rec + MAXN + 1, 0);

	for (int i = c[0].minutes; i != M + 1; ++i)
	{
		for (int j = 0; j != N; ++j)
		{
			if (i < c[j].minutes)
				break;
			rec[i] = rec[i] > (rec[i-c[j].minutes] + c[j].points) ? rec[i] : (rec[i-c[j].minutes] + c[j].points);
		}
	}
	
	fout << rec[M] << endl;

	fin.close();
	fout.close();
	return 0;
}
