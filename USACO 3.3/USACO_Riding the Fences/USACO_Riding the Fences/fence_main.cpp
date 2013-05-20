/*
ID: ryan luo
PROG: fence
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <map>
using namespace std;

#define MAXI 500
int fence[MAXI+1][MAXI+1] = {0};
int main()
{
	ifstream fin ("fence.in" );
	ofstream fout("fence.out");

	int F;
	fin >> F;
	for (int i = 0; i != F; ++i)
	{
		int a, b;
		fin >> a >> b;
		fence[a][b] = 1;
		fence[b][a] = 1;
	}
	
	fin.close();
	fout.close();
	return 0;
}
