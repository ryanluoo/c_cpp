/*
ID: ryan luo
PROG: heritage
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <string>
using namespace std;

ifstream fin ("heritage.in" );
ofstream fout("heritage.out");

string inorder;
string preorder;

void PrintTree(string preo, string ino)
{	
	if (preo.empty())
		return;
	if (preo.size() == 1)
	{
		fout << preo;
		return;
	}

	string leftpre , leftin ;
	string rightpre, rightin;

	int index = ino.find(preo[0]);
	leftin = string(ino.begin(), ino.begin() + index);
	rightin = string(ino.begin() + index + 1, ino.end());

	index = preo.find_first_not_of(leftin, 1);
	index = index == -1 ? preo.size() : index;
	leftpre = string(preo.begin() + 1, preo.begin() + index);
	rightpre = string(preo.begin() + index, preo.end());

	PrintTree(leftpre, leftin);
	PrintTree(rightpre, rightin);
	fout << preo[0];
}

int main()
{
	fin >> inorder >> preorder;

	PrintTree(preorder, inorder);
	//PrintTree("GH", "HG");
	fout << endl;

	fin.close();
	fout.close();
	return 0;
}
