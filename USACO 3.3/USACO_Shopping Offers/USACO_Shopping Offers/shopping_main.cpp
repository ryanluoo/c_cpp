/*
ID: ryan luo
PROG: shopping
LANG: C++
*/

#include <fstream>
#include <cstring>
using namespace std;

#define MAXS 99
#define MAXC 999
#define MAXK 5
#define MAXN 5

struct SO
{
	int n;
	int item[MAXN];
	int numb[MAXN];
	int p;
};

SO so[MAXS];
int item[MAXK];
int numb[MAXK];
int pric[MAXK];

//int code[MAXC];
int reco[6][6][6][6][6];
int s, b;

void Update(int si, int* ii)
{
	for (int k = 0; k != so[si].n; ++k)
	{
		for (int j = 0; j != b; ++j)
		{
			if (so[si].item[k] == item[j])
			{
				ii[j] -= so[si].numb[k];
				break;
			}
		}
	}
}
int main()
{
	ifstream fin ("shopping.in" );
	ofstream fout("shopping.out");

	fin >> s;
	for (int i = 0; i != s; ++i)
	{
		fin >> so[i].n;
		for (int j = 0; j != so[i].n; ++j)
			fin >> so[i].item[j] >> so[i].numb[j];
		fin >> so[i].p;
	}

	fin >> b;

	int minp = 0;
	for (int i = 0; i != b; ++i)
	{
		fin >> item[i] >> numb[i] >> pric[i];
		minp += pric[i] * numb[i];
		//code[item[i]-1] = numb[i];
	}

	//reco[0][0][0][0][0] = 0;
	for (int i1 = 0; i1 <= numb[0]; ++i1)
		for (int i2 = 0; i2 <= numb[1]; ++i2)
			for (int i3 = 0; i3 <= numb[2]; ++i3)
				for (int i4 = 0; i4 <= numb[3]; ++i4)
					for (int i5 = 0; i5 <= numb[4]; ++i5)
					{
						reco[i1][i2][i3][i4][i5] = i1 * pric[0] + i2 * pric[1] + i3 * pric[2] + i4 * pric[3] + i5 * pric[4];
						for (int si = 0; si != s; ++si)
						{
							int ii[5];
							ii[0] = i1; ii[1] = i2; ii[2] = i3; ii[3] = i4; ii[4] = i5;
							Update(si, ii);
							if (ii[0] < 0 ||
								ii[1] < 0 || 
								ii[2] < 0 || 
								ii[3] < 0 ||
								ii[4] < 0)
								continue;
							int newpric = reco[ii[0]][ii[1]][ii[2]][ii[3]][ii[4]] + so[si].p;
							if (newpric < reco[i1][i2][i3][i4][i5])
								reco[i1][i2][i3][i4][i5] = newpric;
						}
					}
	

	fout << reco[numb[0]][numb[1]][numb[2]][numb[3]][numb[4]] << endl;
	fin.close();
	fout.close();
	return 0;
}
