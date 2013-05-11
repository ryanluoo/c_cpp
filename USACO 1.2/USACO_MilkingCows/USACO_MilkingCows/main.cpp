/*
ID: ryan luo
PROG: milk2
LANG: C++
*/

#include <cstdio>
#include <cstdlib>

typedef struct Interval {int up; int down; Interval* nextInterval;};

int main()
{	
	FILE *fin  = fopen("milk2.in" , "r");
	FILE *fout = fopen("milk2.out", "w");	

	int N;
	fscanf(fin, "%d", &N);
	
	Interval* firstInterval = (Interval*) malloc(sizeof(Interval));
	firstInterval->down = 0;
	firstInterval->up   = 0;
	firstInterval->nextInterval = NULL;

	Interval* current;
	//Interval* lastInterval = firstInterval;
	Interval* dIterator = firstInterval;
	Interval* dLastIter = NULL;
	Interval* uIterator = firstInterval;
	Interval* uLastIter = NULL;

	int i;
	for (i = 0; i != N; ++i)
	{
		current = (Interval*) malloc(sizeof(Interval));		
		fscanf(fin, "%d %d", &(current->down), &(current->up));
		current->nextInterval = NULL;

		dIterator = firstInterval->nextInterval;
		dLastIter = firstInterval;
		while (dIterator != NULL)
		{
			if(current->down > dIterator->up)
			{
				dLastIter = dIterator;
				dIterator = dIterator->nextInterval;
			}
			else
				break;
		}

		uIterator = dIterator;
		uLastIter = dLastIter;
		while (uIterator != NULL)
		{
			if (current->up >= uIterator->down)
			{
				uLastIter = uIterator;
				uIterator = uIterator->nextInterval;
			}
			else
				break;
		}
		
		if (dIterator == NULL)
		{
			//add to the END.
			dLastIter->nextInterval = current;
		}
		else
		{
			if (current->down > dIterator->down)
				current->down = dIterator->down;
			if (current->up < uLastIter->up)
				current->up = uLastIter->up;
			dLastIter->nextInterval = current;
			dLastIter->nextInterval->nextInterval = uIterator;

			//free the useless node
			current = dIterator;
			while (dIterator != uIterator)
			{
				dIterator = dIterator->nextInterval;
				free(current);
				current = dIterator;
			}			
		}
	}
	
	for (current = firstInterval->nextInterval; current != NULL; current = current->nextInterval)
	{
		printf("%d %d\n", current->down, current->up);
	}

	int maxConti = 0, maxIdle = 0, lastUp = firstInterval->nextInterval->up;
	for (current = firstInterval->nextInterval; current != NULL; current = current->nextInterval)
	{
		if (current->up - current->down > maxConti)
			maxConti = current->up - current->down;
		if (current->down - lastUp > maxIdle)
			maxIdle = current->down - lastUp;
		lastUp = current->up;
	}

	fprintf(fout, "%d %d\n", maxConti, maxIdle);

	current = firstInterval;
	while (firstInterval != NULL)
	{
		firstInterval = firstInterval->nextInterval;
		free(current); // if the last node is freed, the last node's nextInterval is unknown.
		current = firstInterval;
	}	

	fclose(fin);
	fclose(fout);
	return 0;
}