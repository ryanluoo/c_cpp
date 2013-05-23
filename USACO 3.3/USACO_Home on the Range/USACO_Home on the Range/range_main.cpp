/*
ID: ryan luo
PROG: range
LANG: C++
*/

#include <fstream>
#include <cstring>
using namespace std;

#define MAXN 250
int N;
char field[MAXN][MAXN+1];
char count[MAXN][MAXN];
int main()
{
	ifstream fin ("range.in" );
	ofstream fout("range.out");

	fin >> N;
	fin.getline(field[0], MAXN+1);
	for (int i = 0; i != N; ++i)
	{
		fin.getline(field[i], N+1);
		for (int j = 0; j != N; ++j)
		{
			field[i][j] -= '0';
			count[i][j] = field[i][j];
		}
	}
	
	for (int i = 2; i <= N; ++i)
	{
		int num = 0;
		for (int a = 0; a <= N - i; ++a)
		{
			for (int b = 0; b <= N - i; ++b)
			{
				bool flag = true;
				if (!count[a][b])
					continue;
				for (int j = 0; j != i; ++j)
				{
					if (!field[a+i-1][b+j] || !field[a+j][b+i-1])
					{
						flag = false;
						break;
					}
				}
				if (flag)
				{
					++num;
					count[a][b] = 1;
				}
				else
					count[a][b] = 0;
			}
		}
		if (num != 0)
			fout << i << " " << num << endl;
	}
	fin.close();
	fout.close();
	return 0;
}
