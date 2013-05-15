/*
ID: ryan luo
PROG: prefix
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>
using namespace std;

ifstream fin ("prefix.in" );
ofstream fout("prefix.out");
int main()
{	
	
	string s1 = "AB";
	string s2 = "B";
	if (s1 > s2 + "A")
		fout << "TRUE";
	else
		fout << "FALSE";

	fin.close();
	fout.close();
	return 0;
}
