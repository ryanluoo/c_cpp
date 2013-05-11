/*
ID: ryan luo
PROG: holstein
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <bitset>
using namespace std;

#define MAXV 1000
#define MAXT 15

int vn;
int v[MAXV] = {0};
int type;
int feed[MAXT][MAXV] = {0};

size_t minimum;
unsigned long record;

bool TestConstrains(bitset<MAXT>& b)
{	
	for (size_t i = 0; i != vn; ++i)
	{
		size_t total = 0;
		for (size_t j = 0; j != type; ++j)
			total += (b[j] * feed[j][i]);
		if (total < v[i])
			return false;
	}
	return true;
}

int main()
{
	FILE *fin  = fopen("holstein.in" , "r");
	FILE *fout = fopen("holstein.out", "w");

	int i, j;

/////////// input /////////////////////////////
	fscanf(fin, "%d", &vn);	
	for (i = 0; i != vn; ++i)
		fscanf(fin, "%d", &v[i]);
	fscanf(fin, "%d", &type);
	for (i = 0; i != type; ++i)
		for (j = 0; j != vn; ++j)
			fscanf(fin, "%d", &feed[i][j]);
//////////////////////////////////////////////

	minimum = type + 1;	
	int x;
	for (x = (1 << type) - 1; x != 0; --x)
	{
		bitset<MAXT> b(x);
		size_t n = b.count();
		if (n > minimum)
			continue;

		if (TestConstrains(b))
		{
			minimum = n;
			record = b.to_ulong();
		}
	}
	
	fprintf(fout, "%u", minimum);
	bitset<MAXT> b((long)record);
	for (i = 0; i != type; ++i)
	{
		if (b.test(i))
			fprintf(fout, " %d", i + 1);
	}
	fprintf(fout, "\n");

	fclose(fin);
	fclose(fout);
	return 0;
}
