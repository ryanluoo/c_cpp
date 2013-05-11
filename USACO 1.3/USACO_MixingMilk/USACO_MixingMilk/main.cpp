/*
ID: ryan luo
PROG: milk
LANG: C++
*/

#include <cstdio>
#include <cstdlib>

typedef struct MilkFarmer {int amount; int price;};
int cmp (const void* a, const void* b)
{
	MilkFarmer* farmerA = (MilkFarmer*)a;
	MilkFarmer* farmerB = (MilkFarmer*)b;
	if (farmerA->price < farmerB->price)
		return -1;
	if (farmerA->price == farmerB->price)
		return 0;
	if (farmerA->price > farmerB->price)
		return 1;
}

int main()
{
	FILE *fin  = fopen("milk.in" , "r");
	FILE *fout = fopen("milk.out", "w");
	int N, M;
	fscanf(fin, "%d %d", &N, &M);
	MilkFarmer* farmers = (MilkFarmer*) malloc(sizeof(MilkFarmer) * M);
	int i;
	for (i = 0; i != M; ++i)
	{
		fscanf(fin, "%d %d", &farmers[i].price, &farmers[i].amount);
	}
	qsort(farmers, M, sizeof(MilkFarmer), cmp);
	

	int cost = 0;
	i = 0;
	while (N > 0 && i != M)
	{
		if (farmers[i].amount < N)
		{
			cost += farmers[i].amount * farmers[i].price;
			N -= farmers[i].amount;
			++i;
		}
		else
		{
			cost += N * farmers[i].price;
			N = 0;
		}
	}

	fprintf(fout, "%d\n", cost);
	free(farmers);

	fclose(fin);
	fclose(fout);
	return 0;
}
