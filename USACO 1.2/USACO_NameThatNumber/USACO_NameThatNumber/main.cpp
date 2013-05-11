/*
ID: ryan luo
PROG: namenum
LANG: C++
*/

#include <cstdio>
#include <cstring>

int main()
{
	FILE *fin  = fopen("namenum.in" , "r");
	FILE *fout = fopen("namenum.out", "w");

	FILE *dict = fopen("dict.txt", "r");
	char keypad[8][3] = {{'A','B','C'}, {'D','E','F'}, {'G','H','I'},
						 {'J','K','L'}, {'M','N','O'}, {'P','R','S'},
						 {'T','U','V'}, {'W','X','Y'}};
	char num[13], buf[13];
	fscanf(fin, "%s", num);	
	fscanf(dict, "%s", buf);
	for (; buf[0] != keypad[num[0] - '2'][0];fscanf(dict, "%s", buf));

	int i;
	char none = 1;
	while (!feof(dict) &&  buf[0] != keypad[num[0] - '2' + 1][0])
	{
		char t = 1;
		if (strlen(buf) != strlen(num))
		{
			fscanf(dict, "%s", buf);
			continue;
		}

		for (i = 0; i != strlen(num); ++i)
		{
			if(buf[i] != keypad[num[i] - '2'][0] &&
			   buf[i] != keypad[num[i] - '2'][1] &&
			   buf[i] != keypad[num[i] - '2'][2])
			{
			   t = 0;
			   break;
			}
		}

		if (t == 1)
		{
			none = 0;
			fprintf(fout, "%s\n", buf);
		}

		 fscanf(dict, "%s", buf);
	}

	if (none == 1)
		fprintf(fout, "NONE\n");

	fclose(fin);
	fclose(fout);
	fclose(dict);
	return 0;
}
