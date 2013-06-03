/*
ID: ryan luo
PROG: fence4
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <climits>
#include <list>
using namespace std;

#define MAXN 200
int N;
int xo, yo;
int x[MAXN];
int y[MAXN];

struct Point
{
	double x, y;
	Point()
	{
		x = 0;
		y = 0;
	}
	Point(double x, double y)
	{
		this->x = x;
		this->y = y;
	}
	Point(const Point& p)
	{
		this->x = p.x;
		this->y = p.y;
	}
	Point& operator=(const Point& p)
	{
		this->x = p.x;
		this->y = p.y;
		return *this;
	}
	friend bool operator==(const Point& a, const Point& b)
	{
		return (a.x == b.x && a.y == b.y);
	}
};
struct Line
{
	Point a, b;
	Line ()
	{

	}
	Line(const Line& l)
	{
		this->a = l.a;
		this->b = l.b;
	}
	Line(const Point& p1, const Point& p2)
	{
		this->a = p1;
		this->b = p2;
	}
	Line Sort()
	{
		if (this->a.x > this->b.x)
			return Line(this->b, this->a);
		else
			return *this;
	}
	Line& operator=(const Line& l)
	{
		this->a = l.a;
		this->b = l.b;
		return *this;
	}
	friend bool operator==(const Line& l1, const Line& l2)
	{
		return (l1.a == l2.a && l1.b == l2.b) || (l1.a == l2.b && l1.b == l2.a);
	}
};

Point o;
Line  f[MAXN];

double crossi, crossj;
int IsCross(Line l1, Line l2)
{
	double in = (l2.a.x - l1.a.x) * (l2.b.y - l2.a.y) - (l2.a.y - l1.a.y) * (l2.b.x - l2.a.x);
	double id = (l1.b.x - l1.a.x) * (l2.b.y - l2.a.y) - (l1.b.y - l1.a.y) * (l2.b.x - l2.a.x);	
	double jn = (l1.a.x - l2.a.x) * (l1.b.y - l1.a.y) - (l1.a.y - l2.a.y) * (l1.b.x - l1.a.x);
	double jd = (l2.b.x - l2.a.x) * (l1.b.y - l1.a.y) - (l2.b.y - l2.a.y) * (l1.b.x - l1.a.x);

	if (id == 0 || jd == 0)
		return 0;

	//i,j都是从 l1.a 和 l2.a 为起点来计算
	double i = in / id, j = jn / jd;

	//Cross Point
    crossi = i; crossj = j;

	if (i < 1 && i > 0 && j < 1 && j > 0) // 严格相交于线段中间某点
		return 1;
	else if ((i == 1 || i == 0) && (j < 1 && j > 0)) // 相交于线段AB顶点，但不是CD的顶点
		return 2;
	else if ((j == 1 || j == 0) && (i < 1 && i > 0)) // 相交于线段CD顶点，但不是AB的顶点
		return 3;
	else if ((i == 1 || i == 0) && (j == 1 || j == 0)) // 相交于线段AB，CD的顶点
		return 4;
	else
		return -1; // 不相交
}

//是否三点一线
bool IsOneL(Point a, Point b, Point o)
{
	return (a.x - o.x) * (b.y - o.y) == (a.y - o.y) * (b.x - o.x);
}

//是否平行
bool IsParallel(Line l1, Line l2)
{
    return (l1.a.x - l1.b.x) * (l2.a.y - l2.b.y) == (l1.a.y - l1.b.y) * (l2.a.x - l2.b.x);
}

bool Check (Line fence)
{
	Line fcheck = fence.Sort();
	for (int i = 0; i != N; ++i)
	{
		if (f[i] == fence || IsOneL(f[i].a, f[i].b, o))
			continue;
		Line lcheck = f[i].Sort();
		double lr = 0, rr = 0;
		int checkR = IsCross(Line(o, lcheck.a), fcheck);
		if (checkR > 1 && crossj > 0)
			lr = crossj;
		if (lr >= 1)
			continue;
		checkR = IsCross(Line(o, lcheck.b), fcheck);
		if (checkR > 1 && crossj > 0)
			rr = crossj >= 1 ? 1 : crossj;
		if(rr - lr >= 1)
			return false;
		fcheck.a = Point(fcheck.a.x + fcheck.a.x * lr, fcheck.a.y + fcheck.a.y * lr);
		fcheck.b = Point(fcheck.b.x + fcheck.b.x * rr, fcheck.b.y + fcheck.b.y * rr);
	}
	return true;
}

int main()
{
	ifstream fin ("fence4.in" );
	ofstream fout("fence4.out");

	fin >> N >> xo >> yo;
	for (int i = 0; i != N; ++i)
		fin >> x[i] >> y[i];

	o = Point(xo, yo);
	for (int i = 1; i != N; ++i)
	{
		if (i != N - 1)
			f[i-1] = Line(Point(x[i-1], y[i-1]), Point(x[i], y[i]));
		else
		{
			f[N-2] = Line(Point(x[0]  , y[0]  ), Point(x[N-1], y[N-1]));
			f[N-1] = Line(Point(x[N-2], y[N-2]), Point(x[N-1], y[N-1]));
		}
	}
	
	bool NOFENCE = false;
	for (int i = 0; i < N; ++i)
	{
		for (int j = i + 2; j < N; ++j)
		{
			if ((j+1) % N != i && 0 < IsCross(Line(Point(x[i], y[i]), Point(x[i+1], y[i+1])), Line(Point(x[j], y[j]), Point(x[j+1], y[j+1]))))
				NOFENCE = true;
		}
	}
	
	if (NOFENCE)
	{
		fout << "NOFENCE" << endl;
		fin.close();
		fout.close();
		return 0;
	}

	list<Line> result;
	for (int i = 0; i != N; ++i)
	{
		if (!IsOneL(f[i].a, f[i].b, o) && Check(f[i]))
			result.push_back(f[i]);
	}
	fout << result.size() << endl;
	for (list<Line>::iterator lit = result.begin(); lit != result.end(); ++lit)
		fout << lit->a.x << " " << lit->a.y << " " << lit->b.x  << " "  << lit->b.y  << endl;

	fin.close();
	fout.close();
	return 0;
}
