/*
ID: ryan luo
PROG: beads
LANG: C++
*/

//w may be treated as r or b.
#include <cstdio>
#include <cstdlib>
#include <cstring>

int main()
{
	FILE *fin  = fopen("beads.in" , "r");
	FILE *fout = fopen("beads.out", "w");
	
	char N[4], necklace[351];
	fscanf(fin, "%s\n%s", N, necklace);
	int beadsNum = atoi(N), necklaceLen = strlen(necklace);
	int totalNum = 0; //The result

	//Use the hint from USACO.
	int index = 0;
	int num = 0;
	int numw = 0;
	for (index = 0; index != necklaceLen; ++index)
	{
		if (necklace[index] != 'w')
		{
			bool istop  = false;
			bool ristop = false;
			int  i  = index;
			int  ri = (index == 0) ? necklaceLen - 1 : index - 1;
			char c  = necklace[i];			
			char rc = necklace[ri];

			while (i != ri)
			{
				if (necklace[i] == c || necklace[i] == 'w')
					i = (i == necklaceLen - 1) ? 0 : i + 1;
				else if (ristop)
					break;
				else
					istop = true;

				if(i == ri)
					break;

				if (rc == 'w')
					rc = necklace[ri];

				if (necklace[ri] == rc || necklace[ri] == 'w')
					ri = (ri == 0) ? necklaceLen - 1 : ri - 1;
				else if (istop)
					break;
				else
					ristop = true;
			}

			int fill = 0;
			if (i == ri)
				fill = 1;

			int num1 = 0, num2 = 0;
			if (i <= index)
				num1 = i + (necklaceLen - index);
			else
				num1 = i - index;

			if (ri >= index)
				num2 = index + (necklaceLen - ri - 1);
			else
				num2 = index - 1 - ri;

			if (num1 + num2 + fill > totalNum)
				totalNum = num1 + num2 + fill;
		}
		else
			++numw;
	}
	if (numw == necklaceLen)
		fprintf(fout, "%d\n", necklaceLen);
	else
		fprintf(fout, "%d\n", totalNum);

	fclose(fin);
	fclose(fout);
	return 0;
}
