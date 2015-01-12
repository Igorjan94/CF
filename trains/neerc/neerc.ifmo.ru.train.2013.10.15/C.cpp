#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <queue>

#define enter printf("\n");
#define pb push_back
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>

using namespace std;
int INF = 1000000007;
string FILENAME = "matching";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

void run()
{
    double x;
    cin >> x;
    int deg[10];
    deg[0] = 1;
    if (x >= 10.0)
    {
        printf("No solution\n");
        return;
    }
    for (int i = 1; i <= 9; i++)
        deg[i] = deg[i - 1] * 10;
    double eps = 0.000000001;
    int count = 0;
    if (abs(x - 1.0) < eps)
        for (int i = 1; i <= 9; i++)
            printf("%d\n", i);
    for (int k = 1; k <= 7; k++)
        for (int a = 1; a <= 9; a++)
        {
            double ans = ((x * deg[k] - 1) * a) / (10 - x);
            if (abs(ans - round(ans)) < eps && (ans) < deg[k])
                printf("%d%d\n", a, (int) round(ans)),
                count++;
        }
    if (!count)
        printf("No solution\n");
}

int main()
{
 //   freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
//    freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
