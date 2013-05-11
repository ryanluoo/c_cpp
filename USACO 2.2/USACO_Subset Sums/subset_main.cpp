/*
ID: ryan luo
PROG: subset
LANG: C++
*/

#include <fstream>
using namespace std;

unsigned planNum[40][391] = {0};

unsigned MaxPartitions(int n)
{
    
    planNum[1][1] = 1;
    planNum[1][0] = 1;
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 0; j <= i * (i + 1) / 2; ++j)
        {
            if (i > j)
                planNum[i][j] = planNum[i-1][j];
            else
                planNum[i][j] = planNum[i-1][j] + planNum[i-1][j - i];  
        }
    }
    return planNum[n][n*(n+1)/4] / 2;
}

int main() {
    ifstream fin ("subset.in" );
    ofstream fout("subset.out");
    
    int N;
    fin >> N;
    
    int sum = N * (1 + N) / 2;
    
    if (sum % 2 == 1)
        fout << "0" << endl;
    else
        fout << MaxPartitions(N) << endl;
     
    fin.close();
    fout.close();
    return 0;
}

