/*
ID: ryan luo
PROG: camelot
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <map>
#include <list>
#include <cmath>
#include <climits>
using namespace std;

/*
knight (x, y):
(x-1, y+2), (x+1, y+2)
(x-2, y+1), (x+2, y+1)
(x-2, y-1), (x+2, y-1)
(x-1, y-2), (x+1, y-2)
*/
#define Row R
#define Col C
int R, C;
char kingx, kingy;
//list<char> knightx, knighty;
char knightx[780];
char knighty[780];
int knightn = 0;
int dist[26][30][26][30] = {0};

int main()
{
	ifstream fin ("camelot.in" );
	ofstream fout("camelot.out");

	fin >> R >> C;

	//init
	for (int i = 0; i != Col; ++i)
		for (int j = 0; j != Row; ++j)
			for (int x = 0; x != Col; ++x)
				for (int y = 0; y != Row; ++y)
				{
					if (i == x && j == y)
						dist[i][j][x][y] = 0;
					else
						dist[i][j][x][y] = -1;
				}


	for (int i = 0; i != Col; ++i)
	{
		for (int j = 0; j != Row; ++j)
		{
			int visited[26][30] = {0};
			list< pair<int, int> > q;
			q.push_back(make_pair(i, j));
			while (!q.empty())
			{
				int x = q.front().first;
				int y = q.front().second;
				q.pop_front();

				if (x - 1 >= 0 && y + 2 < Row)
				{
					if (!visited[x - 1][y + 2])
						q.push_back(make_pair(x - 1, y + 2));
					visited[x - 1][y + 2] = 1;
					if (dist[i][j][x - 1][y + 2] == -1 || dist[i][j][x - 1][y + 2] > dist[i][j][x][y] + 1)
						dist[i][j][x - 1][y + 2] = dist[i][j][x][y] + 1;
				}
				if (x - 2 >= 0 && y + 1 < Row)
				{
					if (!visited[x - 2][y + 1])
						q.push_back(make_pair(x - 2, y + 1));
					visited[x - 2][y + 1] = 1;
					if (dist[i][j][x - 2][y + 1] == -1 || dist[i][j][x - 2][y + 1] > dist[i][j][x][y] + 1)
						dist[i][j][x - 2][y + 1] = dist[i][j][x][y] + 1;
				}
				if (x - 2 >= 0 && y - 1 >= 0)
				{
					if (!visited[x - 2][y - 1])
						q.push_back(make_pair(x - 2, y - 1));
					visited[x - 2][y - 1] = 1;
					if (dist[i][j][x - 2][y - 1] == -1 || dist[i][j][x - 2][y - 1] > dist[i][j][x][y] + 1)
						dist[i][j][x - 2][y - 1] = dist[i][j][x][y] + 1;
				}
				if (x - 1 >= 0 && y - 2 >= 0)
				{
					if (!visited[x - 1][y - 2])
						q.push_back(make_pair(x - 1, y - 2));
					visited[x - 1][y - 2] = 1;
					if (dist[i][j][x - 1][y - 2] == -1 || dist[i][j][x - 1][y - 2] > dist[i][j][x][y] + 1)
						dist[i][j][x - 1][y - 2] = dist[i][j][x][y] + 1;
				}

				if (x + 1 < Col && y + 2 < Row)
				{
					if (!visited[x + 1][y + 2])
						q.push_back(make_pair(x + 1, y + 2));
					visited[x + 1][y + 2] = 1;
					if (dist[i][j][x + 1][y + 2] == -1 || dist[i][j][x + 1][y + 2] > dist[i][j][x][y] + 1)
						dist[i][j][x + 1][y + 2] = dist[i][j][x][y] + 1;
				}
				if (x + 2 < Col && y + 1 < Row)
				{
					if (!visited[x + 2][y + 1])
						q.push_back(make_pair(x + 2, y + 1));
					visited[x + 2][y + 1] = 1;
					if (dist[i][j][x + 2][y + 1] == -1 || dist[i][j][x + 2][y + 1] > dist[i][j][x][y] + 1)
						dist[i][j][x + 2][y + 1] = dist[i][j][x][y] + 1;
				}
				if (x + 2 < Col && y - 1 >= 0)
				{
					if (!visited[x + 2][y - 1])
						q.push_back(make_pair(x + 2, y - 1));
					visited[x + 2][y - 1] = 1;
					if (dist[i][j][x + 2][y - 1] == -1 || dist[i][j][x + 2][y - 1] > dist[i][j][x][y] + 1)
						dist[i][j][x + 2][y - 1] = dist[i][j][x][y] + 1;
				}
				if (x + 1 < Col && y - 2 >= 0)
				{
					if (!visited[x + 1][y - 2])
						q.push_back(make_pair(x + 1, y - 2));
					visited[x + 1][y - 2] = 1;
					if (dist[i][j][x + 1][y - 2] == -1 || dist[i][j][x + 1][y - 2] > dist[i][j][x][y] + 1)
						dist[i][j][x + 1][y - 2] = dist[i][j][x][y] + 1;
				}
			}
		}		
	}

	char x;
	int  y;
	fin >> x >> y;
	kingx = x - 'A'; kingy = y - 1;
	while (fin >> x >> y)
	{
		knightx[knightn] = x - 'A';
		knighty[knightn] = y - 1;
		++knightn;
	}

	// gathering point : (x, y)
	int minmoves = INT_MAX;
	for (x = 0; x != C; ++x)
	{
		for (y = 0; y != R; ++y)
		{
			int moves = 0;
			int flag = 0;
			for (int n = 0; n != knightn; ++n)
			{
				//Can't reach
				if (dist[x][y][knightx[n]][knighty[n]] < 0)
				{
					flag = 1;
					break;
				}
				moves += dist[x][y][knightx[n]][knighty[n]];
			}

			if (flag || moves >= minmoves)
				continue;

			//picking point : (px, py)
			char px, py;
			for (px = 0; px != C; ++px)
			{
				for (py = 0; py != R; ++py)
				{					
					for (int n = 0; n != knightn; ++n)
					{
						int nmove = moves;
						//Can't reach
						if (dist[x][y][knightx[n]][knighty[n]] < 0   ||
							dist[x][y][px][py] < 0                   ||
							dist[px][py][knightx[n]][knighty[n]] < 0)
						{
							break;
						}
						nmove -= dist[x][y][knightx[n]][knighty[n]];
						int absx = abs(kingx-px);
						int absy = abs(kingy-py);
						int xy = absx < absy ? absx : absy;
						nmove += dist[x][y][px][py] + absx + absy - xy + dist[px][py][knightx[n]][knighty[n]];
						if (nmove < minmoves)
							minmoves = nmove;
					}
				}
			}
		}
	}

	minmoves = minmoves == INT_MAX ? 0 : minmoves;	
	fout << minmoves << endl;

	fin.close();
	fout.close();
	return 0;
}
