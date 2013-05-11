/*
ID: ryan luo
PROG: hamming
LANG: C++
*/

#include <fstream>
using namespace std;

#define MAX 256

int main()
{	
    ifstream fin ("hamming.in" );
    ofstream fout("hamming.out");

    int N, B, D;
    char table[MAX][MAX] = {0};
    fin >> N >> B >> D;

    //preprocess
    for (int i = 0; i != 1 << B; ++i)
    {
        for (int j = 0; j != 1 << B; ++j)
        {
            int xr = i ^ j;
            xr = (xr & 0x55555555) + ((xr >>  1) & 0x55555555);
            xr = (xr & 0x33333333) + ((xr >>  2) & 0x33333333);
            xr = (xr & 0x0f0f0f0f) + ((xr >>  4) & 0x0f0f0f0f);
            xr = (xr & 0x00ff00ff) + ((xr >>  8) & 0x00ff00ff);
            xr = (xr & 0x0000ffff) + ((xr >> 16) & 0x0000ffff);
            table[i][j] = xr;
        }
    }

    int record[MAX] = {0};
    int num = 0;
    record[num++] = 0;

    for (int i = 0; i != 1 << B; ++i)
    {
        if (num >= N)
            break;
        int flag = 1;
        for (int k = 0; k != num; ++k)
        {
            if (table[i][record[k]] < D)
            {
                flag = 0;
                break;
            }
        }
        if (flag)
            record[num++] = i;
        else
            continue;
    }

    fout << record[0] << " ";
    for (int i = 1; i != num - 1; ++i)
        fout << record[i] << ((i + 1) % 10 == 0 ? "\n" : " ");
    fout << record[num - 1] << endl;


    fin.close();
    fout.close();
    return 0;
}
