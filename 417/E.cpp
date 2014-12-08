#include <bits/stdc++.h>

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

void writeln(int a);void writeln(int a, int b); void writeln(int a, int b, int c);  void writeln(int a, int b, int c, int d);   void writeln(vector<int>& a);
void readln(int& a);void readln(int& a, int& b);void readln(int& a, int& b, int& c);void readln(int& a, int& b, int& c, int& d);void readln(vector<int>& a, int n);

struct graph
{
    vector<vector<int>> edges;
    int n;
    graph(int n);
    graph(int n, int m);
    graph();
    void createGraph(int n);
    void add_edge(int u, int v);
    void add_or_edge(int u, int v);
    void writelnMatrix();
    void writeln();
};

int n, m, k;
vector<vi> a = {{1, 0}, {4, 1}, {6, 1}, {1, 0}, {2, 1}, {2, 5}, {6, 1}, {1, 1}, {1, 0}, {6, 5}, {2, 1}, {1, 3}, {6, 1}, {2, 5}, {2, 8}, {1, 0}, {1, 1}, {4, 9}, {2, 1}, {1, 2}, {2, 12}, {4, 4}, {4, 1}, {1, 5}, {1, 0}, {2, 8}, {6, 9}, {1, 1}, {2, 1}, {2, 21}, {2, 4}, {1, 4}, {1, 2}, {2, 12}, {2, 17}, {1, 0}, {4, 9}, {14, 29}, {2, 8}, {1, 3}, {1, 1}, {4, 33}, {4, 9}, {1, 7}, {2, 9}, {2, 21}, {14, 1}, {1, 2}, {1, 0}, {2, 5}, {2, 17}, {1, 6}, {4, 1}, {2, 8}, {2, 1}, {1, 1}, {1, 3}, {4, 4}, {2, 4}, {1, 5}, {2, 9}, {16, 1}, {4, 32}, {1, 0}, {1, 2}, {2, 5}, {4, 33}, {1, 4}, {2, 17}, {2, 24}, {2, 1}, {1, 9}, {1, 1}, {2, 13}, {2, 20}, {1, 3}, {4, 1}, {4, 32}, {2, 9}, {1, 8}, {1, 0}, {6, 13}, {40, 25}, {1, 2}, {2, 12}, {2, 28}, {6, 8}, {1, 7}, {1, 4}, {2, 8}, {2, 24}, {1, 1}, {4, 17}, {2, 13}, {2, 4}, {1, 6}, {1, 3}, {4, 49}, {2, 9}, {1, 0}};
void writeln(vector<vi>& a)
{
    fori(a.size())
        writeln(a[i]);
}

bool check(int i)
{
    return sqrt(i) - (int) sqrt(i) == 0;
}

void run()
{
    //readln(n, m);
    //n = 1;
    //a.resize(n);
    int c = 100, count=0;
    int x = 3;
    for(int m = 1; m <= 100; m++)
        for(int n = 1, f=1; n <= 100; n++, f=1)
            for(int y = 1; y <= c && f; y++)
                if (check(a[n-1][0]*a[n-1][0]*a[n-1][1] + y*y*(n-a[n-1][1])))
                    f=0,
                    count++;
    cout << count << endl;

}

int main()
{
    //freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}

graph::graph(int n)
{
    this->n = n;
    edges.resize(n);
    int t;
    fori(n)
    {
        edges[i].resize(n);
        forj(n)
            readln(t),
            edges[i][j] = t == '1';
    }
}

graph::graph(int n, int m)
{
    this->n = n;
    edges.resize(n);
    int u, v;
    fori(m)
        readln(u, v),
        add_edge(u - 1, v - 1);
}

void graph::add_edge(int u, int v)
{
    edges[u].pb(v);
}

void graph::add_or_edge(int u, int v)
{
    edges[u].pb(v);
    edges[v].pb(u);
}

graph::graph(){};

void graph::createGraph(int n)
{
    edges.resize(n);
}

void graph::writeln()
{
    fori(n)
        forj(edges[i].size())
            ::writeln(i, edges[i][j]);
}

void graph::writelnMatrix()
{
    fori(n)
    {
        forj(n)
            printf("%d ", edges[i][j]);
        printf("\n");
    }
}

void readln(vector<int> &f, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        readln(x);
        f.push_back(x);
    }
}

void writeln(vector<int> &f)
{
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

void writeln(int a)
{
    printf("%d\n", a);
}

void writeln(int a, int b)
{
    printf("%d %d\n", a, b);
}

void writeln(int a, int b, int c)
{
    printf("%d %d %d\n", a, b, c);
}

void writeln(int a, int b, int c, int d)
{
    printf("%d %d %d %d\n", a, b, c, d);
}

void readln(int &a)
{
    scanf("%d", &a);
}

void readln(int &a, int &b)
{
    scanf("%d %d", &a, &b);
}

void readln(int &a, int &b, int &c)
{
    scanf("%d %d %d", &a, &b, &c);
}

void readln(int &a, int &b, int &c, int &d)
{
    scanf("%d %d %d %d", &a, &b, &c, &d);
}
