/*
ID: ryan luo
PROG: transform
LANG: C++
*/

#include <cstdio>

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!! The 4th transformation means reflection vertically. !!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int N;
char squareBefore[10][10] = {' '};
char squareAfter[10][10]  = {' '};

int Transform();

int main()
{
	FILE *fin  = fopen("transform.in" , "r");
	FILE *fout = fopen("transform.out", "w");
	fscanf(fin, "%d", &N);

	int i, j;
	for (i = 0; i != N; ++i)
	{
		getc(fin); // get the \n
		for (j = 0; j != N; ++j)
			squareBefore[i][j] = getc(fin);
	}
	for (i = 0; i != N; ++i)
	{
		getc(fin); // get the \n
		for (j = 0; j != N; ++j)
			squareAfter[i][j] = getc(fin);
	}

	/*for (i = 0; i != N; ++i)
	{		
	for (j = 0; j != N; ++j)
	fprintf(fout, "%c", squareBefore[i][j]);
	fprintf(fout, "\n");
	}
	fprintf(fout, "\n");
	for (i = 0; i != N; ++i)
	{		
	for (j = 0; j != N; ++j)
	fprintf(fout, "%c", squareAfter[i][j]);
	fprintf(fout, "\n");
	}
	fprintf(fout, "\n");*/

	fprintf(fout, "%d\n", Transform());

	fclose(fin);
	fclose(fout);
	return 0;
}

int Transform()
{
	char r9 = 1, r18 = 1, r27 = 1, rRef = 1, rCom9 = 1, rCom18 = 1, rCom27 = 1, rNo = 1;
	int i, j;
	for (i = 0; i != N; ++i)
	{
		for (j = 0; j != N; ++j)
		{
			if (squareBefore[i][j] != squareAfter[i][j])
				rNo = 0;
			if (squareBefore[i][j] != squareAfter[j][N-1-i])
				r9 = 0;
			if (squareBefore[i][j] != squareAfter[N-1-i][N-1-j])
				r18 = 0;
			if (squareBefore[i][j] != squareAfter[N-1-j][i])
				r27 = 0;
			/*if (squareBefore[i][j] != squareAfter[N-1-i][j])
				rRef = 0;
			if (squareBefore[i][j] != squareAfter[j][i])
				rCom9 = 0;
		    if (squareBefore[i][j] != squareAfter[i][N-1-j])
				rCom18 = 0;
			if (squareBefore[i][j] != squareAfter[N-1-j][N-1-i])
				rCom27 = 0;*/
			if (squareBefore[i][j] != squareAfter[i][N-1-j])
				rRef = 0;
			if (squareBefore[i][j] != squareAfter[N-1-j][N-1-i])
				rCom9 = 0;
		    if (squareBefore[i][j] != squareAfter[N-1-i][j])
				rCom18 = 0;
			if (squareBefore[i][j] != squareAfter[j][i])
				rCom27 = 0;
		}
	}
	if (r9 == 1)
		return 1;
	else if (r18 == 1)
		return 2;
	else if (r27 == 1)
		return 3;
	else if (rRef == 1)
		return 4;
	else if (rCom9 == 1 || rCom18 == 1 || rCom27 == 1)
		return 5;
	else if (rNo == 1)
		return 6;
	else
		return 7;
}