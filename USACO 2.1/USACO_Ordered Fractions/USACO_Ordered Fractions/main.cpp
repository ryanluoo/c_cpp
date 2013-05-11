/*
ID: ryan luo
PROG: frac1
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#define MAXN 160

int N;
struct fraction{unsigned char m; unsigned n;};
unsigned char frac[MAXN+1][MAXN+1] = {0};
fraction f[MAXN*MAXN];
int fNum = 0;
unsigned char prime[MAXN] = {0};
int pNum = 0;

int comp(const void *a,const void *b)
{
	fraction aa = *(fraction*)a;
	fraction bb = *(fraction*)b;
	return aa.n * bb.m - aa.m * bb.n;
}

void ProducePrimeN(int n)
{
    prime[pNum++] = 2;
    prime[pNum++] = 3;
    
    int i, j;
    for (i = 5; i <= n; i += 2)
    {
        char flag = 0;
        for (j = 1; j != pNum; ++j)
        {
            if (i % prime[j] == 0)
            {
                flag = 1;
                break;
            }
        } 
        if (!flag)
            prime[pNum++] = i;
    }
	return;
}

int main()
{
	FILE *fin  = fopen("frac1.in" , "r");
	FILE *fout = fopen("frac1.out", "w");

	fscanf(fin, "%d", &N);
    ProducePrimeN(N);

	int i, j;
	
	for (i = 2; i != N+1; ++i)
	{
		int pi;
		for (pi = 0; pi != pNum; ++pi)
		{
			if (i % prime[pi] == 0)
			{
				for (j = 1; j <= (i / prime[pi]); ++j)
					frac[i][j*prime[pi]] = 1;
			}
		}
	}

	for (i = 2; i != N + 1; ++i)
		for (j = i - 1; j > 0; --j)
		{
			if (frac[i][j] == 0)
			{
				f[fNum].m = i;
				f[fNum].n = j;
				++fNum;
			}
		}
	
	qsort(f, fNum, sizeof(fraction), comp);
	fprintf(fout, "0/1\n");
	for (i = 0; i != fNum; ++i)
	{
		fprintf(fout, "%d/%d\n", f[i].n, f[i].m);
	}
	fprintf(fout, "1/1\n");
	fclose(fin);
	fclose(fout);
	return 0;
}
