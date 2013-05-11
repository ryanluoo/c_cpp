/*
ID: ryan luo
PROG: lamps
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <bitset>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#define Even     0
#define Odd		 1
#define Even3K_1 2
#define Odd3K_1  3

int main() {
    ifstream fin ("lamps.in" );
    ofstream fout("lamps.out");
	int N, C;
	fin >> N >> C;
	bitset<101> b1, b2, b3, b4;
	for (int i = 1; i != 101; ++i)
	{
		b1.set(i);
		if (i % 2)
			b2.set(i);
		else
			b3.set(i);
		
		if (i % 3 == 1)
			b4.set(i);
	}

	char classify[101];
	bitset<16> group[4];
	// if make the group is ON!!! Even.
	for (int i = 0; i != 16; ++i)
	{
		char c1 = (i & 0x08) ? 1 : 0; // button 1
		char c2 = (i & 0x04) ? 1 : 0; // button 2
		char c3 = (i & 0x02) ? 1 : 0; // button 3
		char c4 = (i & 0x01) ? 1 : 0; // button 4
		
		// odd
		if ((c1 + c2) % 2 == 0)
			group[Odd].set(i);
		// even
		if ((c1 + c3) % 2 == 0)
			group[Even].set(i);
		// odd 3k+1
		if ((c1 + c2 + c4) % 2 == 0)
			group[Odd3K_1].set(i);
		// even 3k+1
		if ((c1 + c3 + c4) % 2 == 0)
			group[Even3K_1].set(i);
	}
	//
	//for (int k = 0; k != 4; ++k)
	//	fout << group[k].to_string() << endl;
	
	//classify
	for (int i = 1; i != N + 1; ++i)
	{
		int c = 0;
		if (i % 2 == 0)
			c = 0;
		else
			c = 1;
		if (i % 3 == 1)
			c |= 2;
		classify[i] = c;
	}

	int i;
	fin >> i;
	bitset<16> onType(0xffff);
	int visited[4] = {0};
	while(i != -1) // even
	{
		if (!visited[classify[i]])
		{
			onType &= group[classify[i]];
			visited[classify[i]] = 1;
		}
		fin >> i;
	}
	fin >> i;
	int v[4] = {0};
	while(i != -1) // odd
	{
		if(!v[classify[i]])
		{
			onType &= (~group[classify[i]]);
			v[classify[i]] = 1;
		}
		fin >> i;
	}
	
	//get result
	list<string> result;
	for (int i = 0; i != 16; ++i)
	{
		bitset<101> r(0);
		if (onType[i] && bitset<4>(i).count() <= C)
		{
			char c1 = (i & 0x08) ? 1 : 0; // button 1
			char c2 = (i & 0x04) ? 1 : 0; // button 2
			char c3 = (i & 0x02) ? 1 : 0; // button 3
			char c4 = (i & 0x01) ? 1 : 0; // button 4

			if (c1)
				r ^= b1;
			if (c2)
				r ^= b2;
			if (c3)
				r ^= b3;
			if (c4)
				r ^= b4;

			result.push_back((~r).to_string());
		}
	}

	vector<string> resultt;
	for(list<string>::iterator i = result.begin(); i != result.end(); ++i)
	{
		string s;
		for (int k = 0; k != N; ++k)
			s.push_back((*i)[99 - k]);
		resultt.push_back(s);
	}

	sort(resultt.begin(), resultt.end());
	string s;
	for(vector<string>::iterator i = resultt.begin(); i != resultt.end(); ++i)
	{		
		if (*i != s)
			fout << *i << endl;
		s = *i;
	}
	if (resultt.empty())
		fout << "IMPOSSIBLE" << endl;

    fin.close();
    fout.close();
    return 0;
}

