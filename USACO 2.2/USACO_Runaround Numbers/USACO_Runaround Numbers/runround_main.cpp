/*
ID: ryan luo
PROG: runround
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;


int main() {
    ifstream fin ("runround.in" );
    ofstream fout("runround.out");
	unsigned long MM = 0;
	char M1[11];
	char M[11];
	char round[10];
	int num = 0;
	char c;
	fin >> MM;
	unsigned long MMM = MM;
	while (MMM != 0)
	{
		M1[num++] = MMM % 10;
		MMM /= 10;
	}

	int iiii = 0;
	unsigned long w = 1;
	for (int i = num - 1; i >= 0; --i)
	{
		M[iiii++] = M1[i];
		w *= 10;
	}

	
	
	char *p = new char[num+1];
	char *q = new char[num+1];
	char *r = new char[10];
	int findR = 0;
	for (unsigned long i = MM + 1; i != w; ++i)
	{		
		unsigned long ii = i;
		memset(r, 0, 10);
		memset(q, 0, num);
		int flag = 0;
		for (int j = num - 1; j >= 0; --j)
		{
			p[j] = ii % 10;
			if (p[j] == 0 || r[p[j]] == 1)
			{
				flag = 1;
				break;
			}
			r[p[j]] = 1;
			ii  /= 10;
		}
		if (flag)
			continue;
		int pos = 0;
		for (int k = 0; k != num; ++k)
		{
			pos = (pos + p[pos] % num) % num;
			if (q[pos])
			{
				flag = 1;
				break;
			}
			else
				q[pos] = 1;
		}
		if (flag)
			continue;
		else
		{
			if(pos == 0)
			{
				findR = 1;
				fout << i << endl;
				break;
			}			
		}		
	}

	if (!findR)
	{
		++num;
		for (unsigned long i = w; i != w * 10; ++i)
		{		
			unsigned long ii = i;
			memset(r, 0, 10);
			memset(q, 0, num);
			int flag = 0;
			for (int j = num - 1; j >= 0; --j)
			{
				p[j] = ii % 10;
				if (p[j] == 0 || r[p[j]] == 1)
				{
					flag = 1;
					break;
				}
				r[p[j]] = 1;
				ii  /= 10;
			}
			if (flag)
				continue;
			int pos = 0;
			for (int k = 0; k != num; ++k)
			{
				pos = (pos + p[pos] % num) % num;
				if (q[pos])
				{
					flag = 1;
					break;
				}
				else
					q[pos] = 1;
			}
			if (flag)
				continue;
			else
			{
				if(pos == 0)
				{
					findR = 1;
					fout << i << endl;
					break;
				}			
			}		
		}
	}

	delete [] p;
	delete [] q;
	delete [] r;
    fin.close();
    fout.close();
    return 0;
}

