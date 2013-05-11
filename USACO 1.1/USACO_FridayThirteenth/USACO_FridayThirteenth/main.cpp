/*
ID: ryan luo
PROG: friday
LANG: C++
*/

#include <cstdio>
#define LASTTIME  2    // 1899-12-13 falls on Wed.
#define STARTYEAR 1900

enum Week {Mon = 0, Tue, Wed, Thu, Fri, Sat, Sun};
enum DaysOfMonth {Jan = 0, Feb, Mar, Apr, May, Jun, Jul, Aug, Sept, Oct, Nov, Dec};

int DaysOfLastMonth(int year, int month)
{
	int dayNum = 31;
	switch (month)
	{	
	case May: case Jul: case Oct: case Dec:
		dayNum = 30;
		break;
	case Mar:
		if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0))
			dayNum = 29;
		else
			dayNum = 28;
		break;
	default:
		dayNum = 31;
		break;
	}
	return dayNum;
}

int FallOnWhich(int lastTime, int dayNum)
{
	int thisTime = 0;
	thisTime = (lastTime + dayNum % 7) % 7;
	return thisTime; 
}

int main()
{	
	FILE *fin  = fopen("friday.in" , "r");
	FILE *fout = fopen("friday.out", "w");	
	int N;
	fscanf(fin, "%d", &N);
	int frequnce[7] = {0};

	int i;
	int j;
	int lastTime = LASTTIME; 
	for (i = 0; i != N; ++i)
	{
		for (j = 0; j != 12; ++j)
		{
			lastTime = FallOnWhich(lastTime, DaysOfLastMonth(STARTYEAR + i, j));
			++frequnce[lastTime];
		}
	}
		
	fprintf(fout, "%d %d %d %d %d %d %d", frequnce[5], frequnce[6], frequnce[0], frequnce[1], frequnce[2], frequnce[3], frequnce[4]);
	fprintf(fout, "\n");

	fclose(fin);
	fclose(fout);
	return 0;
}