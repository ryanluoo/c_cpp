/*
ID: ryan luo
PROG: ditch
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <list>
using namespace std;

#define MAXN 200
#define MAXM 200

int N, M;
int c[MAXM * 2][MAXM * 2] = {0};
int f[MAXM * 2][MAXM * 2] = {0};
int e[MAXM * 2] = {0};
int h[MAXM * 2] = {0};
list<int> l;
list<int> g[MAXM * 2];
int vs[MAXM] = {0};
int ve[MAXM] = {0};
list<int> vp;

bool validPoint(int v)
{
	if (v == 0 || v == M - 1)
		return true;
	return !((vs[v] > 0 && ve[v] <= 0) || (vs[v] <= 0 && ve[v] > 0));
	/*return !(vs[v] & ve[v]);*/
}

int cf (int u, int v)
{
	if (c[u][v] > 0)
		return c[u][v] - f[u][v];
	else if (c[v][u] > 0)
		return f[v][u];
	return 0;
}

void RELABEL (int u)
{
	int minh = M + 1;
	for (list<int>::iterator i = g[u].begin(); i != g[u].end(); ++i)
		if (cf(u, *i) > 0 && h[*i] < minh)
			minh = h[*i];
	
	h[u] = minh + 1;	
}

void PUSH (int u, int v)
{
	int incf = e[u] < cf(u, v) ? e[u] : cf(u, v);
	if (c[u][v] > 0)
		f[u][v] += incf;
	else if (c[v][u] > 0)
		f[v][u] -= incf;
	e[u] -= incf;
	e[v] += incf;
}

void DISCHARGE(int u)
{
	list<int>::iterator current = g[u].begin();
	list<int>::iterator v;
	int time = 0;
	while (e[u] > 0)
	{	
		v = current;
		if (v == g[u].end())
		{
			RELABEL(u);
			current = g[u].begin();
		}
		else if (cf(u, *v) > 0 && h[u] == h[*v] + 1)
			PUSH(u, *v);
		else
			++current;
		++time;
	}
}

void RTF ()
{	
	list<int>::iterator u = l.begin();
	while (u != l.end())
	{
		int old_height = h[*u];
		DISCHARGE(*u);
		if (h[*u] != old_height)
		{
			l.push_front(*u);
			l.erase(u);
			u = l.begin();
		}
		++u;
	}
}

int main()
{
	ifstream fin ("ditch.in" );
	ofstream fout("ditch.out");

	fin >> N >> M;

	h[0] = M;

	int i, j;
	int Stemp, Etemp, Ctemp;
	for (i = 0; i != N; ++i)
	{		
		fin >> Stemp >> Etemp >> Ctemp;
		Stemp -= 1; Etemp -= 1;
		c[Stemp][Etemp] += Ctemp;
		vs[Stemp] += 1;
		ve[Etemp] += 1;
	}

	//删除孤立点
	for (i = 1; i != M - 1; ++i)
		if (!validPoint(i))
			vp.push_back(i);

	while (!vp.empty())
	{
		int v = *vp.begin();
		if (ve[v] <= 0)
		{
			for (i = 1; i != M - 1; ++i)
			{
				if (c[v][i] != 0)
				{
					c[v][i] = 0;
					--ve[i];
					if (!validPoint(i))
						vp.push_back(i);
				}
			}
		}
		else if (vs[v] <= 0)
		{
			for (i = 1; i != M - 1; ++i)
			{
				if (c[i][v] != 0)
				{
					c[i][v] = 0;
					--vs[i];
					if (!validPoint(i))
						vp.push_back(i);
				}
			}
		}
		vp.pop_front();
	}


	//初始化邻接链表，预流，溢出数组。
	int m = M;
	for (i = 0; i != M - 1; ++i)
		for (j = 1; j != M; ++j)
		{
			if (i != j && c[i][j] != 0)
			{
				g[i].push_back(j);
				g[j].push_back(i);

				if (i == 0) //源节点
				{
					e[0] -= c[i][j];
					f[0][j] = c[i][j];
					e[j] += c[i][j];
				}

				//消除平行边
				if (c[j][i] != 0)
				{
					c[j][m] = c[m][i] = c[j][i];
					c[j][i] = 0;
					g[j].push_back(m); g[m].push_back(j);
					g[i].push_back(m); g[m].push_back(i); 
					++m;
				}				
			}
		}

	for (i = 1; i != M - 1; ++i)
	{
		bool vp = false;
		for (j = 0; j != m; ++j)
			if (i != j && (c[i][j] != 0 || c[j][i] != 0))
			{
				vp = true;
				break;
			}
		if (vp)
			l.push_back(i);
	}

	for (i = M; i != m; ++i)
		l.push_back(i);

	M = m;

	//前置重贴标签算法
	RTF();

	int maxf = 0;
	for (i = 1; i != M; ++i)
		if (c[0][i] > 0)
			maxf += f[0][i];

	fout << maxf << endl;

	fin.close();
	fout.close();
	return 0;
}
