/*
ID: ryan luo
PROG: pprime
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

char DecidePrimePrime (int a)
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
	FILE *fin  = fopen("pprime.in" , "r");
	FILE *fout = fopen("pprime.out", "w");

	int a, b;
	fscanf(fin, "%d %d", &a, &b);
	
	int i;
	//首先生成所有的回文
	//1
	if (a < 10 && b >= 5)
	{
		for (i = a; i < 10 && i <= b; ++i)
			if (DecidePrimePrime(i) != -1)
				fprintf(fout, "%d\n", i);
	}

	//2
	if (a < 100 && b >= 10)
	{
		for (i = 11; i <= 99; i += 11)
		{
			if (i > b)
				break;
			if (i < a)
				continue;
			if (DecidePrimePrime(i) != -1)
				fprintf(fout, "%d\n", i);
 		}			
	}

	//3
	if (a < 1000 && b >= 100)
	{
		char c1, c2;
		for (c1 = 1; c1 <= 9; ++c1)
			for (c2 = 0; c2 <= 9; ++c2)
			{
				i = c1 * 101 + c2 * 10;
				if (i > b)
					break;
				if (i < a)
					continue;
				if (DecidePrimePrime(i) != -1)
					fprintf(fout, "%d\n", i);
			}
	}

	//4
	if (a < 10000 && b >= 1000)
	{
		char c1, c2;
		for (c1 = 1; c1 <= 9; ++c1)
			for (c2 = 0; c2 <= 9; ++c2)
			{
				i = c1 * 1001 + c2 * 110;
				if (i > b)
					break;
				if (i < a)
					continue;
				if (DecidePrimePrime(i) != -1)
					fprintf(fout, "%d\n", i);
			}
	}

	//5
	if (a < 100000 && b >= 10000)
	{
		char c1, c2, c3;
		for (c1 = 1; c1 <= 9; ++c1)
			for (c2 = 0; c2 <= 9; ++c2)
				for (c3 = 0; c3 <= 9; ++c3)
				{
					i = c1 * 10001 + c2 * 1010 + c3 * 100;
					if (i > b)
						break;
					if (i < a)
						continue;
					if (DecidePrimePrime(i) != -1)
						fprintf(fout, "%d\n", i);
				}
	}

	//6
	if (a < 1000000 && b >= 100000)
	{
		char c1, c2, c3;
		for (c1 = 1; c1 <= 9; ++c1)
			for (c2 = 0; c2 <= 9; ++c2)
				for (c3 = 0; c3 <= 9; ++c3)
				{
					i = c1 * 100001 + c2 * 10010 + c3 * 1100;
					if (i > b)
						break;
					if (i < a)
						continue;
					if (DecidePrimePrime(i) != -1)
						fprintf(fout, "%d\n", i);
				}
	}

	//7
	if (a < 10000000 && b >= 1000000)
	{
		char c1, c2, c3, c4;
		for (c1 = 1; c1 <= 9; ++c1)
			for (c2 = 0; c2 <= 9; ++c2)
				for (c3 = 0; c3 <= 9; ++c3)
					for (c4 = 0; c4 <= 9; ++c4)
				{
					i = c1 * 1000001 + c2 * 100010 + c3 * 10100 + c4 * 1000;
					if (i > b)
						break;
					if (i < a)
						continue;
					if (DecidePrimePrime(i) != -1)
						fprintf(fout, "%d\n", i);
				}
	}

	//8
	if (a < 100000000 && b >= 10000000)
	{
		char c1, c2, c3, c4;
		for (c1 = 1; c1 <= 9; ++c1)
			for (c2 = 0; c2 <= 9; ++c2)
				for (c3 = 0; c3 <= 9; ++c3)
					for (c4 = 0; c4 <= 9; ++c4)
					{
						i = c1 * 10000001 + c2 * 1000010 + c3 * 100100 + c4 * 1100;
						if (i > b)
							break;
						if (i < a)
							continue;
						if (DecidePrimePrime(i) != -1)
							fprintf(fout, "%d\n", i);
					}
	}

	fclose(fin);
	fclose(fout);
	return 0;
}
