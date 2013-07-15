/*
ID: ryan luo
PROG: fence6
LANG: C++
*/

#include <fstream>
#include <cstring>
using namespace std;

#define MAXN 100

struct LINE
{
	int ID ;
	int len;
	int N1, N2;
	int pid1, pid2;
	int join1[8];
	int join2[8];
};

int N;
int i, j, k;
LINE lines[MAXN];
int dist[MAXN][MAXN] = {0};
int pred[MAXN][MAXN] = {0};

int main()
{
	ifstream fin ("fence6.in" );
	ofstream fout("fence6.out");
	
	fin >> N;
	for (i = 0; i != N; ++i)
	{
		fin >> lines[i].ID >> lines[i].len;
		fin >> lines[i].N1 >> lines[i].N2;
		for (j = 0; j != lines[i].N1; ++j)
			fin >> lines[i].join1[j];
		for (j = 0; j != lines[i].N2; ++j)
			fin >> lines[i].join2[j];
		lines[i].pid1 = lines[i].pid2 = -1;
	}
	
	int pid = 0;
	for (i = 0; i != N; ++i)
	{
		if (lines[i].pid1 == -1)
		{
			lines[i].pid1 = pid;
			++pid;
			for (j = 0; j != lines[i].N1; ++j)
			{
				int conn = lines[i].join1[j] - 1;
				if (lines[conn].pid1 == -1)
					lines[conn].pid1 = lines[i].pid1;
				else
					lines[conn].pid2 = lines[i].pid1;
			}
		}
	
		if (lines[i].pid2 == -1)
		{
			lines[i].pid2 = pid;
			++pid;
			for (j = 0; j != lines[i].N2; ++j)
			{
				int conn = lines[i].join2[j] - 1;
				if (lines[conn].pid1 == -1)
					lines[conn].pid1 = lines[i].pid2;
				else
					lines[conn].pid2 = lines[i].pid2;
			}
		}
	}

	//initial
	for (i = 0; i != pid; ++i)
	{
		for (j = 0; j != pid; ++j)
		{
			if (i == j)
				dist[i][j] = pred[i][j] = 0;
			else
				dist[i][j] = pred[i][j] = 0x7fffffff;

		}
	}


	for (i = 0; i != N; ++i)
	{
		dist[lines[i].pid1][lines[i].pid2] = lines[i].len;
		dist[lines[i].pid2][lines[i].pid1] = lines[i].len;
	}

	for (i = 0; i != pid; ++i)
	{
		for (j = 0; j != pid; ++j)
		{
			for (k = 0; k != pid; ++k)
			{
				if (dist[i][k] != 0x7fffffff && dist[k][j] != 0x7fffffff && (
				    dist[i][j] == 0x7fffffff || dist[i][j] >= dist[i][k] + dist[k][j]))
				{
					if (dist[i][j] > dist[i][k] + dist[k][j])
						pred[i][j] = dist[i][j];
					dist[i][j] = dist[i][k] + dist[k][j];
				}
				else if (dist[i][k] != 0x7fffffff && dist[k][j] != 0x7fffffff && ((pred[i][j] == 0x7fffffff || dist[i][k] + dist[k][j] < pred[i][j])))
				{
					pred[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}
	}
	
	int minloop = 0x7fffffff;
	for (i = 0; i != pid; ++i)
	{
		for (j = 0; j != pid; ++j)
		{
			if (pred[i][j] != 0x7fffffff && dist[i][j] != 0x7fffffff && pred[i][j] != dist[i][j])
			{
				if (minloop > pred[i][j] + dist[i][j])
					minloop = pred[i][j] + dist[i][j];
			}
		}
	}

	fout << minloop << endl;

	fin.close();
	fout.close();
	return 0;
}
