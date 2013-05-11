/*
ID: ryan luo
PROG: spin
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstring>
#include <list>
#include <map>
#include <vector>
using namespace std;

#define MAXS 180
#define MAXA 360
#define WNUM 5

int s[5];
int w[5];
struct wedge
{
	int start;
	int extent;
};
wedge wdg[5][WNUM];

int main()
{
	ifstream fin ("spin.in" );
	ofstream fout("spin.out");
	
	for (int i = 0; i != 5; ++i)
	{
		fin >> s[i] >> w[i];
		for (int j = 0; j != w[i]; ++j)
			fin >> wdg[i][j].start >> wdg[i][j].extent;
	}

	fin.close();
	fout.close();
	return 0;
}
