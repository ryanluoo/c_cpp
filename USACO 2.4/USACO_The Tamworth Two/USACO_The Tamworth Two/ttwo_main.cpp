/*
ID: ryan luo
PROG: ttwo
LANG: C++
*/

#include <fstream>
#include <cstring>
#include <map>
using namespace std;

class Pair : public pair<int, int>
{
public:
	friend Pair operator+(Pair p1, Pair p2)
	{
		Pair temp;
		temp.first  = p1.first + p2.first;
		temp.second = p1.second+ p2.second;
		return temp;
	}
	Pair operator+=(Pair p)
	{
		this->first  += p.first;
		this->second += p.second;
		return *this;
	}

	Pair operator=(Pair p)
	{
		this->first  = p.first;
		this->second = p.second;
		return *this;
	}

	Pair()
	{
		this->first = 0;
		this->second = 0;
	}

	Pair(pair<int, int> p)
	{
		this->first  = p.first;
		this->second = p.second;
	}

};

int main()
{
	ifstream fin ("ttwo.in" );
	ofstream fout("ttwo.out");

	char grid[12][12];
	Pair farmer;
	Pair cow;

	memset(grid[ 0], '*', 12);
	memset(grid[11], '*', 12);		
	for (int i = 1; i != 11; ++i)
	{
		fin.getline(&grid[i][1], 11);
		for (int j = 1; j != 11; ++j)
			if (grid[i][j] == 'F')
				farmer = make_pair(i, j);
			else if (grid[i][j] == 'C')
				cow = make_pair(i, j);
		grid[i][0] = grid[i][11] = '*';
	}
	
	Pair directf[4] = {make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0), make_pair(0, -1)};
	Pair directc[4] = {make_pair(-1, 0), make_pair(0, 1), make_pair(1, 0), make_pair(0, -1)};
	int dfIndex = 0, dcIndex = 0;

	if (farmer == cow)
	{
		fout << "0" <<endl;
	}
	else
	{
		int step = 0;
		int flagf = 0;
		int flagc = 0;
		while (1)
		{
			if (farmer == cow)
			{
				fout << step << endl;
				break;
			}
			++step;
			Pair temp = farmer + directf[dfIndex];
			if (grid[temp.first][temp.second] == '*')
				++dfIndex %= 4;
			else
				farmer = temp;
			
			temp = cow + directc[dcIndex];
			if (grid[temp.first][temp.second] == '*')
				++dcIndex %= 4;
			else
				cow = temp;
				
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//���˿��Ǹ�������ѭ������Ҫ���������λ��
			//����NOCOW�ϵ���ʾ��
			//״ֻ̬��(10*10*4)400�֣����������(400*400)160000�֣�
			//Ҳ����˵���������160000������ô�϶�������е�״̬������
			//2�����ϣ���ô�Ϳ϶���һ����ѭ������Զ��������.
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			/*if (flagf && flagc)
			{
				fout << "0" << endl;
				break;
			}*/
			if (step >= 160000)
			{
				fout << "0" << endl;
				break;
			}
		}
	}
	
	fin.close();
	fout.close();
	return 0;
}
