/*
ID: ryan luo
PROG: milk3
LANG: C++
*/
//test
#include <cstdio>
#include <cstdlib>
#include <cstring>

char amounts[21][21][21] = {0};
char* cAmount = NULL;
int A, B, C;

void
process(int a, int b, int c)
{
	if (a == 0)
		cAmount[c] = 1;

	if (amounts[a][b][c] == 1)
		return;
	else
		amounts[a][b][c] = 1;
	
	// C --> A
	if (c > (A - a))		
		process(A, b, c - (A - a));
	else
		process(a + c, b, 0);

	//C --> B
	if (c > (B - b))
		process(a, B, c - (B - b));
	else
		process(a, b + c, 0);

	//A --> B
	if (a > (B - b))
		process(a - (B - b), B, c);
	else
		process(0, b + a, c);

	//A --> C
	if (a > (C - c))
		process(a - (C - c), b, C);
	else
		process(0, b, c + a);

	//B --> A
	if (b > (A - a))
		process(A, b - (A - a), c);
	else
		process(a + b, 0, c);

	//B --> C
	if (b > (C - c))
		process(a, b - (C - c), C);
	else
		process(a, 0, c + b);
}

int 
main()
{
	FILE *fin  = fopen("milk3.in" , "r");
	FILE *fout = fopen("milk3.out", "w");

	fscanf(fin, "%d %d %d", &A, &B, &C);
	cAmount = (char*)malloc(sizeof(char) * (C+1));
	memset(cAmount, 0, C + 1);
	process(0, 0, C);
	int i;
	int first = 1;
	for (i = 0; i != C + 1; ++i)
	{
		if (cAmount[i] == 1)
		{
			if (first == 1)
			{
				first = 0;
				fprintf(fout, "%d", i);
			}
			else
				fprintf(fout, " %d", i);
		}
	}
	fprintf(fout, "\n");

	free(cAmount);
	fclose(fin);
	fclose(fout);
	return 0;
}
