/*
ID: ryan luo
PROG: fence4
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <climits>
#include <cmath>
#include <list>
using namespace std;

#define MAXN 200
#define MINDIFF 1e-6
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
		return (fabs(a.x - b.x) < MINDIFF && fabs(a.y - b.y) < MINDIFF);
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
		bool b1 = (l1.a == l2.a && l1.b == l2.b);
		bool b2 = (l1.a == l2.b && l1.b == l2.a);
		bool b = b1 || b2;
		return b;
	}
	friend bool operator!=(const Line& l1, const Line& l2)
	{
		return !(l1 == l2);
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

Point Mid (Point a, Point b)
{
	return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
}

bool Check (Line fence, int num)
{
	//if (pow(fence.a.x - fence.b.x, 2) + pow(fence.a.y - fence.b.y, 2) < MINDIFF)
	if (fence.a == fence.b)
		return false;

	Line oa(o, fence.a);
	Line ob(o, fence.b);
	bool seena = true, seenb = true;

	for (int i = 0; i != N; ++i)
	{
		bool oasee = true;	bool obsee = true;
		if (i == num)
			continue;
		if (IsCross(oa, f[i]) > 0) 
			oasee = false;
		if (IsCross(ob, f[i]) > 0)
			obsee = false;
		if (!oasee && !obsee)
			return false;
		seena &= oasee;
		seenb &= obsee;
	}
	if (seena || seenb)
		return true;

	Point mid = Mid(fence.a, fence.b);
	Line newl = Line(fence.a, mid);
	if (Check(newl, num)) 
		return true;
	newl = Line(mid, fence.b);
	if (Check(newl, num))
		return true;
	return false;
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
			if ((j+1) % N != i && 0 < IsCross(Line(Point(x[i], y[i]), Point(x[(i+1)%N], y[(i+1)%N])), Line(Point(x[j], y[j]), Point(x[(j+1)%N], y[(j+1)%N]))))
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
		if (!IsOneL(f[i].a, f[i].b, o) && Check(f[i], i))
			result.push_back(f[i]);
	}
	fout << result.size() << endl;
	for (list<Line>::iterator lit = result.begin(); lit != result.end(); ++lit)
		fout << lit->a.x << " " << lit->a.y << " " << lit->b.x  << " "  << lit->b.y  << endl;

	fin.close();
	fout.close();
	return 0;
}
