/*
ID: ryan luo
PROG: concom
LANG: C++
*/

#include <fstream>
#include <string>
using namespace std;

#define MAXNUM 100

ifstream fin ("concom.in" );
ofstream fout("concom.out");
int n;
int maxn = 0;
char tri[MAXNUM+1][MAXNUM+1] = {0};
char con[MAXNUM+1][MAXNUM+1] = {0};
//char res[MAXNUM+1][MAXNUM+1] = {0};
//char sta[MAXNUM+1][MAXNUM+1] = {0};

//int FindControl(int h, int s)
//{
//	if (h == s)
//		return 0;
//	if (con[h][s] == 1 || tri[h][s] > 50)
//		return 1;
//	if (con[h][s] == -1)
//		return 0;	
//	if (tri[h][s] <= 50 && tri[h][s] != 0)
//	{
//		con[h][s] = -1;
//		return 0;
//	}
//	if(sta[h][s] == 1)
//		return 0;
//
//	sta[h][s] = 1;
//	int sum = 0;
//	int flag = 0;
//	for (int i = 1; i <= maxn; ++i)
//	{
//		
//		if (i != h && i != s && tri[i][s] > 0)
//		{	
//			if (sta[h][i] == 1)
//				flag = 1;
//			sum += FindControl(h, i) * tri[i][s];
//			if (sum > 50)
//			{
//				con[h][s] = 1;
//				return 1;
//			}
//		}
//	}
//
//	sta[h][s] = 0;
//
//	if (sum > 50)
//	{
//		con[h][s] = 1;
//		return 1;
//	}
//
//	if (flag == 0)
//		con[h][s] = -1;
//	else
//		con[h][s] = 0;
//	return 0;
//}

int main()
{
	fin >> n;

	for (int i = 0; i != n; ++i)
	{
		int j1, j2, k;
		fin >> j1 >> j2 >> k;
		maxn = maxn > j1 ? maxn : j1;
		maxn = maxn > j2 ? maxn : j2;
		tri[j1][j2] = k;
		if (tri[j1][j2] > 50)
		{
			con[j1][j2] = 1;
			//fout << j1 << " " << j2 << endl;
		}
	}

	/*for (int i = 1; i <= maxn; ++i)
	for (int j = 1; j <= maxn; ++j)
	{
	if (i != j && FindControl(i, j) == 1)
	fout << i << " " << j << endl;
	}*/

	while (1)
	{
		int flag = 1;

		for (int i = 1; i <= maxn; ++i)
		{
			char s[MAXNUM+1] = {0};
			int num = 0;
			s[num++] = i;
			for (int m = 1; m <= maxn; ++m)
			{
				if (con[i][m])
					s[num++] = m;
			}
			
			for (int j = 1; j <= maxn; ++j)
			{
				if (i == j || con[i][j] == 1)
					continue;
				int sum = 0;
				for (int k = 0; k != num; ++k)
				{
					sum += tri[s[k]][j];
				}
				if (sum > 50)
				{
					con[i][j] = 1;
					//fout << i << " " << j << endl;
					flag = 0;
				}
			}
		}

		if (flag)
			break;
	}

	for (int i = 1; i <= maxn; ++i)
		for (int j = 1; j <= maxn; ++j)
			if(i != j && con[i][j] == 1)
				fout << i << " " << j << endl;

	fin.close();
	fout.close();
	return 0;
}
