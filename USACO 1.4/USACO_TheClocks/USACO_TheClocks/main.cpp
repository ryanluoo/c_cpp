/*
ID: ryan luo
PROG: clocks
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cstring>

//Declaration
enum Lable {A, B, C, D, E, F, G, H, I};
int  table[9]     = {0}; //存放需要几步能到12点
int  tableTemp[9] = {0};
char sequence[9]  = {0};
char seqBest[9]   = {0};

void 
TakeMove(int move, int time)
{
	//不可能大于3次
	if(time > 3)
		return;
	if(time == 0)
		return;
	++move;

	switch (move)
	{
	case 1: //ABDE
		tableTemp[A] = (tableTemp[A] < time) ? 4 - time + tableTemp[A] : tableTemp[A] - time;
		tableTemp[B] = (tableTemp[B] < time) ? 4 - time + tableTemp[B] : tableTemp[B] - time;
		tableTemp[D] = (tableTemp[D] < time) ? 4 - time + tableTemp[D] : tableTemp[D] - time;
		tableTemp[E] = (tableTemp[E] < time) ? 4 - time + tableTemp[E] : tableTemp[E] - time;
		break;
	case 2: //ABC
		tableTemp[A] = (tableTemp[A] < time) ? 4 - time + tableTemp[A] : tableTemp[A] - time;
		tableTemp[B] = (tableTemp[B] < time) ? 4 - time + tableTemp[B] : tableTemp[B] - time;
		tableTemp[C] = (tableTemp[C] < time) ? 4 - time + tableTemp[C] : tableTemp[C] - time;
		break;
	case 3: //BCEF
		tableTemp[B] = (tableTemp[B] < time) ? 4 - time + tableTemp[B] : tableTemp[B] - time;
		tableTemp[C] = (tableTemp[C] < time) ? 4 - time + tableTemp[C] : tableTemp[C] - time;
		tableTemp[E] = (tableTemp[E] < time) ? 4 - time + tableTemp[E] : tableTemp[E] - time;
		tableTemp[F] = (tableTemp[F] < time) ? 4 - time + tableTemp[F] : tableTemp[F] - time;
		break;
	case 4://ADG 
		tableTemp[A] = (tableTemp[A] < time) ? 4 - time + tableTemp[A] : tableTemp[A] - time;
		tableTemp[D] = (tableTemp[D] < time) ? 4 - time + tableTemp[D] : tableTemp[D] - time;
		tableTemp[G] = (tableTemp[G] < time) ? 4 - time + tableTemp[G] : tableTemp[G] - time;
		break; 
	case 5: //BDEFH 
		tableTemp[B] = (tableTemp[B] < time) ? 4 - time + tableTemp[B] : tableTemp[B] - time;
		tableTemp[D] = (tableTemp[D] < time) ? 4 - time + tableTemp[D] : tableTemp[D] - time;
		tableTemp[E] = (tableTemp[E] < time) ? 4 - time + tableTemp[E] : tableTemp[E] - time;
		tableTemp[F] = (tableTemp[F] < time) ? 4 - time + tableTemp[F] : tableTemp[F] - time;
		tableTemp[H] = (tableTemp[H] < time) ? 4 - time + tableTemp[H] : tableTemp[H] - time;
		break;
	case 6: //CFI 
		tableTemp[C] = (tableTemp[C] < time) ? 4 - time + tableTemp[C] : tableTemp[C] - time;
		tableTemp[F] = (tableTemp[F] < time) ? 4 - time + tableTemp[F] : tableTemp[F] - time;
		tableTemp[I] = (tableTemp[I] < time) ? 4 - time + tableTemp[I] : tableTemp[I] - time;
		break;
	case 7: //DEGH
		tableTemp[D] = (tableTemp[D] < time) ? 4 - time + tableTemp[D] : tableTemp[D] - time;
		tableTemp[E] = (tableTemp[E] < time) ? 4 - time + tableTemp[E] : tableTemp[E] - time;
		tableTemp[G] = (tableTemp[G] < time) ? 4 - time + tableTemp[G] : tableTemp[G] - time;
		tableTemp[H] = (tableTemp[H] < time) ? 4 - time + tableTemp[H] : tableTemp[H] - time;
		break;
	case 8: //GHI
		tableTemp[G] = (tableTemp[G] < time) ? 4 - time + tableTemp[G] : tableTemp[G] - time;
		tableTemp[H] = (tableTemp[H] < time) ? 4 - time + tableTemp[H] : tableTemp[H] - time;
		tableTemp[I] = (tableTemp[I] < time) ? 4 - time + tableTemp[I] : tableTemp[I] - time;
		break; 
	case 9: //EFHI
		tableTemp[E] = (tableTemp[E] < time) ? 4 - time + tableTemp[E] : tableTemp[E] - time;
		tableTemp[F] = (tableTemp[F] < time) ? 4 - time + tableTemp[F] : tableTemp[F] - time;
		tableTemp[H] = (tableTemp[H] < time) ? 4 - time + tableTemp[H] : tableTemp[H] - time;
		tableTemp[I] = (tableTemp[I] < time) ? 4 - time + tableTemp[I] : tableTemp[I] - time;
		break;
	default:
		break;
	}
}

void
ResetTable()
{
	int i;
	for (i = A; i != I + 1; ++i)
		tableTemp[i] = table[i];
}

int 
CheckTable()
{
	int i;
	for (i = A; i != I + 1; ++i)
		if (tableTemp[i] != 0)
			return -1;

	return 1;
}

void
ToQuanternary(int s)
{
	int i;
	for (i = 0; i != 9; ++i)
	{
		sequence[i] = s & 3;
		s = s >> 2;
	}
}

int
Compare()
{
	char unfold[27] = {0};
	char seqBestfold[27] = {0};

	int i = 0, j = 0, k = 27;
	for (i = 8; i != -1; --i)
	{
		for (j = 0; j != sequence[i]; ++j)
			unfold[--k] = i;
	}

	k = 27;
	for (i = 8; i != -1; --i)
	{
		for (j = 0; j != seqBest[i]; ++j)
			seqBestfold[--k] = i;
	}

	if (memcpy(seqBestfold, unfold, 27) >= 0)
		return 1;
	else
		return -1;
}


int 
main()
{
	FILE *fin  = fopen("clocks.in" , "r");
	FILE *fout = fopen("clocks.out", "w");
	
	int i, j;
	for (i = A; i != I + 1; ++i)
	{		
		int temp;
		fscanf(fin, "%d", &temp);
		table[i] = (12 - temp) / 3;
	}

	for (i = 0; i != 262144; ++i)
	{
		ResetTable();
		ToQuanternary(i);
		for (j = 0; j != 9; ++j)
			TakeMove(j, sequence[j]);
		if (CheckTable() == 1 && Compare() != -1)
			memcpy(seqBest, sequence, 9);
	}

	int k = 0;
	char c[27] = {0};
	for (i = 0; i != 9; ++i)
		for (j = 0; j != seqBest[i]; ++j)
			c[k++] = i + 1;

	fprintf(fout, "%d", c[0]);
	for (i = 1; i != k; ++i)
		fprintf(fout, " %d", c[i]);
	fprintf(fout, "\n");

	fclose(fin);
	fclose(fout);
	return 0;
}
