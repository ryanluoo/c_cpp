/*
ID: ryan luo
PROG: preface
LANG: C++
*/

#include <fstream>
#include <iostream>
using namespace std;

enum RecordIndex {i, v, x, l, c, d, m};

typedef struct
{
    int n[7];
} RomanNum;

RomanNum record[3][10];
char resultt[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
int result[7] = {0};
void ini()
{
    for (int k = 0; k != 10; ++k)
    {
        switch(k)
        {
            case 1:
            case 2:
            case 3:
                record[0][k].n[i] = k;
                break;
            
            case 4:
            case 6:
                record[0][k].n[i] = 1;
                record[0][k].n[v] = 1;
                break;
                
            case 5:
                record[0][k].n[v] = 1;
                break;
            case 7:
                record[0][k].n[i] = 2;
                record[0][k].n[v] = 1;
                break;
            case 8:
                record[0][k].n[i] = 3;
                record[0][k].n[v] = 1;
                break;
            case 9:
                record[0][k].n[i] = 1;
                record[0][k].n[x] = 1;
                break;
            default:
                break;
        }
    }

    for (int k = 0; k != 10; ++k)
    {
        switch(k)
        {
            case 3:
            case 1:
            case 2:
                record[1][k].n[x] = k;
                break;
            
            case 4:
            case 6:
                record[1][k].n[x] = 1;
                record[1][k].n[l] = 1;
                break;
                
            case 5:
                record[1][k].n[l] = 1;
                break;
            case 7:
                record[1][k].n[x] = 2;
                record[1][k].n[l] = 1;
                break;
            case 8:
                record[1][k].n[x] = 3;
                record[1][k].n[l] = 1;
                break;
            case 9:
                record[1][k].n[x] = 1;
                record[1][k].n[c] = 1;
                break;
            default:
                break;
        }
    }
    
    for (int k = 0; k != 10; ++k)
    {
        switch(k)
        {
            case 3:
            case 1:
            case 2:
                record[2][k].n[c] = k;
                break;
            
            case 4:
            case 6:
                record[2][k].n[c] = 1;
                record[2][k].n[d] = 1;
                break;
                
            case 5:
                record[2][k].n[d] = 1;
                break;
            case 7:
                record[2][k].n[c] = 2;
                record[2][k].n[d] = 1;
                break;
            case 8:
                record[2][k].n[c] = 3;
                record[2][k].n[d] = 1;
                break;
            case 9:
                record[2][k].n[c] = 1;
                record[2][k].n[m] = 1;
                break;
            default:
                break;
        }
    }
}

void add(RomanNum rn)
{
    for (int k = 0; k != 7; ++k)
        result[k] += rn.n[k];
}

int main() {
    ifstream fin ("preface.in" );
    ofstream fout("preface.out");
    
    int N;
    fin >> N;

    ini();
    
    for (int kk = 1; kk <= N; ++kk)
    {
        int k = kk;
        int temp = k % 10;
        add(record[0][temp]);
        
        
        k = k / 10;
        if (k == 0)
            continue;        
        temp = k % 10;
        add (record[1][temp]);
        
        
        k = k / 10;
        if (k == 0)
            continue;
        temp = k % 10;
        add (record[2][temp]);
        
        
         k = k / 10;
        if (k == 0)
            continue;
        temp = k % 10;
        result[m] += temp;
        
    }
  
    for (int k = 0; k != 7; ++k)
        if(result[k] != 0)
            fout << resultt[k] << " " << result[k] << endl;
    
    fin.close();
    fout.close();
    return 0;
}

