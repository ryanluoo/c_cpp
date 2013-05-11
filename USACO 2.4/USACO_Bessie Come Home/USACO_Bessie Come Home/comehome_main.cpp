/*
ID: ryan luo
PROG: comehome
LANG: C++
*/

#include <fstream>
#include <cctype>
#include <algorithm>
#include <climits>
#include <queue>
#include <map>
using namespace std;

int GetGraphIndex(char c)
{
	if (islower(c))
		return c - 'a';
	if (isupper(c))
		return c - 'A' + 26;
	return -1;
}

int main()
{
	ifstream fin ("comehome.in" );
	ofstream fout("comehome.out");

	int P;
	fin >> P;

	int  graph[52][52];
	for (int i = 0; i != 52; ++i)
	{
		fill(graph[i], graph[i] + 52, -1);
		graph[i][i] = 0;
	}
	
	for (int i = 0; i != P; ++i)
	{
		char v1, v2;
		int  w;
		fin >> v1 >> v2 >> w;
		w = graph[GetGraphIndex(v1)][GetGraphIndex(v2)] != -1 && w > graph[GetGraphIndex(v1)][GetGraphIndex(v2)] ? graph[GetGraphIndex(v1)][GetGraphIndex(v2)] : w;
		graph[GetGraphIndex(v1)][GetGraphIndex(v2)] = w;
		graph[GetGraphIndex(v2)][GetGraphIndex(v1)] = w;
	}
	
	//floyd
	for (int k = 0; k != 52; ++k)
	{
		for (int i = 0; i != 52; ++i)
		{
			for (int j = 0; j != 52; ++j)
			{
				if (graph[i][k] != -1 && graph[k][j] != -1 && (graph[i][j] == -1 || graph[i][j] > graph[i][k] + graph[k][j]))
					graph[i][j] = graph[i][k] + graph[k][j];
			}
		}
	}

	int max = INT_MAX; char c;
	for (int i = 26; i != 51; ++i)
	{
		if (graph[i][GetGraphIndex('Z')] != -1 && graph[i][GetGraphIndex('Z')] < max)
		{
			max = graph[i][GetGraphIndex('Z')];
			c = i - 26 + 'A';
		}
	}
	fout << c << " " << max << endl;
	fin.close();
	fout.close();
	return 0;
}
