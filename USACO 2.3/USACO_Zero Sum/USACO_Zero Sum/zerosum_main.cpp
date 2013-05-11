/*
ID: ryan luo
PROG: zerosum
LANG: C++
*/

#include <fstream>
#include <string>
using namespace std;

ifstream fin ("zerosum.in" );
ofstream fout("zerosum.out");

int N;

int Cal(string s)
{
	int result = 0;
	int c = s[s.size()-1] - '0';
	int w = 10;
	for (int i = s.size() - 2; i > 0; i -= 2)
	{
		if (s[i] == ' ')
		{
			c = c + (s[i-1] - '0') * w;
			w *= 10;
		}
		else if (s[i] == '-')
		{
			result -= c;
			w = 10;
			c = s[i-1] - '0';
		}
		else if (s[i] == '+')
		{
			result += c;
			w = 10;
			c = s[i-1] - '0';
		}
	}
	return result+c;
}

void GetResult(string current, int pos)
{
	if (pos >= 2 * N - 1)
	{
		if (Cal(current) == 0)
			fout << current << endl;
		return;
	}
	
	// ' '
	char c = '0' + (pos+3)/2;
	string s = current+" ";
	s.push_back(c);
	GetResult(s, pos+2);

	// '+'
	c = '0' + (pos+3)/2;
	s = current+"+";
	s.push_back(c);
	GetResult(s, pos+2);

	// '-'
	c = '0' + (pos+3)/2;
	s = current+"-";
	s.push_back(c);
	GetResult(s, pos+2);
}

int main()
{
	

	fin >> N;

	GetResult("1", 1);

	fin.close();
	fout.close();
	return 0;
}
