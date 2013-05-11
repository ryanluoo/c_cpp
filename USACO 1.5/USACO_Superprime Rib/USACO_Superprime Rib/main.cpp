/*
ID: ryan luo
PROG: sprime
LANG: C++
*/

#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

char DecidePrime (int a)
{
	char below[25] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
	int i = 0;
	for (i = 0; i != 25; ++i)
	{
		if (a == below[i])
			return 1;
		if (a % below[i] == 0)
			return -1;
	}

	if (a <= 100)
		return -1;

	int line = pow(a, 0.5);
	for (i = 101; i <= line; i = i + 2)
	{
		if (a % i == 0)
			return -1;
	}
	return 1;
}

int main()
{
	FILE *fin  = fopen("sprime.in" , "r");
	FILE *fout = fopen("sprime.out", "w");
	
	int N;
	fscanf(fin, "%d", &N);
	vector<int> sp;

	sp.push_back(2);
	sp.push_back(3);
	sp.push_back(5);
	sp.push_back(7);

	int n;
	for (n = 0; n != N - 1; ++n)
	{
		vector<int> temp;

		for (vector<int>::iterator vi = sp.begin(); vi != sp.end(); ++vi)
		{
			int i = *vi;

			if (DecidePrime(i * 10 + 1) != -1)
				temp.push_back(i * 10 + 1);
			if (DecidePrime(i * 10 + 3) != -1)
				temp.push_back(i * 10 + 3);
			if (DecidePrime(i * 10 + 5) != -1)
				temp.push_back(i * 10 + 5);
			if (DecidePrime(i * 10 + 7) != -1)
				temp.push_back(i * 10 + 7);
			if (DecidePrime(i * 10 + 9) != -1)
				temp.push_back(i * 10 + 9);
		}
		sp = temp;
	}
	
	for (vector<int>::iterator i = sp.begin(); i != sp.end(); ++i)
		fprintf(fout, "%d\n", *i);

	fclose(fin);
	fclose(fout);
	return 0;
}
