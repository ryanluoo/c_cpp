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
		return a.x == b.x && a.y == b.y;
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
	Line& operator=(const Line& l)
	{
		this->a = l.a;
		this->b = l.b;
		return *this;
	}
};

double crossi, crossj;
int IsCross(Point a, Point b, Point c, Point d)
{
	// Line1 : (ax, ay), (bx, by)
	// Line2 : (cx, cy), (dx, dy)
	double in = (c.x - a.x) * (d.y - c.y) - (c.y - a.y) * (d.x - c.x);
	double id = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);	
	double jn = (a.x - c.x) * (b.y - a.y) - (a.y - c.y) * (b.x - a.x);
	double jd = (d.x - c.x) * (b.y - a.y) - (d.y - c.y) * (b.x - a.x);

	if (id == 0 || jd == 0)
		return 0;

	double i = in / id, j = jn / jd;
	//Cross Point
    crossi = i; crossj = j;

	if (i < 1 && i > 0 && j < 1 && j > 0) // 严格相交于线段中间某点
		return 1;
	//else if ((i == 1 || i == 0) && (j < 1 && j > 0)) // 相交于线段AB顶点，但不是CD的顶点
	//	return -1;
	//else if ((j == 1 || j == 0) && (i < 1 && i > 0)) // 相交于线段CD顶点，但不是AB的顶点
	//	return -2;
	//else if ((i == 1 || i == 0) && (j == 1 || j == 0)) // 相交于线段AB，CD的顶点
	//	return -3;
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
	for (int i = 0; i != N; ++i)
	{
		double ratioi, ratioi_1;
		int cresult = IsCross(Point(xo, yo), Point(x[i], y[i]), fence.a, fence.b));
		if (cresult != 0 || crossi < 1)
			
	}
}
int main()
{
	ifstream fin ("fence4.in" );
	ofstream fout("fence4.out");

	fin >> N >> xo >> yo;
	for (int i = 0; i != N; ++i)
		fin >> x[i] >> y[i];

	bool NOFENCE = false;
	for (int i = 0; i < N; ++i)
	{
		for (int j = i + 2; j < N; ++j)
		{
			if ((j+1)%N == i)
				continue;
			if (IsCross(Point(x[i], y[i]), Point(x[(i+1)%N], y[(i+1)%N]),
						Point(x[j], y[j]), Point(x[(j+1)%N], y[(j+1)%N])) == 1)
				NOFENCE = true;
		}
	}

	list<Line> result;
	//Observe
	for (int i = 1; i < N; ++i)
	{
		if (i != N - 1)
		{
			if (!IsOneL(Point(x[i-1], y[i-1]), Point(x[i], y[i]), Point(xo, yo)) && Check(Line(Point(x[i-1], y[i-1]), Point(x[i], y[i]))))
				result.push_back(Line(Point(x[i-1], y[i-1]), Point(x[i], y[i])));
		}
		else
		{
			if (!IsOneL(Point(x[0], y[0]), Point(x[N-1], y[N-1]), Point(xo, yo)) && Check(Line(Point(x[0], y[0]), Point(x[N-1], y[N-1]))))
				result.push_back(Line(Point(x[0], y[0]), Point(x[N-1], y[N-1])));
			if (!IsOneL(Point(x[N-2], y[N-2]), Point(x[N-1], y[N-1]), Point(xo, yo)) && Check(Line(Point(x[N-2], y[N-2]), Point(x[N-1], y[N-1]))))
				result.push_back(Line(Point(x[N-2], y[N-2]), Point(x[N-1], y[N-1])));
		}
	}

	if (NOFENCE)
		fout << "NOFENCE" << endl;
	else
	{
		fout << result.size() << endl;
		for (list<Line>::iterator lit = result.begin(); lit != result.end(); ++lit)
			fout << lit->a.x << " " << lit->a.y << " " << lit->b.x << " " << lit->b.y << endl;
	}

	fin.close();
	fout.close();
	return 0;
}
