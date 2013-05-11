/*
ID: ryan luo
PROG: cowtour
LANG: C++
*/

#include <fstream>
#include <map>
#include <cmath>
#include <climits>
#include <iomanip>
using namespace std;

typedef struct 
{
	unsigned short x; 
	unsigned short y;
	bool belong;
} Coord;

int main()
{
	ifstream fin ("cowtour.in" );
	ofstream fout("cowtour.out");
	
	int N;
	fin >> N;

	Coord  grid[150];
	bool   adjacency[150][150];
	double path[150][150];

	for (int i = 0; i != N; ++i)
		fin >> grid[i].x >> grid[i].y;
	
	fin.get();
	char *buf = new char[N+1];
	for (int i = 0; i != N; ++i)
	{
		fin.getline(buf, N+1);
		for (int j = 0; j != N; ++j)
		{
			adjacency[i][j] = buf[j] - '0';
			if (buf[j] - '0')
			{
				path[i][j] = sqrt(pow((double)(grid[i].x - grid[j].x), 2) + 
								  pow((double)(grid[i].y - grid[j].y), 2));
			}
			else
				path[i][j] = -1;
		}
		path[i][i] = 0;
	}
	delete [] buf;
	
	//DFS
	
	//floyd
	for (int k = 0; k != N; ++k)
	{
		for (int i = 0; i != N; ++i)
		{
			for (int j = 0; j != N; ++j)
			{
				if (path[i][k] != -1 && path[k][j] != -1 && (path[i][j] == -1 || path[i][j] > path[i][k] + path[k][j]))
					path[i][j] = path[i][k] + path[k][j];
			}
		}
	}

	double maxpath = 0;
	for (int i = 0; i != N; ++i)
		for (int j = i + 1; j != N; ++j)
		{
			maxpath = maxpath > path[i][j] ? maxpath : path[i][j];
		}

	double minpath = -1;
	for (int i = 0; i != N; ++i)
		for (int j = i + 1; j != N; ++j)
		{
			if (path[i][j] == -1)
			{
				double ij = sqrt(pow((double)(grid[i].x - grid[j].x), 2) + pow((double)(grid[i].y - grid[j].y), 2));
				double maxi = 0, maxj = 0;
				for (int k = 0; k != N; ++k)
				{
					if (path[i][k] != -1)
						maxi = maxi > path[i][k] ? maxi : path[i][k];
				}
				for (int k = 0; k != N; ++k)
				{
					if (path[j][k] != -1)
						maxj = maxj > path[j][k] ? maxj : path[j][k];
				}
				double newpath = ij + maxi + maxj;
				newpath = newpath > maxpath ? newpath : maxpath;
				minpath = (minpath == -1 || newpath < minpath) ? newpath : minpath;
			}
		}
	
	fout << fixed << setprecision(6) << minpath << endl;

	fin.close();
	fout.close();
	return 0;
}
