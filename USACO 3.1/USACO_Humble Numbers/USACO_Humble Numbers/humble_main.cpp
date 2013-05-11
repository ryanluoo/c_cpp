/*
ID: ryan luo
PROG: humble
LANG: C++
*/

#include <iostream>
#include <queue>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>
#include <climits>
using namespace std;

priority_queue<int> q;
vector<int> s;
set<int> vised;
int k;

void dfs(long long a, int n)
{
	if(a != 1 && vised.find(a) == vised.end())
	{
		if(q.size() < k || a < q.top())
		{
			vised.insert(a);
			q.push(a);
		}
		if(q.size() > k)
			q.pop();
	}

	if(n == s.size()) return ;

	while(a < INT_MAX)
	{
		if(q.size() == k && a > q.top()) break;
		dfs(a, n + 1);
		a *= s[n];
	}
}

int main()
{
	int n;
	freopen("humble.in", "r", stdin);
	freopen("humble.out", "w", stdout);

	cin >> n >> k;
	for(int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		s.push_back(a);
	}
	dfs(1, 0);
	cout << q.top() << endl;

	return 0;
}
