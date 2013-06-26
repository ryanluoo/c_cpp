/*
ID: ryan luo
PROG: nuggets
LANG: C++
*/

#include <fstream>
#include <cstring>
using namespace std;

#define MAXI   256
#define MAXNUG 2000000000
int  N;
int  nuggets[10];
char history[MAXI+1];
char rec[MAXI+1];
int  flag = 0;

int Count1()
{
	int r = 0;
	for (int i = 0; i != MAXI + 1; ++i)
	{
		if (history[i] == 1)
			++r;
	}
	return r;
}
int main()
{
	ifstream fin ("nuggets.in" );
	ofstream fout("nuggets.out");
	
	fin >> N;
	unsigned minn = MAXNUG;
	unsigned maxn = 0;
	for (int i = 0; i != N; ++i)
	{
		fin >> nuggets[i];
		minn = minn < nuggets[i] ? minn : nuggets[i];
		maxn = maxn > nuggets[i] ? maxn : nuggets[i];
	}	
	memset(history, 0, MAXI+1);
	memset(rec, 0, MAXI+1);
	
	if (minn == 1)
		flag = 1;

	unsigned int maxnug = 1;
	unsigned int nug = minn;
	unsigned int nopurchase  = 0;
	int start = 0;
	
	while (nug < MAXNUG && nopurchase <= MAXI)
	{	
		history[start] = 0;		

		for (int n = 0; n != N; ++n)
		{
			if (history[start] == 1)
				continue;
			if (nug - nuggets[n] == 0)
				history[start] = 1;
			else
				history[start] = history[(nuggets[n] + start) % (MAXI + 1)];
		}

		if (history[start] == 0)
		{
			nopurchase = 0;
			maxnug = nug;
		}
		else
			++nopurchase;

		if (nug == 1000000)
		{
			flag = 1;
			break;
		}

		//int r = Count1();
		start = start == 0 ? MAXI : start - 1;
		++nug;		
	}

	if (flag == 1)
		fout << "0" << endl;
	else
		fout << maxnug << endl;

	fin.close();
	fout.close();
	return 0;
}
