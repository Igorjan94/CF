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
int n, m;
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
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

int main()
{
//    freopen("input.txt", "r", stdin);
    int t;
    readln(t);
    for (int tt = 0; tt < t; tt++)
    {
        char c, d;
        int start = 0, finish = 0;
        scanf("%c%c", &c, &d);
        start += 60 * 60 * ((c - '0') * 10 + d - '0');
        scanf(":");
        scanf("%c%c", &c, &d);
        start += 60 * ((c - '0') * 10 + d - '0');
        scanf(":");
        scanf("%c%c", &c, &d);
        start += ((c - '0') * 10 + d - '0');
        scanf(" ");
        scanf("%c%c", &c, &d);
        finish += 60 * 60 * ((c - '0') * 10 + d - '0');
        scanf(":");
        scanf("%c%c", &c, &d);
        finish += 60 * ((c - '0') * 10 + d - '0');
        scanf(":");
        scanf("%c%c", &c, &d);
        finish += ((c - '0') * 10 + d - '0');
        readln(m);
        m *= 60;
        int time = (finish - start + 24 * 60 * 60) % (24 * 60 * 60);
        if (time == 0)
            time = 60 * 60 * 24;
        if (time >= m)
            printf("Perfect\n"); else
            if (time >= m - 60 * 60)
                printf("Test\n"); else
                printf("Fail\n");
    }
   return 0;
}
