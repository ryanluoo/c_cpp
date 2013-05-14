/*
ID: ryan luo
PROG: msquare
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <map>
#include <set>
#include <string>
#include <cstdlib>
using namespace std;

#define MAX 40320
#define LEN 8

int seq;
//unsigned short rec[MAX+1];
//char path[MAX+1];
map< int, pair<int, string> > dict;
set<int> rec;

//Trans
int A(int s)
{
	//char c[LEN];
	int re = 0;
	div_t r = div(s, 10);
	int w = 10000000;
	for (int i = LEN - 1; i >= 0; --i)
	{
		re += r.rem * w;
		w /= 10;
		r = div(r.quot, 10);
	}
	return re;
}
int _A(int s)
{
	return A(s);
}

int B(int s)
{
	div_t r = div(s, 10000);
	div_t h = div(r.quot, 10);
	div_t l = div(r.rem, 1000);
	return h.rem * 10000000 + h.quot * 10000 + l.rem * 10 + l.quot;
}
int _B(int s)
{
	div_t r = div(s, 10000);
	div_t h = div(r.quot, 1000);
	div_t l = div(r.rem, 10);
	return h.rem * 100000 + h.quot * 10000 + l.rem * 1000 + l.quot;
}

int C(int s)
{
	div_t r = div(s, 10);
	int w_0 = r.rem;
	r = div(r.quot, 100);
	int w_1 = r.rem;
	r = div(r.quot, 100);
	int w_3 = r.rem;
	r = div(r.quot, 100);
	int w_5 = r.rem;
	int w_7 = r.quot;	
	r = div(w_1, 10);
	w_1 = r.rem;
	int w_2 = r.quot;
	r = div(w_5, 10);
	w_5 = r.rem;
	int w_6 = r.quot;

	return w_7 * 10000000 + w_1 * 1000000 + w_6 * 100000 + w_3 * 1000 + w_5 * 100 + w_2 * 10 + w_0;

}
int _C(int s)
{
	div_t r = div(s, 10);
	int w_0 = r.rem;
	r = div(r.quot, 100);
	int w_1 = r.rem;
	r = div(r.quot, 100);
	int w_3 = r.rem;
	r = div(r.quot, 100);
	int w_5 = r.rem;
	int w_7 = r.quot;	
	r = div(w_1, 10);
	w_1 = r.rem;
	int w_2 = r.quot;
	r = div(w_5, 10);
	w_5 = r.rem;
	int w_6 = r.quot;

	return w_7 * 10000000 + w_5 * 1000000 + w_2 * 100000 + w_3 * 1000 + w_1 * 100 + w_6 * 10 + w_0;
}

/////////////////////////////////////////////////
//// Delete
/////////////////////////////////////////////////
unsigned int contor (unsigned int num)
{
	unsigned int r = 0;
	unsigned int f[8] = {1, 1, 2, 6, 24, 120, 720, 5040};
	bool hash[8] = {0};
	for (int i = 7; i >= 0; --i)
	{
		unsigned int quo = num / f[i];
		unsigned int rem = num % f[i];

		for (int j = 0; j <= quo; ++j)
		{
			if (hash[j]) ++quo;
		}
		hash[quo] = true;
		r = r * 10 + quo + 1;		
		num = rem;
	}
	return r;
}

int main()
{
	ifstream fin ("msquare.in" );
	ofstream fout("msquare.out");

	//Can't
	/*for (unsigned int i = 0; i != MAX; ++i)	
		dict.insert(make_pair(contor(i), i));*/
		
	seq = 0;
	for (int i = 0; i != 8; ++i)
	{
		short w;
		fin >> w;
		seq = seq * 10 + w;
	}

	dict.insert(make_pair(12345678, make_pair(0,  "")));
	rec.insert(12345678);
	/*dict.insert(make_pair(87654321, make_pair(1, "A")));
	dict.insert(make_pair(41236785, make_pair(1, "B")));
	dict.insert(make_pair(17245368, make_pair(1, "C")));*/
	while (1)
	{
		map< int, pair<int, string> > newdict;
		for (map< int, pair<int, string> >::iterator mit = dict.begin(); mit != dict.end(); ++mit)
		{
			int n;
			map< int, pair<int, string> >::iterator fr;

			n = A(mit->first);
			if (rec.find(n) == rec.end())
			{
				fr = newdict.find(n);
				if (fr == newdict.end() || fr->second.second > mit->second.second + "A")
					newdict[n] = make_pair(mit->second.first + 1, mit->second.second + "A");
			}			

			n = B(mit->first);
			if (rec.find(n) == rec.end())
			{
				fr = newdict.find(n);
				if (fr == newdict.end() || fr->second.second > mit->second.second + "B")
					newdict[n] = make_pair(mit->second.first + 1, mit->second.second + "B");
			}

			n = C(mit->first);
			if (rec.find(n) == rec.end())
			{
				fr = newdict.find(n);
				if (fr == newdict.end() || fr->second.second > mit->second.second + "C")
					newdict[n] = make_pair(mit->second.first + 1, mit->second.second + "C");
			}
		}

		if (dict.find(seq) != dict.end())
			break;
		for (map< int, pair<int, string> >::iterator mit = newdict.begin(); mit != newdict.end(); rec.insert(mit->first), ++mit);
		dict = newdict;
	}
	
	fout << dict[seq].first << endl << dict[seq].second << endl;
	
	fin.close();
	fout.close();
	return 0;
}
