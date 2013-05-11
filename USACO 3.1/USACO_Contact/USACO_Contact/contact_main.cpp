/*
ID: ryan luo
PROG: contact
LANG: C++
*/

#include <fstream>
#include <algorithm>
#include <bitset>
#include <string>
#include <map>
#include <vector>
#include <cstring>
using namespace std;

#define MAXN  50
#define MAXAB 12
#define MAXC  200000

string seq;
int hz[2][1 << MAXAB];
map<int, vector< pair<int, int> > > result;

int main()
{
	ifstream fin ("contact.in" );
	ofstream fout("contact.out");
	
	int A, B, N;
	fin >> A >> B >> N;

	while (!fin.eof())
	{
		char c = fin.get();
		if (c == '1' || c == '0')
			seq.push_back(c);
	}
	memset(hz[0], 0, sizeof(int) * (1 << MAXAB));
	memset(hz[1], 0, sizeof(int) * (1 << MAXAB));

	//Process
	size_t i = 0;
	while (i + B <= seq.size())
	{
		string s(seq.begin() + i, seq.begin() + i + B);
		bitset<MAXAB> temp(s);
		++hz[0][temp.to_ulong()];
		++i;
	}

	int now = 0; int nowSize = 1 << B;
	for (int j = B; j >= A; --j)
	{
		//Process Now
		for (int k = nowSize - 1; k >= 0; --k)
		{
			int freq = hz[now][k];
			if (freq == 0)
				continue;
			map<int, vector< pair<int, int> > >::iterator rit = result.find(freq);
			if (rit == result.end())
			{
				vector< pair<int, int> > temp;
				temp.push_back(make_pair(j, k));
				result.insert(make_pair(freq, temp));
				if (result.size() > N)
					result.erase(result.begin());
			}
			else
			{
				rit->second.push_back(make_pair(j, k));
			}
		}

		if (j == A)
			break;

		//Create Next
		int next = now ^ 1;
		memset(hz[next], 0, sizeof(int) * (1 << MAXAB));
		for (int k = 0; k != nowSize; ++k)
		{
			hz[next][k >> 1] += hz[now][k];
		}
		//Create Remainder
		if (i + j - 1 <= seq.size())
		{
			string s(seq.begin() + i, seq.end());
			bitset<MAXAB> temp(s);
			++hz[next][temp.to_ulong()];
			++i;
		}		

		nowSize = 1 << j;
		now = next;
	}
	
	for (map<int, vector< pair<int, int> > >::reverse_iterator mit = result.rbegin(); mit != result.rend(); ++mit)
	{
		fout << mit->first << endl;
		int vit = mit->second.size() - 1;
		vector< pair<int, int> > temp = mit->second;
		for (; vit >= 0; --vit)
		{
			int second = temp[vit].second;
			string s;
			int x = 1;
			for (int j = 0; j != temp[vit].first; ++j)
			{
				if ((second & x) == 0)
					s = "0" + s;
				else
					s = "1" + s;
				x = x << 1;
			}
			fout << s << ((temp.size() - vit) % 6 == 0 || vit == 0 ? "\n" : " ");
		}
	}
	fin.close();
	fout.close();
	return 0;
}
