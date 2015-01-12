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

int g[1001][1001];
void addedge(int i, int j, int v = 1)
{
    g[i][j] = v;
    g[j][i] = v;
}

void run()
{
    int k;
    readln(k);
    if (k == 1)
    {
        printf("2\nNY\nYN\n");
        return;
    }
    if (k == 3)
    {
        printf("5\nNNYYY\nNNYYY\nYYNNN\nYYNNN\nYYNNN\n");
        return;
    }
    vi ans;
    int mx = 0;
    fori(30)
        if (1 << i & k)
            ans.pb(i),
            mx = i;
    int count = 2, last = 0, thelast;
    for (int j = ans.size() - 1; j >= 0; j--)
    {
        addedge(0, count);
        addedge(0, count + 1);
        for (int i = 0, f = 0; i < mx && !f; i++)
            for (int t = 0; t < 2; t++, count++)
                if (i < ans[j] - 1)
                    addedge(count, count + 2 - t),
                    addedge(count, count + 3 - t),
                    last = max(last, count + 2 - t);
                else
                if (j == ans.size() - 1)
                    addedge(count, 1);
                else
                    if (i < ans[j + 1] - 2)
                    {
                        if (i == 0)
                            last = max(last, count + 2);
                        addedge(count, count + 2);
                    }
                    else
                        addedge(count, thelast, j || !t || !(k % 2)),
                        f = 1;
        thelast = last;
    }
    writeln(count);
    fori(count)
    {
        forj(count)
            printf("%c", g[i][j] ? 'Y' : 'N');
        enter;
    }
}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
