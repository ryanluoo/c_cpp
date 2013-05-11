/*
ID: ryan luo
PROG: rect1
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <set>
#include <map>
#include <cstring>
using namespace std;

#define MAXAB 10000
#define MAXN   1000
#define MAXC   2500

#define lson L, m, rt << 1
#define rson m, R, rt << 1 | 1

struct RECTLINE
{
	int l, r, h; // left, right, height
	int n; // layer number
	int c; // color
	
	RECTLINE() : l(0), r(0), h(0), n(0), c(1) {}
	RECTLINE(int l, int r, int h, int n, int c) : l(l), r(r), h(h), n(n), c(c) {}
	RECTLINE& operator= (const RECTLINE& rl)
	{
		l = rl.l; r = rl.r; h = rl.h;
		n = rl.n; c = rl.c;
		return *this;
	}
	//Compare
	friend bool operator< (const RECTLINE& rl1, const RECTLINE& rl2) 
	{ 
		return (rl1.h < rl2.h || (rl1.h == rl2.h && rl1.n < rl2.n));
	}
	friend bool operator==(const RECTLINE& rl1, const RECTLINE& rl2)
	{
		return (rl1.h == rl2.h && rl1.n == rl2.n);
	}
	friend bool operator> (const RECTLINE& rl1, const RECTLINE& rl2) 
	{
		return (rl1.h > rl2.h || (rl1.h == rl2.h && rl1.n > rl2.n));
	}
};

set<int> X;
RECTLINE rectline[MAXN << 1];
int low, high;
int  sum[MAXC + 1];
int  col[MAXAB << 2];
char cnt[MAXAB << 2];

//Tree Function
void PushDown(int rt)
{
	if (cnt[rt] == 1)
	{
		cnt[rt << 1] = cnt[rt << 1 | 1] = 1;
		col[rt << 1] = col[rt << 1 | 1] = col[rt];
	}
}

void PushUp(int rt)
{
	if (rt == 1)
		return;
	if (cnt[rt] != 1 || cnt[rt ^ 1] != 1 || col[rt] != col[rt ^ 1])
		cnt[rt >> 1] = 0;
	else
	{
		col[rt >> 1] = col[rt];
		cnt[rt >> 1] = 1;
	}
	PushUp(rt >> 1);
}

void Update(int l, int r, int c, int L, int R, int rt)
{
	if (R - L == 1)
	{
		if (L >= l && L < r)
		{
			sum[col[rt]] -= (high - low);
			sum[c] += (high - low);
			cnt[rt] = 1;
			col[rt] = c;
			PushUp(rt);
		}
		return;
	}

	if (cnt[rt] != 1)
	{
		int m = (L + R) >> 1;
		if (l < m) Update(l, r, c, lson);
		if (r > m) Update(l, r, c, rson);
		return ;
	}

	if (L >= l && R <= r)
	{
		sum[col[rt]] -= (R - L) * (high - low);
		sum[c] += (R - L) * (high - low);
		cnt[rt] = 1;
		col[rt] = c;
		PushUp(rt);
		return;
	}

	PushDown(rt);
	int m = (L + R) >> 1;
	if (l < m) Update(l, r, c, lson);
	if (r > m) Update(l, r, c, rson);
	return;	
}

int main()
{
	ifstream fin ("rect1.in" );
	ofstream fout("rect1.out");
	
	int A, B, N;
	fin >> A >> B >> N;
	
	X.insert(0); X.insert(B);
	int m = 0;
	for (int i = 0; i != N; ++i)
	{
		int llx, lly, urx, ury, c;
		fin >> llx >> lly >> urx >> ury >> c;
		rectline[m++] = RECTLINE(llx, urx, lly,   i + 1 , c);
		rectline[m++] = RECTLINE(llx, urx, ury, -(i + 1), c);
		X.insert(lly); X.insert(ury);
	}
	stable_sort(rectline, rectline + m);

	memset(sum, 0, sizeof(int) * (MAXC + 1));
	set<int>::iterator xit = X.begin();
	map<int ,RECTLINE> cover;
	int rindex = 0;
	while (1)
	{
		low  = *xit;
		if (++xit == X.end())
			break;
		high = *xit;

		//每一次新的扫描，则重新建立一棵树//		
		memset(col, 0, sizeof(int) * (MAXAB << 2));
		memset(cnt, 0, MAXAB << 2);
		
		//Initialization
		cnt[1] = 1; col[1] = 1; 
		sum[1] += A * (high - low); 

		//Find Cover Colors
		for (; rindex < m && rectline[rindex].h == low; ++rindex)
		{
			if (rectline[rindex].n > 0)
				cover.insert(make_pair(rectline[rindex].n, rectline[rindex]));
			else
				cover.erase(-rectline[rindex].n);
		}

		// Insert the colored segment
		for (map<int, RECTLINE>::iterator mapit = cover.begin(); mapit != cover.end(); ++mapit)
			Update(mapit->second.l, mapit->second.r, mapit->second.c, 0, A, 1);
	}

	//Ouput Result
	for (int i = 1; i != MAXC + 1; ++i)
	{
		if (sum[i] != 0)
			fout << i << " " << sum[i] << endl;
	}

	fin.close();
	fout.close();
	return 0;
}
