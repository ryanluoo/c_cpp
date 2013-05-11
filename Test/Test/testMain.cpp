/*
ID: ryan luo
PROG: prefix
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>
using namespace std;

ifstream fin ("prefix.in" );
ofstream fout("prefix.out");
int main()
{	
	int h[5];
	memset(h, 0, sizeof(int) * 5);

	for (int i = 0; i != 5; ++i)
		fout << h[i] << " ";

	fin.close();
	fout.close();
	return 0;
}
