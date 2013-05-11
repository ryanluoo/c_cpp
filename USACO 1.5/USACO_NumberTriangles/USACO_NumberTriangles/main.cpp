/*
ID: ryan luo
PROG: numtri
LANG: C++
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

int R;
int* triangle  = NULL;
int* triangleH = NULL;

int 
findLargest(int layer, int index)
{
	if (layer == 1)
		return triangle[0];
	int startIndex  = (layer - 1) * layer / 2;
	if (triangleH[startIndex + index] != -1)
		return triangleH[startIndex + index];

	int higherStart = (layer - 1) * (layer - 2) / 2;
	int i = triangle[startIndex + index];
	int result;
	if (index == 0)
		result = i + findLargest(layer - 1, 0);
	else if (index == layer - 1)
		result = i + findLargest(layer - 1, layer - 2);
	else
	{
		int left  = i + findLargest(layer - 1, index - 1);
		int right = i + findLargest(layer - 1, index);
		result =  left > right ? left : right;
	}
	triangleH[startIndex + index] = result;
	return result;
}

int findHighest(int layer)
{
	if (layer == 1)
		return triangle[0];

	int result = 0;
	int i;
	for (i = 0; i != layer; ++i)
	{
		int x = findLargest(layer, i);
		if (x > result)
			result = x;
	}
	return result;	
}

int 
main()
{
	FILE *fin  = fopen("numtri.in" , "r");
	FILE *fout = fopen("numtri.out", "w");

	fscanf(fin, "%d", &R);
	unsigned int size = R * (R + 1) / 2;
	triangle  = (int*)malloc(sizeof(int) * size);
	triangleH = (int*)malloc(sizeof(int) * size);

	int i;
	for (i = 0; i != size; ++i)
	{
		fscanf(fin, "%d", &triangle[i]);
		triangleH[i] = -1;
	}
	
	fprintf(fout, "%d\n", findHighest(R));

	free(triangle);
	free(triangleH);
	fclose(fin);
	fclose(fout);
	return 0;
}
