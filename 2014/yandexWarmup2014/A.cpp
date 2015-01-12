#include <bits/stdc++.h>

#define pb push_back
#define ll long long
#define forit(it, r) for (auto it = r.begin(); it != r.end(); it++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define forn1(i, n) for (int i = 1; i < n; i++)
#define fori(n) for (int i = 0; i < n; i++)
#define forj(n) for (int j = 0; j < n; j++)
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>
#ifndef ONLINE_JUDGE
#define lld I64d
#endif
#define FILENAME "input"
#define INF 1000000007

using namespace std;

template <class Head, class... Tail> void writeln(Head head, Tail... tail);
template <class Head, class... Tail> void readln(Head& head, Tail&... tail);
void writeln(){printf("\n");}void readln(){}
struct graph{vector<vector<int>> edges;int n;graph(int);graph(int, int);graph();void createGraph(int);void add_edge(int, int);void add_or_edge(int, int);void writelnMatrix();void writeln();};

///----------------------------------------------------------------------------------------------------------------------------

int n, m, k;
int field[11][11];

void run()
{
    char c, d, space, wx, wy, wtx, wty;
    readln(c, d, space);
    fori(10)
        forj(10)
            if (i == 0 || j == 0 || i == 9 || j == 9)
                field[i][j] = 1;
    field[c - 'a' + 1][d - '0'] = 1;
    wx = c -'a'+ 1;
    wy = d -'0';
    readln(c, d, space);
    field[c - 'a' + 1][d - '0'] = 2;
    wtx = c -'a'+ 1;
    wty = d -'0';
    readln(c, d);
    field[c - 'a' + 1][d - '0'] = 3;
    c = c - 'a' + 1;
    d = d - '0';
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
            if (field[wx + dx][wy + dy] == 3)
            {
                writeln("Strange");
                return;
            }
            else
                field[wx + dx][wy + dy] = 1;
    bool check = false;

    for (int dx = wtx + 1; dx <= 9; dx++)
        if (field[dx][wty] == 3)
            check = true;
        else
            if (dx == wx && wty == wy)
                break;
            else
                field[dx][wty] = 1;
    for (int dx = wtx - 1; dx >= 0; dx--)
        if (field[dx][wty] == 3)
            check = true;
        else
            if (dx == wx && wty == wy)
                break;
            else
                field[dx][wty] = 1;
    for (int dx = wty - 1; dx >= 0; dx--)
        if (field[wtx][dx] == 3)
            check = true;
        else
            if (wtx == wx && wy == dx)
                break;
            else
                field[wtx][dx] = 1;
    for (int dx = wty + 1; dx <= 9; dx++)
        if (field[wtx][dx] == 3)
            check = true;
        else
            if (wtx == wx && wy == dx)
                break;
            else
                field[wtx][dx] = 1;
//    printf("%d %d %d %d %d %d\n", wx, wy, wtx, wty, c, d);
    int count = 0;
//    for (int dx = 0; dx <= 9; dx++)
  //      for (int dy = 0; dy <= 9; dy++)
    //        printf("%d%c", field[dx][dy], dy == 9 ? '\n' : ' ');
    for (int dx = -1; dx <= 1; dx++)
        for (int dy = -1; dy <= 1; dy++)
            if (dx * dx + dy * dy != 0 && (field[c + dx][d + dy] == 1))
                count++;
    //writeln(count);
    if (count == 8 && check)
    {
        writeln("Checkmate");
        return;
    }
    if (count == 8)
    {
        writeln("Stalemate");
        return;
    }
    if (check)
    {
        writeln("Check");
        return;
    }
    writeln("Normal");
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    run();
    return 0;
}

























graph::graph(int n){this->n = n;edges.resize(n);int t;fori(n){edges[i].resize(n);forj(n)readln(t),edges[i][j] = t == '1';}}graph::graph(int n, int m){this->n = n;edges.resize(n);int u, v;fori(m)readln(u, v),add_edge(u - 1, v - 1);}void graph::add_edge(int u, int v){edges[u].pb(v);}void graph::add_or_edge(int u, int v){edges[u].pb(v);edges[v].pb(u);}graph::graph(){};void graph::createGraph(int n){edges.resize(n);}void graph::writeln(){fori(n)forj(edges[i].size())::writeln(i, edges[i][j]);}void graph::writelnMatrix(){::writeln(edges);}
void print(double a){printf("%f ", a);}
void print(int a){printf("%d ", a);}
void print(string a){printf("%s ", a.c_str());}
void print(long long a){printf("%lld ", a);}
void print(unsigned long a){printf("%ld ", a);}
void print(unsigned int a){printf("%d ", a);}
void print(char a){printf("%c ", a);}
template<class Type>
void print(vector<Type>& a){for(int i = 0; i < a.size(); ++i)print(a[i]);}
template<class Type>
void print(vector<vector<Type>>& a){for(int i = 0; i < a.size(); ++i)writeln(a[i]);}
template<class Type1, class Type2>
void print(pair<Type1, Type2>& a){print(a.first);print(a.second);}
void read(double &a){scanf("%lf", &a);}
void read(int &a){scanf("%d", &a);}
void read(string &a){cin>>a;}
void read(long long &a){scanf("%lld", &a);}
void read(char &a){scanf("%c", &a);}
template<class Type>
void read(vector<Type> &a){if (a.size() == 0){int n; read(n); a.resize(n);}for(int i = 0; i < a.size(); ++i)read(a[i]);}
template<class Type>
void read(vector<vector<Type>> &a){for(int i = 0; i < a.size(); ++i)readln(a[i]);}
template <class Head, class... Tail>
void writeln(Head head, Tail... tail){print(head);writeln(tail...);}
template <class Head, class... Tail>
void readln(Head& head, Tail&... tail){read(head);readln(tail...);}
