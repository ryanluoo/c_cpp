/*
ID: ryan luo
PROG: calfflac
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cctype>

#define MAXLEN 20000
char file[MAXLEN+1];
int len = 0;
int imax = 0, jmax = 0, lenmax = 0;
//int p[MAXLEN][MAXLEN] = {0};
char isLetter(char c)
{
	if(islower(c) || isupper(c))
		return 1;
	else
		return 0;
}

void findLongest(int center)
{
	//Odd
	int i = center - 1, j = center + 1, l = 1;
	while (i >= 0 || j <= len - 1)
	{
		if (i >= 0 && !isLetter(file[i]))
			--i;
		else if (j <= len - 1 && !isLetter(file[j]))
			++j;
		else if (j >= len || i < 0 || tolower(file[i]) != tolower(file[j]))
		{
			++i;
			--j;
			break;
		}
		else if (tolower(file[i]) == tolower(file[j]))
		{
			--i;
			++j;
			l += 2;
		}
	}
	
	if (l > lenmax)
	{
		lenmax = l;
		imax = i;
		jmax = j;
	}
	if (center + 1 >= len)
		return;

	i = center - 1; j = center + 1; l = 2;
	while(!isLetter(file[j]))
	{
		++j;
		if (j == len)
			return;
	}

	if (tolower(file[center]) != tolower(file[j]))
		return;
	j = j + 1;
	//Even
	
	while (i >= 0 || j <= len - 1)
	{
		if (i >= 0 && !isLetter(file[i]))
			--i;
		else if (j <= len - 1 && !isLetter(file[j]))
			++j;
		else if (j >= len || i < 0 || tolower(file[i]) != tolower(file[j]))
		{
			++i;
			--j;
			break;
		}
		else if (tolower(file[i]) == tolower(file[j]))
		{
			--i;
			++j;
			l += 2;
		}
	}

	if (l > lenmax)
	{
		lenmax = l;
		imax = i;
		jmax = j;
	}
}

//int isPalindrome(int i, int j)
//{
//	if (p[i][j] != -2)
//		return p[i][j];
//
//	if (i == j)
//	{
//		if (isLetter(file[i]))
//		{
//			p[i][j] = 1;
//			return 1;
//		}
//		else
//		{
//			p[i][j] = 0;
//			return 0;
//		}
//	}
//
//	if (i + 1 == j)
//	{
//		if (!isLetter(file[i]) && !isLetter(file[j]))
//		{
//			p[i][j] = 0;
//			return 0;
//		}
//		else if (isLetter(file[i]) && isLetter(file[j]))
//		{
//			p[i][j] = 2;
//			return 2;
//		}
//		else
//		{
//			p[i][j] = 1;
//			return 1;
//		}
//	}
//
//	if (!isLetter(file[i]))
//	{
//		if (p[i+1][j] == -2)
//			p[i+1][j] = isPalindrome(i+1, j);
//		p[i][j] = p[i+1][j];
//		return p[i][j];
//	}
//	if (!isLetter(file[j]))
//	{
//		if (p[i][j-1] == -2)
//			p[i][j-1] = isPalindrome(i, j-1);		
//		p[i][j] = p[i][j-1];
//		return p[i][j];
//	}
//
//	if (tolower(file[i]) != tolower(file[j]))
//	{
//		p[i][j] = -1;
//		return -1;
//	}
//
//	if (p[i+1][j-1] == -2)
//		p[i+1][j-1] = isPalindrome(i+1, j-1);
//	if (p[i+1][j-1] == -1)
//	{
//		p[i][j] = -1;
//		return -1;
//	}
//
//	p[i][j] = p[i+1][j-1] + 2;
//	return p[i][j];
//}

int main()
{
	FILE *fin  = fopen("calfflac.in" , "r");
	FILE *fout = fopen("calfflac.out", "w");


	while (!feof(fin) && len != MAXLEN)
		file[len++] = getc(fin);
	file[--len] = '\0';

	//int i, j;
	//for (i = 0; i != len; ++i)
	//	for (j = 0; j != len; ++j)
	//	{
	//		p[i][j] = -2;
	//	}

	//int imax = 0, jmax = 0, lenmax = 0;	
	//for (i = 0; i != len; ++i)
	//{
	//	for (j = i; j != len; ++j)
	//	{
	//		int l = isPalindrome(i, j);
	//		if(l != -1 && l > lenmax)
	//		{
	//			lenmax = l;
	//			imax = i;
	//			jmax = j;
	//		}
	//	}
	//}
	//fprintf(fout, "%d\n", lenmax);
	//while(!isLetter(file[imax++]));
	//for (i = imax-1; i <= jmax; ++i)
	//	fprintf(fout, "%c", file[i]);
	//fprintf(fout, "\n");

	int i = 0;
	while (i != len)
	{
		if (i + lenmax >= len)
			break;
		if (isLetter(file[i]))
			findLongest(i);
		int l = lenmax;
		++i;
	}
	while (!isLetter(file[imax++])); --imax;
	while (!isLetter(file[jmax--])); ++jmax;
	fprintf(fout, "%d\n", lenmax);
	for (i = imax; i != jmax + 1; ++i)
		fprintf(fout, "%c", file[i]);
	fprintf(fout, "\n");
	fclose(fin);
	fclose(fout);
	return 0;
}
