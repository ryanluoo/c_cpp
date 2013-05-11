/*
ID: ryan luo
PROG: packrec
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <climits>

typedef struct Solution 
{
	int p;
	int q;
	Solution* ptr;
};
//ver, hor
int rec[4][2]  = {0};
int recT[4][2] = {0};
Solution *s   = NULL;
int hor = 0, ver = 0, area = INT_MAX;

void FreeSolutions()
{
	Solution* temp = s;
	Solution* now  = s;
	while (now != NULL)
	{
		now = temp->ptr;
		free(temp);
		temp = now;
	}
}
void InsertSolution(int p, int q)
{
	Solution *end = s;
	Solution *now = s;
	if (p >= q)
	{
		int x = p;
		p = q;
		q = x;
	}

	if (s == NULL)
	{
		s      = (Solution*)malloc(sizeof(Solution));
		s->p   = p;
		s->q   = q;
		s->ptr = NULL;
	}
	else
	{
		while (end != NULL && end->p < p)
		{
			now = end;
			end = end->ptr;			
		}
		if (end != NULL && end->p == p)
			return;

		if (now->p < p)
		{
			now->ptr		  = (Solution*)malloc(sizeof(Solution));
			now->ptr->p   = p;
			now->ptr->q   = q;
			now->ptr->ptr = end;
		}
		else if (now->p > p) // first node
		{
			s	   = (Solution*)malloc(sizeof(Solution));
			s->p   = p;
			s->q   = q;
			s->ptr = now;
		}
	}
}
void PrintSolutions(FILE* fout)
{
	Solution* now = s;
	while (now != NULL)
	{
		fprintf(fout, "%d %d\n", now->p, now->q);
		now = now->ptr;
	}
}
int SearchMax(int a, int b, int c, int d)
{
	if (a >= b && a >= c && a >= d)
		return a;
	if (b >= a && b >= c && b >= d)
		return b;
	if (c >= a && c >= b && c >= d)
		return c;
	return d;
}
void Rotate(int i)
{
	if (i & 8)
	{
		recT[0][0] = rec[0][1];
		recT[0][1] = rec[0][0];
	}
	else
	{
		recT[0][0] = rec[0][0];
		recT[0][1] = rec[0][1];
	}

	if (i & 4)
	{
		recT[1][0] = rec[1][1];
		recT[1][1] = rec[1][0];
	}
	else
	{
		recT[1][0] = rec[1][0];
		recT[1][1] = rec[1][1];
	}

	if (i & 2)
	{
		recT[2][0] = rec[2][1];
		recT[2][1] = rec[2][0];
	}
	else
	{
		recT[2][0] = rec[2][0];
		recT[2][1] = rec[2][1];
	}

	if (i & 1)
	{
		recT[3][0] = rec[3][1];
		recT[3][1] = rec[3][0];
	}
	else
	{
		recT[3][0] = rec[3][0];
		recT[3][1] = rec[3][1];
	}
}

int main()
{
	FILE *fin  = fopen("packrec.in" , "r");
	FILE *fout = fopen("packrec.out", "w");
		
	int i;
	for (i = 0; i != 4; ++i)
		fscanf(fin, "%d %d", &rec[i][0], &rec[i][1]);


	for (i = 0; i != 16; ++i)
	{
		Rotate(i);

		//1st.
		hor = recT[0][1] + recT[1][1] + recT[2][1] + recT[3][1];
		ver = SearchMax(recT[0][0], recT[1][0], recT[2][0], recT[3][0]);
		if (hor * ver < area)
		{
			FreeSolutions();
			s = NULL;
			InsertSolution(hor, ver);
			area = hor * ver;
		}
		else if (hor * ver == area)
			InsertSolution(hor, ver);

		//2nd.
		int j = 0, k = 0, m = 0;
		for (j = 0; j != 4; ++j)
		{
			int recThree[3][2] = {0};

			m = 0;
			for (k = 0; k != 4; ++k)
			{
				if (k == j)
					continue;
				recThree[m][0] = recT[k][0];
				recThree[m][1] = recT[k][1];
				++m;
			}
			
			int horTop = recThree[0][1] +  recThree[1][1] +  recThree[2][1];
			int verTop = SearchMax(recThree[0][0], recThree[1][0], recThree[2][0], 0);
			hor = horTop >= recT[j][1] ? horTop : recT[j][1];
			ver = verTop + recT[j][0];
			if (hor * ver < area)
			{
				FreeSolutions();
				s = NULL;
				InsertSolution(hor, ver);
				area = hor * ver;
			}
			else if (hor * ver == area)
				InsertSolution(hor, ver);
		}

		//3rd.4th.5th.
		int n = 0;
		for (j = 0; j != 4; ++j)
		{
			int recThree[3][2] = {0};
			m = 0;
			for (k = 0; k != 4; ++k)
			{
				if (k == j)
					continue;
				recThree[m][0] = recT[k][0];
				recThree[m][1] = recT[k][1];
				++m;
			}
			

			for (k = 0; k != 3; ++k)
			{
				int recTwo[2][2] = {0};
				n = 0;
				for (m = 0; m != 3; ++m)
				{
					if (m == k)
						continue;
					recTwo[n][0] = recThree[m][0];
					recTwo[n][1] = recThree[m][1];
					++n;
				}

				//3rd
				int verTwoTogether = recTwo[0][0] > recTwo[1][0] ? recTwo[0][0] : recTwo[1][0];
				int horTwoTogether = recTwo[0][1] + recTwo[1][1];
				int verLeft = verTwoTogether + recThree[k][0];
				int horLeft = horTwoTogether > recThree[k][1] ? horTwoTogether : recThree[k][1];
				ver = verLeft > recT[j][0] ? verLeft : recT[j][0];
				hor = horLeft + recT[j][1];
				if (hor * ver < area)
				{
					FreeSolutions();
					s = NULL;
					InsertSolution(hor, ver);
					area = hor * ver;
				}
				else if (hor * ver == area)
					InsertSolution(hor, ver);

				//4th, 5th
				horLeft = recTwo[0][1] > recTwo[1][1] ? recTwo[0][1] : recTwo[1][1];
				verLeft = recTwo[0][0] + recTwo[1][0];
				hor = horLeft + recT[j][1] + recThree[k][1];
				ver = SearchMax(verLeft, recT[j][0], recThree[k][0], 0);
				if (hor * ver < area)
				{
					FreeSolutions();
					s = NULL;
					InsertSolution(hor, ver);
					area = hor * ver;
				}
				else if (hor * ver == area)
					InsertSolution(hor, ver);

				//6th
				int horLeftDown = recT[j][1] + recThree[k][1];
				int verLeftDown;
				int vTaller, hTaller, vShorter, hShorter;
				if (recT[j][0] > recThree[k][0])
				{
					verLeftDown = recT[j][0];
					vTaller = recT[j][0];
					hTaller = recT[j][1];
					vShorter = recThree[k][0];
					hShorter = recThree[k][1];
				}
				else
				{
					verLeftDown = recThree[k][0];
					vShorter = recT[j][0];
					hShorter = recT[j][1];
					vTaller = recThree[k][0];
					hTaller = recThree[k][1];			
				}
				
				//first recTwo[0]
				if (recTwo[0][1] > hTaller)
				{
					if (recTwo[1][0] <= (vTaller - vShorter))
					{
						ver = verLeftDown + recTwo[0][0];
						int h1 = hTaller + recTwo[1][1];
						hor = h1 > horLeftDown ? h1 : horLeftDown;
						hor = hor > recTwo[0][1] ? hor : recTwo[0][1];
					}
					else
					{
						if (recTwo[0][1] < horLeftDown)
						{
							int v1 = recTwo[1][0] + vShorter;
							int v2 = recTwo[0][0] + vTaller;
							ver = v1 > v2 ? v1 : v2;
						}
						else
						{
							int v1 = recTwo[0][0] + vTaller;
							int v2 = recTwo[1][0];
							ver = v1 > v2 ? v1 : v2;
						}
						int h1 = recTwo[0][1] + recTwo[1][1];
						hor = h1 > horLeftDown ? h1 : horLeftDown;
					}
				}
				else
				{
					int v1 = vTaller  + recTwo[0][0];
					int v2 = vShorter + recTwo[1][0];
					ver = v1 > v2 ? v1 : v2;
					int h1 = hTaller + recTwo[1][1];
					hor = h1 > horLeftDown ? h1 : horLeftDown;
				}
				if (hor * ver < area)
				{
					FreeSolutions();
					s = NULL;
					InsertSolution(hor, ver);
					area = hor * ver;
				}
				else if (hor * ver == area)
					InsertSolution(hor, ver);


				//first recTwo[1]
				if (recTwo[1][1] > hTaller)
				{
					if (recTwo[0][0] <= (vTaller - vShorter))
					{
						ver = verLeftDown + recTwo[1][0];
						int h1 = hTaller + recTwo[0][1];
						hor = h1 > horLeftDown ? h1 : horLeftDown;
						hor = hor > recTwo[1][1] ? hor : recTwo[1][1];
					}
					else
					{
						if (recTwo[1][1] < horLeftDown)
						{
							int v1 = recTwo[0][0] + vShorter;
							int v2 = recTwo[1][0] + vTaller;
							ver = v1 > v2 ? v1 : v2;
						}
						else
						{
							int v1 = recTwo[1][0] + vTaller;
							int v2 = recTwo[0][0];
							ver = v1 > v2 ? v1 : v2;
						}
						int h1 = recTwo[1][1] + recTwo[0][1];
						hor = h1 > horLeftDown ? h1 : horLeftDown;
					}
				}
				else
				{
					int v1 = vTaller  + recTwo[1][0];
					int v2 = vShorter + recTwo[0][0];
					ver = v1 > v2 ? v1 : v2;
					int h1 = hTaller + recTwo[0][1];
					hor = h1 > horLeftDown ? h1 : horLeftDown;
				}
				if (hor * ver < area)
				{
					FreeSolutions();
					s = NULL;
					InsertSolution(hor, ver);
					area = hor * ver;
				}
				else if (hor * ver == area)
					InsertSolution(hor, ver);
			}
		}		
	}

	fprintf(fout, "%d\n", area);
	PrintSolutions(fout);

	FreeSolutions();
    fclose(fin);
	fclose(fout);
	return 0;
}
