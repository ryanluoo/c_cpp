/*
ID: ryan luo
PROG: fact4
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXN 4220
int f[MAXN+1];

int main()
{
	ifstream fin ("fact4.in" );
	ofstream fout("fact4.out");

	int N;
	fin >> N;
	
	f[1] = 1;
	for (int i = 2; i <= N; ++i)
	{
		int t = f[i - 1] * i;
		div_t d = div(t, 10);
		while (d.rem == 0)
			d = div(d.quot, 10);
		f[i] = d.rem;
		d = div(d.quot, 10);
		f[i] += d.rem * 10;
		d = div(d.quot, 10);
		f[i] += d.rem * 100;
		d = div(d.quot, 10);
		f[i] += d.rem * 1000;
	}
	fout << f[N] % 10 << endl;

	fin.close();
	fout.close();
	return 0;
}
