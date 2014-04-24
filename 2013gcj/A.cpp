#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
vector<int> a;
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<int> &f, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        read(x);
        f.push_back(x);
    }
}

void writeln(vector<int> &f)
{
    int x;
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

char ans[4][30] = {"Draw", "X won", "O won", "Game has not completed"};
int field[4][4];

int test()
{
    char c;
    bool f = false;
    for (int i = 0; i < 4; i++, scanf("%c", &c))
        for (int j = 0; j < 4; j++)
        {
            scanf("%c", &c);
            switch (c)
            {
                case 'X' :
                    field[i][j] = 1;
                    break;
                case 'O' :
                    field[i][j] = 2;
                    break;
                case 'T' :
                    field[i][j] = 3;
                    break;
                default :
                    field[i][j] = 0;
                    f = true;
                    break;
            }
        }
    scanf("%c", &c);
    int j, k;
    bool ff;
    for (int i = 0; i < 4; i++)
    {
        ff = false;
        for (j = 0, k = field[i][0] == 3 ? field[i][1] : field[i][0]; j < 4; j++)
            {
                if (field[i][j] == 3)
                    continue;
                if (field[i][j] != k || !field[i][j])
                {
                    ff = true;
                    break;
                }
            }
        if (!ff)
            return k;
    }
    for (int i = 0; i < 4; i++)
    {
        ff = false;
        for (j = 0, k = field[0][i] == 3 ? field[1][i] : field[0][i]; j < 4; j++)
            {
                if (field[j][i] == 3)
                    continue;
                if (field[j][i] != k || !field[j][i])
                {
                    ff = true;
                    break;
                }
            }
        if (!ff)
            return k;
    }
        ff = false;
        for (j = 0, k = field[0][0] == 3 ? field[1][1] : field[0][0]; j < 4; j++)
            {
                if (field[j][j] == 3)
                    continue;
                if (field[j][j] != k || !field[j][j])
                {
                    ff = true;
                    break;
                }
            }
        if (!ff)
            return k;

        ff = false;
        for (j = 0, k = field[0][3 - 0] == 3 ? field[1][3 - 1] : field[0][3 - 0]; j < 4; j++)
            {
                if (field[j][3 - j] == 3)
                    continue;
                if (field[j][3 - j] != k || !field[j][3 - j])
                {
                    ff = true;
                    break;
                }
            }
        if (!ff)
            return k;

    return f ? 3 : 0;
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.txt", "w+", stdout);
    int T;
    readln(T);
    for (int tttt = 0; tttt < T; tttt++)
    {
        printf("Case #%d: ", tttt + 1);
        printf("%s\n", ans[test()]);
    }
    return 0;
}
