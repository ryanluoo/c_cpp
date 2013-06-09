/*
ID: ryan luo
PROG: fence9
LANG: C++
*/

#include <fstream>
#include <cstring>
using namespace std;

#define MAXNM 32000

double N, M, P;
int main()
{
	ifstream fin ("fence9.in" );
	ofstream fout("fence9.out");
	fin >> N >> M >> P;

	int omn = 0;
	int pONl = 0;
	for (int i = 1; i < N; ++i)
	{
		double y = M / N * i;
		int yi = y;
		if (y == (double)yi)
			++pONl;
	}

	omn = N == 0 ? 0 : ((N - 1) * (M - 1) - pONl) / 2;

	pONl = 0;
	int pmn = 0;
	if (P == N)
		fout << omn << endl;
	else if (P > N)
	{
		for (int i = N + 1; i < P; ++i)
		{
			double y = (P - i) * M / (P - N);
			int yi = y;
			if (y == (double)yi)
				++pONl;
		}
		pmn = ((P - N - 1) * (M - 1) - pONl) / 2;
		int c = N == 0 ? 0 : M - 1;
		fout << pmn + omn + c << endl;
	}
	else
	{
		for (int i = P + 1; i < N; ++i)
		{
			double y = (i - P) * M / (N - P);
			int yi = y;
			if (y == (double)yi)
				++pONl;
		}
		pmn = ((N - P - 1) * (M - 1) - pONl) / 2;
		fout << omn - pONl - pmn << endl;
	}

	fin.close();
	fout.close();
	return 0;
}
