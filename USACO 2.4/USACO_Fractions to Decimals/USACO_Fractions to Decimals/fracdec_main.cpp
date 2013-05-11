/*
ID: ryan luo
PROG: fracdec
LANG: C++
*/

#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
using namespace std;


int main()
{
	ifstream fin ("fracdec.in" );
	ofstream fout("fracdec.out");
	
	int N, D;
	fin >> N >> D;

	int  rec[100000];
	fill(rec, rec + 100000, -1);
	string result;
	ldiv_t r = ldiv(N, D);

	stringstream ss;
	ss << r.quot;
	result += ss.str();
	result.push_back('.');
	rec[r.rem] = result.size();

	while (1)
	{
		r = ldiv(r.rem * 10, D);
		result.push_back(r.quot + '0');
		if (r.rem == 0)
			break;
		if(rec[r.rem] != -1)
		{
			result.insert(result.begin() + rec[r.rem], '(');
			result.push_back(')');
			break;
		}
		else
			rec[r.rem] = result.size();
	}

	size_t i = 0;
	for (i = 0; i + 75 < result.size(); i += 76)
		fout << string(result.begin() + i, result.begin() + i + 76) << endl;
	fout << string(result.begin() + i, result.end()) << endl;
	
	fin.close();
	fout.close();
	return 0;
}
