/*
ID: ryan luo
PROG: crypt1
LANG: C++
*/

#include <cstdio>
#include <cstdlib>

int N;
int digits[9] = {0};

int comp(const void *a,const void *b)
{
	return *(int*)a - *(int*)b;
}

char check(int result, int size)
{
	int i;
	int temp;
	int base = (size == 3) ? 100 : 1000;
	for (i = 0; i != size; ++i)
	{
		temp = result / base;
		if(bsearch(&temp, digits + (9 - N), N, sizeof(int), comp) == NULL)
			return 0;
		result = result % base;
		base /= 10;
	}
	return 1;
}

char isPrime(int ia, int ja, int ka, int ib, int jb)
{
	int A   = digits[ia] * 100 + digits[ja] * 10 + digits[ka];
	int B1  = digits[jb];
	int B10 = digits[ib];
	if (A * B1 >= 1000 || A * B10 >= 1000)
		return 0;
	if (!check(A*B1, 3) || !check(A*B10, 3) || !check(A*(B1+B10*10), 4))
		return 0;
	return 1;
}

int main()
{
	FILE *fin  = fopen("crypt1.in" , "r");
	FILE *fout = fopen("crypt1.out", "w");


	
	fscanf(fin, "%d", &N);
	
	int i;
	for (i = 0; i != N; ++i)
		fscanf(fin, "%d", &digits[i]);
	qsort(digits, 9, sizeof(int), comp);
	
	int num = 0;
	int ia, ja, ka, ib, jb;
	for (ia = 9 - N; ia != 9; ++ia)
	{
		for (ja = 9 - N; ja != 9; ++ja)
		{
			for (ka = 9 - N; ka != 9; ++ka)
			{
				for (ib = 9 - N; ib != 9; ++ib)
				{
					for (jb = 9 - N; jb != 9; ++jb)
					{
						if (isPrime(ia, ja, ka, ib, jb))
						{
							++num;
						}
					}
				}
			}
		}
	}
	
	fprintf(fout, "%d\n", num);
	
    fclose(fin);
	fclose(fout);
	return 0;
}
