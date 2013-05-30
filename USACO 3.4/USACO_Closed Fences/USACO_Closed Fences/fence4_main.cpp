/*
ID: ryan luo
PROG: fence4
LANG: C++
*/

#include <fstream>
#include <cstring>
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

Point cp;
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
	cp.x = a.x + i * (b.x - a.x);
	cp.y = a.y + i * (b.y - a.y);

	if (i < 1 && i > 0 && j < 1 && j > 0) // 严格相交于线段中间某点
		return 1;
	else if ((i == 1 || i == 0) && (j < 1 && j > 0)) // 相交于线段AB顶点，但不是CD的顶点
		return -1;
	else if ((j == 1 || j == 0) && (i < 1 && i > 0)) // 相交于线段CD顶点，但不是AB的顶点
		return -2;
	else if ((i == 1 || i == 0) && (j == 1 || j == 0)) // 相交于线段AB，CD的顶点
		return -3;
	else
		return 0; // 严格不相交
}

bool IsOneL(Point a, Point b, Point o)
{
	return (a.x - o.x) * (b.y - o.y) == (a.y - o.y) * (b.x - o.x);
}

int main()
{
	ifstream fin ("fence4.in" );
	ofstream fout("fence4.out");

	fin >> N >> xo >> yo;
	for (int i = 0; i != N; ++i)
	{
		fin >> x[i] >> y[i];
	}

	bool NOFENCE = false;
	for (int i = 0; i < N; ++i)
	{
		for (int j = i + 2; j < N; ++j)
		{
			if ((j+1)%N == i)
				continue;
			if (IsCross(Point(x[i], y[i]), Point(x[(i+1)%N], y[(i+1)%N]),
						Point(x[j], y[j]), Point(x[(j+1)%N], y[(j+1)%N])) != 0)
				NOFENCE = true;
		}
	}

	list<Line> result;
	//Observe
	for (int i = 1; i < N; ++i)
	{
		bool seen = true;
		if (IsOneL(Point(x[i-1], y[i-1]), Point(x[i], y[i]), Point(xo, yo)))
			seen = false;

		double x1 = x[i-1], y1 = y[i-1];
		double x2 = x[i],   y2 = y[i];

		for (int j = 0; j < N; ++j)
		{
			bool seeni = true, seeni_1 = true;
			if (i - 1 == j)
				continue;
			if (0 != IsCross(Point(xo, yo), Point(x[i],   y[i]),   Point(x[j], y[j]), Point(x[(j+1)%N], y[(j+1)%N])))
				seeni = false;
			if (0 != IsCross(Point(xo, yo), Point(x[i-1], y[i-1]), Point(x[j], y[j]), Point(x[(j+1)%N], y[(j+1)%N])))
				seeni_1 = false;
			if (!seeni && !seeni_1)
				seen = false;
		}
		if (seen)
			result.push_back(Line(Point(x[i-1], y[i-1]), Point(x[i], y[i])));
	}
	//last point
	bool seen = true;
	if (IsOneL(Point(x[0], y[0]), Point(x[N-1], y[N-1]), Point(xo, yo)))
		seen = false;
	for (int j = 0; j < N; ++j)
	{
		bool seeni = true, seeni_1 = true;
		if (N - 1 == j)
			continue;
		if (0 != IsCross(Point(xo, yo), Point(x[0],   y[0]),   Point(x[j], y[j]), Point(x[(j+1)%N], y[(j+1)%N])))
			seeni = false;
		if (0 != IsCross(Point(xo, yo), Point(x[N-1], y[N-1]), Point(x[j], y[j]), Point(x[(j+1)%N], y[(j+1)%N])))
			seeni_1 = false;
		if (!seeni && !seeni_1)
			seen = false;
	}
	if (seen)
	{
		if (result.back().b == Point(x[N-1], y[N-1]))
		{
			Line l = result.back();
			result.pop_back();
			result.push_back(Line(Point(x[0], y[0]), Point(x[N-1], y[N-1])));
			result.push_back(l);
		}
		else
			result.push_back(Line(Point(x[0], y[0]), Point(x[N-1], y[N-1])));
		
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
