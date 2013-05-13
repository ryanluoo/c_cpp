/*
ID: ryan luo
PROG: msquare
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <map>
using namespace std;

#define MAX 40320

unsigned short ts;
unsigned short rec[MAX+1];
char path[MAX+1];
map<unsigned int, unsigned short> dict;

unsigned int contor (unsigned int num)
{
	unsigned int r = 0;
	unsigned int f[8] = {1, 1, 2, 6, 24, 120, 720, 5040};
	bool hash[9] = {0};
	for (int i = 7; i >= 0; --i)
	{
		unsigned int quo = num / f[i];
		unsigned int rem = num % f[i];

		int less = 0;
		for (int j = 1; j != quo; ++j)
			if (!hash[j]) ++less;
		r = r * 10 + less;
		hash[less] = 1;
		num = rem;
	}
	return r;
}
int main()
{
	ifstream fin ("msquare.in" );
	ofstream fout("msquare.out");

	for (unsigned int i = 0; i != MAX; ++i)
	{
		dict.insert(make_pair(contor(i), i));
	}
	
	ts = 0;
	for (int i = 0; i != 8; ++i)
	{
		unsigned short w;
		fin >> w;
		ts = ts * 10 + w;
	}
	
	fin.close();
	fout.close();
	return 0;
}
