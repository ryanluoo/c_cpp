/*
ID: ryan luo
PROG: dualpal
LANG: C++
*/

#include <cstdio>
#include <cmath>
#include <cstring>

char digit[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

char ChangeBase(int value, int base)
{
	char numOnBase[15], numOnBaseR[15];
	int remainder = value % base;
	int quotient  = value / base;
	int i = 0;
	while (quotient >= base)
	{
		numOnBase[i] = digit[remainder];
		++i;
		remainder = quotient % base;
		quotient  = quotient / base;
	}
	numOnBase[i]   = digit[remainder];
	numOnBase[++i] = digit[quotient];
	
	while (numOnBase[i] == '0' && i > 0)
		--i;
	numOnBase[++i] = '\0';
	int j = 0;
	for (j = 0; j != i; ++j)
		numOnBaseR[j] = numOnBase[i-1-j];
	numOnBaseR[j] = '\0';

	if (!strcmp(numOnBase, numOnBaseR))
		return 1;
	return 0;
}

int main()
{
	FILE *fin  = fopen("dualpal.in" , "r");
	FILE *fout = fopen("dualpal.out", "w");
	int N, S;
	fscanf(fin, "%d %d", &N, &S);
	++S;
	int i = 0;
	while (i != N)
	{
		int k = 0;
		int j = 0;
		for (j = 2; j <= 10; ++j)
		{
			if (ChangeBase(S, j) == 1)
				++k;
			if (k == 2)
			{
				fprintf(fout, "%d\n", S);
				++i;
				break;
			}
		}
		++S;
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
