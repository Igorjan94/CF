#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
const int pos[] = {128, 192, 224, 240, 248, 252, 254, 255};
int a[100001][4], ans[4];
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

int main()
{
 //  freopen("input.txt", "r", stdin);
    int n, k;
    readln(n, k);
    for (int i = 0; i < n; i++)
        scanf("%d.%d.%d.%d\n", &a[i][0], &a[i][1], &a[i][2], &a[i][3]);
    int c = 0;
    int j = 0;
    ans[c] = pos[j];
    ans[1] = 0;
    ans[2] = 0;
    ans[3] = 0;
    set< pair< pair<int, int>, pair<int, int> > > se;
    while (true)
    {
        se.clear();
        for (int i = 0; i < n; i++)
            se.insert(make_pair(make_pair(a[i][0] & ans[0], a[i][1] & ans[1]),
                               make_pair(a[i][2] & ans[2], a[i][3] & ans[3])));
        if (se.size() > k)
        {
            printf("-1\n");
            return 0;
        }
        if (se.size() == k)
        {
            printf("%d.%d.%d.%d\n", ans[0], ans[1], ans[2], ans[3]);
            return 0;
        }
        if (j == 7)
            c++,
            j = 0;
        ans[c] = pos[++j];
    }
   return 0;
}
