/*
ID: ryan luo
PROG: gift1
LANG: C++
*/

//w may be treated as r or b.
#include <cstdio>
#include <cstdlib>
#include <cstring>

typedef struct {char name[15]; int account;} GiftGiver;
GiftGiver * group;
int NP;
void AddAccount(char*, int);

int main()
{	
	FILE *fin  = fopen("gift1.in" , "r");
	FILE *fout = fopen("gift1.out", "w");
	
	fscanf(fin, "%d", &NP);
	group = (GiftGiver*)malloc(sizeof(GiftGiver) * NP);

	int i;
	for (i = 0; i != NP; ++i)
	{
		fscanf(fin, "%s", group[i].name);
		group[i].account = 0;
	}

	
	while (!feof(fin))
	{
		int iniAccount = 0, NGi = 0;
		char name[15];
		fscanf(fin, "%s %d %d", name, &iniAccount, &NGi);
		int gift = (NGi == 0) ? 0 : iniAccount / NGi;
		AddAccount(name, 0 - iniAccount);
		AddAccount(name, iniAccount - gift * NGi);

		int i;
		for (i = 0; i != NGi; ++i)
		{
			fscanf(fin, "%s", name);
			AddAccount(name, gift);
		}
	}
	
	free(group);
	fclose(fin);
	fclose(fout);
	return 0;
}

void AddAccount(char* name, int leftNum)
{
	int i;
	for (i = 0; i != NP; ++i)
	{
		if (strlen(group[i].name) == strlen(name) && !strcmp(group[i].name, name))
		{
			group[i].account += leftNum;
			return;
		}
	}
	return;
}