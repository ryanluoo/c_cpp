/*
ID: ryan luo
PROG: ratios
LANG: C++
*/

#include <fstream>
#include <cstring>
using namespace std;

int m[3][4] = {0};

// least common multiple
int lcm(int a, int b)
{
	if (a * b == 0)
		return 0;
	int max = (a >= b ? a : b);
	int min = (a <  b ? a : b);
	int i;
	for(i = 1;;i++)
		if((max * i) % min == 0)
			return (max * i);
}

int main()
{
	ifstream fin ("ratios.in" );
	ofstream fout("ratios.out");

	fin >> m[0][3] >> m[1][3] >> m[2][3];
	m[0][3] = -m[0][3]; 
	m[1][3] = -m[1][3]; 
	m[2][3] = -m[2][3];
	for (int i = 0; i != 3; ++i)
		fin >> m[0][i] >> m[1][i] >> m[2][i];
	
//first
	int l = lcm (m[0][0], m[1][0]);
	if (m[1][0] != 0)
	{
		m[1][1] = m[1][1] * l / m[1][0] - m[0][1] * l / m[0][0];
		m[1][2] = m[1][2] * l / m[1][0] - m[0][2] * l / m[0][0];
		m[1][3] = m[1][3] * l / m[1][0] - m[0][3] * l / m[0][0];
		m[1][0] = 0;
		if (m[1][1] < 0)
		{
			m[1][1] = -m[1][1];
			m[1][2] = -m[1][2];
			m[1][3] = -m[1][3];
		}
	}	

	l = lcm (m[0][0], m[2][0]);	
	if (m[2][0] != 0)
	{
		m[2][1] = m[2][1] * l / m[2][0] - m[0][1] * l / m[0][0];
		m[2][2] = m[2][2] * l / m[2][0] - m[0][2] * l / m[0][0];
		m[2][3] = m[2][3] * l / m[2][0] - m[0][3] * l / m[0][0];
		m[2][0] = 0;
		if (m[2][1] < 0)
		{
			m[2][1] = -m[2][1];
			m[2][2] = -m[2][2];
			m[2][3] = -m[2][3];
		}
	}

//second
	l = lcm (m[1][1], m[2][1]);
	if (m[2][1] != 0)
	{
		m[2][2] = m[2][2] * l / m[2][1] - m[1][2] * l / m[1][1];
		m[2][3] = m[2][3] * l / m[2][1] - m[1][3] * l / m[1][1];	
		m[2][1] = 0;
		if (m[2][2] < 0)
		{
			m[2][2] = -m[2][2];
			m[2][3] = -m[2][3];
		}
	}

	if (m[2][2] * m[2][3] >= 0)
		fout << "NONE" << endl;
	else
	{
		l = lcm (m[2][2], -m[2][3]);
		int x = l / (-m[2][3]);
		int c = l /   m[2][2];
		int b = (m[1][3] * x + m[1][2] * c) / (-m[1][1]);
		if (b < 0)
			fout << "NONE" << endl;
		else
		{
			int a = (m[0][3] * x + m[0][2] * c + m[0][1] * b) / (-m[0][0]);
			if (a < 0)
				fout << "NONE" << endl;
			else
				fout << a << " " << b << " " << c << " " << x << endl;
		}
		
	}
	



	fin.close();
	fout.close();
	return 0;
}
