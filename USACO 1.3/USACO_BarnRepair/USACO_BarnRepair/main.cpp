/*
ID: ryan luo
PROG: barn1
LANG: C++
*/

#include <cstdio>
#include <cstdlib>

int cmp(const void *a, const void *b)
{
	 return -(*(int*)a - *(int*)b);
}

int main()
{
	FILE *fin  = fopen("barn1.in" , "r");
	FILE *fout = fopen("barn1.out", "w");

	int M, S, C;
	fscanf(fin, "%d %d %d", &M, &S, &C);
	char* stalls = (char*)malloc(sizeof(char) * S);
	int i, num = 0;
	int minNum = S, maxNum = 0;
	for (i = 0; i != S; ++i)
		stalls[i] = 0;
	for (i = 0; i != C; ++i)
	{
		fscanf(fin, "%d", &num);
		stalls[num] = 1;
		if (minNum > num)
			minNum = num;
		if (maxNum < num)
			maxNum = num;
	}

	int unOccupiedNum = 0;
	char counting = 0;
	int *o = (int*)malloc(sizeof(int) * (S-C));
	int j = 0;
	for (i = minNum; i != maxNum+1; ++i)
	{
		if (stalls[i] == 0)
		{
			counting = 1;
			++unOccupiedNum;
		}
		else
		{
			if (counting == 1)
			{
				o[j++] = unOccupiedNum;
			    //fprintf(fout, "%d %d \n", i, unOccupiedNum);
				unOccupiedNum = 0;
				counting = 0;
			}			
		}
	}
	/*fprintf(fout, "\n");
	for (i = 0; i != j; ++i)
	fprintf(fout, "%d ", o[i]);*/
	qsort(o, j, sizeof(int), cmp);

	int sum = 0;
	for(i = 0; i != M-1 && i != S-C; ++i)
		sum += o[i];
		
	fprintf(fout, "%d\n", maxNum - minNum + 1 - sum);
	free(stalls);
	free(o);

	fclose(fin);
	fclose(fout);
	return 0;
}
