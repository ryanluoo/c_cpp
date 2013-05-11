/*
ID: ryan luo
PROG: maze1
LANG: C++
*/

#include <fstream>
#include <climits>
#include <algorithm>
#include <iostream>
#include <stack>
#include <map>
#include <queue>
#include <cstring>
using namespace std;

#define WMAX  38
#define HMAX 100
#define GMAXSIZE WMAX*HMAX


char graph[HMAX][WMAX];
int dist[HMAX][WMAX];
char visted[HMAX][WMAX];
//       1
//    0     3
//       2
int main()
{
	ifstream fin ("maze1.in" );
	ofstream fout("maze1.out");

	for (int i = 0; i != HMAX; ++i)
	{
		fill(graph[i], graph[i] + WMAX, 0xff);
		fill(visted[i], visted[i] + WMAX, 0);
		fill(dist[i], dist[i] + WMAX, INT_MAX);
	}

	int W, H;
	fin >> W >> H;
	
	//Read Maze
	char *buf = new char [W * 2 + 2];	
	int exitp[2] = {0}; int exiti = 0;
	fin.get();
	for (int i = 0; i != 2 * H + 1; ++i)
	{
		fin.getline(buf, W * 2 + 2);
		if (buf[0] == ' ')
		{
			int id = ((i - 1) / 2) * W;
			exitp[++exiti %= 2] = id;
		}

		for (int j = 1; j != 2 * W; ++j)
		{			
			if (i % 2)
			{
				if (j % 2 == 0 && buf[j] == ' ')
				{
					int h = (i - 1) / 2;
					int w = j / 2 - 1;
					//graph[h * W + w][h * W + w + 1] = 1;
					graph[h][w]   = graph[h][w]   & 0xfb;
					graph[h][w+1] = graph[h][w+1] & 0xfe;
				}
			}
			else
			{
				if (i == 0)
				{
					if (j % 2 == 1 && buf[j] == ' ')
					{
						int id = (j - 1) / 2;
						exitp[++exiti %= 2] = id;
					}
				}
				else if (i == 2 * H)
				{
					if (j % 2 == 1 && buf[j] == ' ')
					{
						int id = (H - 1) * W + (j - 1) / 2;
						exitp[++exiti %= 2] = id;
					}
				}
				else
				{
					if (j % 2 == 1 && buf[j] == ' ')
					{
						int h = i / 2 - 1;
						int w = (j - 1) / 2;
						graph[h][w]   = graph[h][w]   & 0xf7;
						graph[h+1][w] = graph[h+1][w] & 0xfd;
					}
				}
			}
		}

		if (buf[2 * W] == ' ')
		{
			int id = ((i - 1) / 2) * W + W - 1;
			exitp[++exiti %= 2] = id;
		}
	}
	delete [] buf;


	//BFS
	queue< pair<int, int> > bfs;
	int x = exitp[0] / W, y = exitp[0] % W;
	bfs.push(make_pair(x, y)); dist[x][y] = 1; visted[x][y] = 1;
	x = exitp[1] / W, y = exitp[1] % W;
	if (exitp[0] != exitp[1])
	{
		bfs.push(make_pair(x, y)); dist[x][y] = 1; visted[x][y] = 1;
	}
	
	int maxl = 0;
	while (!bfs.empty())
	{
		pair<int, int> temp = bfs.front();
		char c = graph[temp.first][temp.second];
		int d = dist[temp.first][temp.second];
		if (d > maxl)
			maxl = d;
		if ((c & 0x01) == 0)
		{
			if (dist[temp.first][temp.second-1] > d + 1)
				dist[temp.first][temp.second-1] = d + 1;
			if (!visted[temp.first][temp.second-1])
			{
				bfs.push(make_pair(temp.first, temp.second - 1));
				visted[temp.first][temp.second-1] = 1;
			}
		}
		if ((c & 0x02) == 0)
		{
			if (dist[temp.first-1][temp.second] > d + 1)
				dist[temp.first-1][temp.second] = d + 1;
			if (!visted[temp.first-1][temp.second])
			{
				bfs.push(make_pair(temp.first - 1, temp.second));
				visted[temp.first-1][temp.second] = 1;
			}
		}
		if ((c & 0x04) == 0)
		{
			if (dist[temp.first][temp.second+1] > d + 1)
				dist[temp.first][temp.second+1] = d + 1;
			if (!visted[temp.first][temp.second+1])
			{
				bfs.push(make_pair(temp.first, temp.second + 1));
				visted[temp.first][temp.second+1] = 1;
			}
		}
		if ((c & 0x08) == 0)
		{
			if (dist[temp.first+1][temp.second] > d + 1)
				dist[temp.first+1][temp.second] = d + 1;
			if (!visted[temp.first+1][temp.second])
			{
				bfs.push(make_pair(temp.first + 1, temp.second));
				visted[temp.first+1][temp.second] = 1;
			}			
		}
		bfs.pop();
	}

	fout << maxl << endl;

	fin.close();
	fout.close();
	return 0;
}
