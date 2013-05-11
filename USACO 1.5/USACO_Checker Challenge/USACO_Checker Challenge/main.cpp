/*
ID: ryan luo
PROG: checker
LANG: C++
*/

#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;

FILE *fin  = fopen("checker.in" , "r");
FILE *fout = fopen("checker.out", "w");
int up;
int N;
int s[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int total = 0;

//  N - y + x
// 2N - y - x
int ps (int a) 
{
	switch (a)
	{
	case 1:
		return 1;
	case 2:
		return 2;
	case 4:
		return 3;
	case 8:
		return 4;
	case 16:
		return 5;
	case 32:
		return 6;
	case 64:
		return 7;
	case 128:
		return 8;
	case 256:
		return 9;
	case 512:
		return 10;
	case 1024:
		return 11;
	case 2048:
		return 12;
	case 4096:
		return 13;
	default:
		return -1;
	}
}

void searchSolution(int row, int rd, int ld, int depth)
{
	if (row != up)
	{
		int p = up & (~(row | rd | ld));
		while (p != 0)
		{
			int pos = p & ((~p) + 1);
			s[depth] = pos;
			p = p - pos;
			searchSolution(row + pos, (rd + pos) >> 1, (ld + pos) << 1, depth + 1);
		}
	}
	else
	{		
		++total;
		if (total <= 3)
		{
			for (int i = 0; i != N - 1; ++i)
			{
				fprintf(fout, "%d ", ps(s[i]));
			}
			fprintf(fout, "%d\n", ps(s[N-1]));
		}
	}
}

int main()
{
	
	fscanf(fin, "%d", &N);	
	up = (1 << N) - 1;	
	searchSolution(0, 0, 0, 0);
	fprintf(fout, "%d\n", total);

	fclose(fin);
	fclose(fout);
	return 0;
}
