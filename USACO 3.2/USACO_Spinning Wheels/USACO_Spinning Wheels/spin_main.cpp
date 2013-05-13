/*
ID: ryan luo
PROG: spin
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <map>
#include <vector>
using namespace std;

#define MAXS 180
#define WNUM 5

int s[5];
int w[5];
pair<int, int> wdg[5][WNUM];

int main()
{
	ifstream fin ("spin.in" );
	ofstream fout("spin.out");
	
	for (int i = 0; i != 5; ++i)
		memset(wdg[i], 0, sizeof(pair<int, int>) * WNUM);
	
	for (int i = 0; i != 5; ++i)
	{
		fin >> s[i] >> w[i];
		for (int j = 0; j != w[i]; ++j)
			fin >> wdg[i][j].first >> wdg[i][j].second;	
	}
	
	int t = 0;
	int flag = 0;
	while (!flag)
	{
		vector< pair<int, int> > vp;
		for (int i = 0; i != w[0]; ++i)
			vp.push_back(make_pair((wdg[0][i].first + s[i] * t) % 360, wdg[0][i].second));

		//every wheel
		for (int i = 1; i != 5; ++i)
		{
			int vsize = vp.size();
			if (vsize == 0)
				break;
			//every wedge
			for (int j = 0; j != w[i]; ++j)
			{
				pair<int, int> temp = wdg[i][j];
				temp.first = (temp.first + s[i] * t) % 360;

				for (int k = 0; k != vsize; ++k)
				{
					if (temp.first >= vp[k].first)
					{
						if (vp[k].second + vp[k].first >= temp.first)
						{
							int ext = vp[k].second + vp[k].first - temp.first;
							vp.push_back(make_pair(temp.first, (temp.second < ext ? temp.second : ext)));
						}

						if (temp.second + temp.first >= vp[k].first + 360)
						{
							int ext = temp.second + temp.first - vp[k].first - 360;
							vp.push_back(make_pair(vp[k].first, (vp[k].second < ext ? vp[k].second : ext)));
						}
					}
					else
					{
						if (temp.second + temp.first >= vp[k].first)
						{
							int ext = temp.second + temp.first - vp[k].first;
							vp.push_back(make_pair(vp[k].first, (vp[k].second < ext ? vp[k].second : ext)));
						}

						if (vp[k].second + vp[k].first >= temp.first + 360)
						{
							int ext = vp[k].second + vp[k].first - temp.first - 360;
							vp.push_back(make_pair(temp.first, (temp.second < ext ? temp.second : ext)));
						}
					}
				}
			}
			vp.erase(vp.begin(), vp.begin() + vsize);
		}		
		++t;
		if (!vp.empty())
			flag = 1;

		if (((s[0] * t) % 360) == ((s[1] * t) % 360) &&
			((s[1] * t) % 360) == ((s[2] * t) % 360) &&
			((s[2] * t) % 360) == ((s[3] * t) % 360) && 
			((s[3] * t) % 360) == ((s[4] * t) % 360))
			break;		
	}
	if (flag)
		fout << t - 1 << endl;
	else
		fout << "none" << endl;

	fin.close();
	fout.close();
	return 0;
}
