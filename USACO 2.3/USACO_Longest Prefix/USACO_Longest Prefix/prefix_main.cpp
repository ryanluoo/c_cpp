/*
ID: ryan luo
PROG: prefix
LANG: C++
*/

#include <fstream>
#include <cstring>
using namespace std;

#define PMAXLEN 10
#define PMAXNUM 200
#define MAXLEN  200000

char prm[PMAXNUM][PMAXLEN+1];
int  prmNum = 0;
int  plenmax = 0;
char S[MAXLEN+1];
int history[MAXLEN] = {0};

int cmp (const void *s1, const void *s2)
{
	return strcmp((char*)s1, (char*)s2);
}

int FindPrm(char *s, int num)
{
	char *c = new char[num+1];
	strncpy(c, s, num);
	c[num] = '\0';
	int result;	
	void *r = bsearch(c, prm, prmNum, PMAXLEN+1, cmp);
	if (r == NULL)
		result = 0;
	else
		result = 1;
	delete [] c;
	return result;
}

int FindPrefixLen(int end)
{

	if(FindPrm(S, 1))
		history[0] = 1;
	else
		history[0] = 0;
	
	for (int i = 1; i <= end; ++i)
	{
		int maxever = history[i-1];
		for (int j = 1; j <= plenmax; ++j)
		{
			if (i - j + 1 < 0)
				break;
			if((i - j < 0 || history[i-j] == i-j+1) && FindPrm(S+i-j+1, j))
			{
				maxever = i+1;
				break;
			}			
		}
		history[i] = maxever;
	}

	return history[end];
}



int main()
{	
	ifstream fin ("prefix.in" );
	ofstream fout("prefix.out");
		
	char str[PMAXLEN+1];
	while (1)
	{
		fin >> str;
		if (str[0] == '.')
			break;
		if (strlen(str) > plenmax)
			plenmax = strlen(str);
		strcpy(prm[prmNum++], str);
	}
	int num = 0;
	while (1)
	{
		char c = fin.get();
		if(c == EOF)
			break;
		if (c <= 'Z' && c >= 'A')
			S[num++] = c;
	}
	S[num] = '\0';
	qsort(prm, prmNum, PMAXLEN+1, cmp);
	fout << FindPrefixLen(num) << endl;

	fin.close();
	fout.close();
	return 0;
}
