#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#define ll long long
#define enter printf("\n");
#define pb push_back

using namespace std;
int INF = 1000000007;
string FILENAME = "diophantus";
string FILEINPUT = FILENAME;

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

void run()
{
    int n;
    readln(n);
    ll N = (ll) n;
    N *= N;
    int k = 2;
    for (ll i = 1; i <= n; i++)
        if (N % i == 0)
        {
            k += 2;
            if (i * i == N)
                k--;
        }
    printf("%d", k / 2);
}

int main()
{
   freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
   freopen(FILENAME.append(".out").c_str(), "w", stdout);
   int T;
   readln(T);
   for (int TT = 0; TT < T; TT++)
   {
        printf("Scenario #%d:\n", TT + 1);
        run();
        if (TT < T - 1)
            printf("\n\n");
   }
   return 0;
}
