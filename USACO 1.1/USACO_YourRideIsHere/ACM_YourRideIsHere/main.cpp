/*
ID: ryan luo
PROG: ride
LANG: C++
*/

//In case it overflows.

#include <cstdio>
#include <cstring>

int main()
{
	FILE *fin  = fopen ("ride.in",  "r");
	FILE *fout = fopen ("ride.out", "w");
	char comet[7], group[7];
	fscanf (fin, "%s\n%s", comet, group);	/* the two input integers */

	int a = 1, b = 1, i;
	for(i = 0; i != strlen(comet); ++i)
		a *= (comet[i] - 'A' + 1);
	a %= 47;

	for(i = 0; i != strlen(group); ++i)
		b *= (group[i] - 'A' + 1);
	b %= 47;

	if (a == b)
		fprintf(fout, "GO\n");
	else
		fprintf(fout, "STAY\n");

	fclose(fin);
	fclose(fout);
	return 0;
}