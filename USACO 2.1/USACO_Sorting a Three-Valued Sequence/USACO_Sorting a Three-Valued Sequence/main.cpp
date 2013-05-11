/*
ID: ryan luo
PROG: sort3
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#define MAXN 1000

int N;
char seq[MAXN];
int nums[3] = {0};
int occupy[4][4] = {0};
int exchageNum = 0;

int main()
{
	FILE *fin  = fopen("sort3.in" , "r");
	FILE *fout = fopen("sort3.out", "w");

	fscanf(fin, "%d", &N);	
	int i;
	for (i = 0; i != N; ++i)
	{
		int t;
		fscanf(fin, "%d", &t);
		seq[i] = t;
		++nums[t - 1];
	}

	for (i = 0; i != nums[0]; ++i)
	{
		if (seq[i] == 2)
			++occupy[2][1];
		if (seq[i] == 3)
			++occupy[3][1];
	}
	for (i = nums[0]; i != nums[0]+nums[1]; ++i)
	{
		if (seq[i] == 1)
			++occupy[1][2];
		if (seq[i] == 3)
			++occupy[3][2];
	}
	for (i = nums[0]+nums[1]; i != nums[0]+nums[1]+nums[2]; ++i)
	{
		if (seq[i] == 1)
			++occupy[1][3];
		if (seq[i] == 2)
			++occupy[2][3];		
	}
	
	//cal
	if (occupy[1][2] != 0)
	{
		int e = occupy[1][2] < occupy[2][1] ? occupy[1][2] : occupy[2][1];
		occupy[1][2] -= e;
		occupy[2][1] -= e;
		exchageNum += e;
	}

	if (occupy[1][3] != 0)
	{
		int e = occupy[1][3] < occupy[3][1] ? occupy[1][3] : occupy[3][1];
		occupy[1][3] -= e;
		occupy[3][1] -= e;
		exchageNum += e;
	}

	if (occupy[2][3] != 0)
	{
		int e = occupy[2][3] < occupy[3][2] ? occupy[2][3] : occupy[3][2];
		occupy[2][3] -= e;
		occupy[3][2] -= e;
		exchageNum += e;
	}

	int e = occupy[1][2] + occupy[1][3];

	exchageNum = exchageNum + 2 * e;

	fprintf(fout, "%d\n", exchageNum);
	
	fclose(fin);
	fclose(fout);
	return 0;
}
