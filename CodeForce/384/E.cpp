#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#define enter printf("\n")
#define pb push_back
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define forn1(i, n) for (int i = 1; i < n; i++)
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>

using namespace std;
int INF = 1000000007;
string FILENAME = "input";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}
    int n, m;
    vi edges(200001), diff(200001);
    vector<short> a(200001);
    bool cha = false;

int get(int u, int depth = 1)
{
    return diff[u] * depth + (u && cha ? get(edges[u], -depth) : 0);
}

void run()
{
    readln(n, m);
    int u, v, x;
    fori(n)
        scanf("%d", &a[i]);
    fori(n - 1)
        readln(u, v),
        edges[v - 1] = u - 1;
    int prev = -1, pv = -1;
    fori(m)
    {
        read(x);
        if (x == 1)
        {
            prev = -1;
            cha = true;
            readln(u, v);
            diff[u - 1] += v;
        }
        else
        {
            readln(u);
            if (prev == u)
            {
                writeln(pv);
            }
            else
            {
                prev = u;
                writeln(pv = get(u - 1) + a[u - 1]);
            }
        }
    }
}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
