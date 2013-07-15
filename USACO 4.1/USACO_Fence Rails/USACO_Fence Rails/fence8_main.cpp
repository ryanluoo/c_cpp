/*
ID: ryan luo
PROG: fence8
LANG: C++
*/

//#include <fstream>
//#include <algorithm>
//#include <set>
//using namespace std;
//ifstream fin("fence8.in");
//ofstream fout("fence8.out");
//int N,R,A[2048],Cf[60],Now[60],Pre[2048],Max,Sums,Limit,Tot;
//bool flag;
//bool Cmp(int a,int b)
//{
//	return a>b;
//}
//void Initialize()
//{
//	int i;
//	fin>>N;
//	for(i=1;i<=N;i++)
//	{
//		fin>>Cf[i];
//		Tot+=Cf[i];
//	}
//	sort(Cf+1,Cf+N+1);
//	fin>>R;
//	for(i=1;i<=R;i++)
//		fin>>A[i];
//	sort(A+1,A+R+1);
//	for(i=1;i<=R;i++)
//		if(A[i]>Cf[N])
//			break;
//	R=i-1;
//	for(i=1;i<=R;i++)
//		Pre[i]=Pre[i-1]+A[i];
//}
//
//void DFS(int pos,int Prev)
//{
//	int i,st,R=0;
//	if(Sums>Tot-Pre[Limit])
//		return;
//	if(pos>Limit)
//		flag=true;
//	if(flag)
//		return;
//	st=1;
//	if(A[Limit-pos+1]==A[Limit-pos+2])
//		st=Prev;
//	for(i=st;i<=N;i++)
//		if(A[Limit-pos+1]<=Cf[i])
//		{
//			Cf[i]-=A[Limit-pos+1];
//			if(Cf[i]<A[1])
//				Sums+=Cf[i];
//			DFS(pos+1,i);
//			if(Cf[i]<A[1])
//				Sums-=Cf[i];
//			Cf[i]+=A[Limit-pos+1];
//		}
//}
//
//int main()
//{
//	Initialize();
//
//	for(Limit=1;Limit<=R;Limit++)
//	{
//		flag=false;
//		DFS(1,1);
//		if(!flag)
//			break;
//	}
//	fout<<Limit-1<<endl;
//	fin.close();
//	fout.close();
//	return 0;
//}


#include <fstream>
#include <cstdlib>
#include <climits>
#include <map>
#include <stack>
using namespace std;

#define MAXN  50
#define MAXR  1023
#define MAXRL 128

int N, R;
int boards[MAXN], rails[MAXR], sumrails[MAXR], sumboards;
int i, j;
stack< pair<int, int> > dfsstack;
int result = 0;

int cmp (const void *a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int main()
{
	ifstream fin ("fence8.in" );
	ofstream fout("fence8.out");

	fin >> N;
	sumboards = 0;
	for (i = 0; i != N; ++i)
	{
		fin >> boards[i];
		sumboards += boards[i];
	}

	fin >> R;
	for (i = 0; i != R; ++i)
		fin >> rails[i];
	
	qsort(boards, N, sizeof(boards[0]), cmp);
	qsort( rails, R, sizeof( rails[0]), cmp);

	//initial
	sumrails[0] = rails[0];
	for (i = 1; i != R; ++i)
	{
		sumrails[i] = sumrails[i-1] + rails[i];
		if (rails[i] > boards[N-1] || sumrails[i] > sumboards)
			break;
	}
	R = i;
	//////////////////////////////////////////////
	


	fin.close();
	fout.close();
	return 0;
}