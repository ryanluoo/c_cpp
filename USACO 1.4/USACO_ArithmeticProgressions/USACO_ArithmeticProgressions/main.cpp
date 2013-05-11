/*
ID: ryan luo
PROG: ariprog
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;


int 
main()
{
	char* bisquares;

	FILE *fin  = fopen("ariprog.in" , "r");
	FILE *fout = fopen("ariprog.out", "w");
	vector <pair<int, int> > re;
	int len, bound;
	fscanf(fin, "%d %d", &len, &bound);
	int size = bound * bound * 2;
	bisquares = (char*) malloc(sizeof(char) * size + 1);

	
	int i = 0, j = 0, num = 0;
	for (i = 0; i != size + 1; ++i)
		bisquares[i] = 0;

	for (i = 0; i != bound + 1; ++i)
		for (j = i; j != bound + 1; ++j)
			bisquares[i * i + j * j] = 1;
	
	int none = 1;
	int a, b;
	for (a = 0; a != size + 1; ++a)
	{		
		if (bisquares[a] == 0)
			continue;
		for (b = 1; b != bound * bound + 1; ++b)
		{
			int n, of = 0, accept = 1;
			if (a + b * (len - 1) > size)
				break;
			for (n = 1; n != len; ++n)
			{
				int m = a + b * n;

				if (m > size)
				{
					of = 1;
				}
				else if (m <= size && bisquares[a + n * b] == 0)
				{
					if (m == size)
						of = 1;
					accept = 0;
					break;
				}				
			}

			if (of == 1)
				break;
			if (accept == 1)
			{
				none = 0;
				re.push_back(make_pair(b, a));
			}
		}
	}

	if (none == 1)
		fprintf(fout, "NONE\n");
	else
	{
		sort(re.begin(),re.end());
		for(int i = 0; i != re.size(); ++i)
		{
			fprintf(fout, "%d %d\n", re[i].second, re[i].first);
		}
	}

	free(bisquares);

	fclose(fin);
	fclose(fout);
	return 0;
}
