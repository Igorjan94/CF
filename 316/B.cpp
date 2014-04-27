#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
vector<int> a, c;
vector<bool> b;
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<int> &f, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        read(x);
        a[x] = i;
    }
}

void writeln(vector<int> &f)
{
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

int main()
{
   freopen("input.txt", "r", stdin);
   int n, m;
   readln(n, m);
   a.resize(n + 1, 0);
   b.resize(n + 1, false);
   readln(a, n);
   a[0] = 0;
   writeln(a);
   for (int i = 1; i <= n; i++)
        if (!b[i])
        {
            int counter = 0;
            int s = i;
            while (a[s] != 0)
            {
                b[s] = true;
                s = a[s];
                counter++;
            }
            if (counter)
            c.push_back(counter);
        }
    writeln(c);
   return 0;
}
