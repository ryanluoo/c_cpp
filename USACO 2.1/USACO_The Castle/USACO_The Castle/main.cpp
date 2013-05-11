/*
ID: ryan luo
PROG: castle
LANG: C++
*/

#include <cstdio>
#include <queue>
#include <map>
using namespace std;

int main()
{
	FILE *fin  = fopen("castle.in" , "r");
	FILE *fout = fopen("castle.out", "w");
	int M, N;
	fscanf(fin, "%d %d", &M, &N);

	unsigned char   castle[50][50] = {0};
	int castSize[50][50] = {0};
	int   castId[50][50] = {0};


	int i, j;
	for (i = 0; i != N; ++i)
		for (j = 0; j != M; ++j)
			fscanf(fin, "%d", &castle[i][j]);

	//BFS
	int num = 0, sizel = 0;
	unsigned char mask7_4 = 240; // 11110000
	
	for (i = 0; i != N; ++i)
		for (j = 0; j != M; ++j)
		{
			if ((castle[i][j] & mask7_4) != 0)
				continue;
			
			queue< pair<int, int> > bfsQueue;
			queue< pair<int, int> > storage;

			bfsQueue.push(make_pair(i, j));
			castle[i][j] += 16;

			int size = 0;
			while (!bfsQueue.empty())
			{
				pair<int, int> p = bfsQueue.front();
				storage.push(p);
				bfsQueue.pop();

				++size;
				unsigned char walls = castle[p.first][p.second];
							
				if ((walls & 1) == 0 && p.second != 0)
				{
					if ((castle[p.first][p.second - 1] & mask7_4) == 0)
					{
						bfsQueue.push(make_pair(p.first, p.second - 1));	
						castle[p.first][p.second - 1] += 16;
					}
				}
				if ((walls & 2) == 0 && p.first != 0)
				{
					if ((castle[p.first - 1][p.second] & mask7_4) == 0)
					{
						bfsQueue.push(make_pair(p.first - 1, p.second));
						castle[p.first - 1][p.second] += 16;
					}
				}
				if ((walls & 4) == 0 && p.second != M)
				{
					if ((castle[p.first][p.second + 1] & mask7_4) == 0)
					{
						bfsQueue.push(make_pair(p.first, p.second + 1));
						castle[p.first][p.second + 1] += 16;
					}
				}
				if ((walls & 8) == 0 && p.first != N)
				{
					if ((castle[p.first + 1][p.second] & mask7_4) == 0)
					{
						bfsQueue.push(make_pair(p.first + 1, p.second));
						castle[p.first+1][p.second] += 16;
					}
				}
			}
			++num;
			sizel = size > sizel ? size : sizel;

			while (!storage.empty())
			{
				pair<int, int> p = storage.front();
				castId[p.first][p.second] = num;
				castSize[p.first][p.second] = size;
				storage.pop();
			}
		}

	

	unsigned int mi = 0, mj = 0, msize = 0;
	char w = ' ';
	for (i = 0; i != N; ++i)
		for (j = 0; j != M; ++j)
		{
			if (i != 0)
			{
				if(castId[i][j] != castId[i-1][j])
				{
					if (castSize[i][j] + castSize[i-1][j] > msize)
					{
						mi = i;
						mj = j;
						w  = 'N';
						msize = castSize[i][j] + castSize[i-1][j];
					}
					else if (castSize[i][j] + castSize[i-1][j] == msize)
					{
						if (j > mj || i < mi)
						{
						}
						else if (j == mj && i == mi){}
						else
						{
							mi = i;
							mj = j;
							w  = 'N';
							msize = castSize[i][j] + castSize[i-1][j];
						}						
					}
				}
			}

			if (j != M - 1)
			{
				if(castId[i][j] != castId[i][j+1])
				{
					if (castSize[i][j] + castSize[i][j+1] > msize)
					{
						mi = i;
						mj = j;
						w  = 'E';
						msize = castSize[i][j] + castSize[i][j+1];
					}
					else if (castSize[i][j] + castSize[i][j+1] == msize)
					{
						if (j > mj || i < mi)
						{
						}
						else if (j == mj && i == mi){}
						else
						{
							mi = i;
							mj = j;
							w  = 'E';
							msize = castSize[i][j] + castSize[i][j+1];
						}
					}						
				}
			}
		}

	fprintf(fout, "%d\n%d\n%d\n%d %d %c\n", num, sizel, msize, mi+1, mj+1, w);
	fclose(fin);
	fclose(fout);
	return 0;
}
