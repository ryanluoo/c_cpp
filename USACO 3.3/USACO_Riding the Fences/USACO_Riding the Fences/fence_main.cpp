/*
ID: ryan luo
PROG: fence
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <list>
#include <map>
using namespace std;

#define MAXI 500

struct node
{
	node *next;
	int v;
	node (int x){
		this->next = NULL;
		this->v = x;
	}
	node ()
	{
		this->next = NULL;
		this->v = 0;
	}
};

node fencel[MAXI+1];
node* tail[MAXI+1];
int  fencea[MAXI+1][MAXI+1] = {0};
int path[2*MAXI+1] = {0};
int npath = 0;
int f = 0;
list< pair<int, int> > l;
void Euler(int cur, int last)
{
	while (fencel[cur].next != NULL)
	{
		int i = fencel[cur].next->v;
		node *n = fencel[cur].next;
		fencel[cur].next = fencel[cur].next->next;
		delete n;
		if (fencea[cur][i] > 0)
		{
			--fencea[i][cur];
			--fencea[cur][i];
			Euler(i, cur);			
		}
	}
	path[npath++] = cur;
	path[npath++] = last;
}

int main()
{
	ifstream fin ("fence.in" );
	ofstream fout("fence.out");

	for (int i = 0; i != MAXI+1; ++i)
	{
		tail[i] = &fencel[i];
		fencel[i].v = 0;
	}

	int F;
	fin >> F;
	int min = 501;
	for (int i = 0; i != F; ++i)
	{
		int a, b;
		fin >> a >> b;
		min = a < min ? a : min; 
		min = b < min ? b : min;
		++fencea[a][b];
		++fencea[b][a];
		++fencea[0][a];
		++fencea[0][b];
	}
	for (int i = 0; i != MAXI+1; ++i)
	{
		for (int j = 0; j != MAXI+1; ++j)
		{
			for (int n = 0; n != fencea[i][j]; ++n)
			{
				tail[i]->next = new node(j);
				tail[i] = tail[i]->next;
			}
		}
	}
	
	int start;
	for (start = 1; start != MAXI+1; ++start)
	{
		if (fencea[0][start] % 2 == 1)
			break;
	}
	start = start == MAXI + 1 ? min : start;

	//EULER
	Euler(start, -1);
		
	npath -= 2;
	while(npath >= 0)
	{
		fout << path[npath] << endl;
		npath -= 2;
	}
	fin.close();
	fout.close();
	return 0;
}
