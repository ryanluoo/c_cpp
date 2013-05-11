/*
ID: ryan luo
PROG: palsquare
LANG: C++
*/

#include <cstdio>
#include <cmath>
#include <cstring>

char digit[20] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
				  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

void ChangeBase(int value, int base, char numOnBase[18], char numOnBaseR[18])
{
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
}

int main()
{
	FILE *fin  = fopen("palsquare.in" , "r");
	FILE *fout = fopen("palsquare.out", "w");

	int B;
	fscanf(fin, "%d", &B);
	
	char a[18], b[18], bb[18];

	float i = 0;
	for (i = 1; i != 301; ++i)
	{
		ChangeBase(pow(i, 2), B, a, b);
		if (!strcmp(a, b))
		{
			ChangeBase(i, B, a, bb);
			fprintf(fout, "%s %s\n", bb, b);
		}
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
