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
ll N, M;
vi a;

ll f(ll j)
{
    ll q = m / (j + 2), w = m % (j + 2);
    return (ll) (N - j) * (N - j) + j - (ll) (q + 1) * (q + 1) * w - (ll) (q * q * (j + 2 - w));
}

void run()
{
    readln(n, m);
    N = n, M = m;
    if (m == 0)
    {
        cout << N * N << endl;
        fori(n)
            printf("o");
        return;
    }
    if (n == 0)
    {
        cout << -M * M << endl;
        fori(m)
            printf("x");
        return;
    }
    ll ans = -10000000000000ll;
    int z = -1;
    for(ll i = 0; i < N; i++)
    {
        ll temp = f(i);
        if (ans < temp)
            ans = temp,
            z = i;
    }
//    writeln(z);
    cout << ans << endl;
    int te = 0;
    fori(z + 1)
    {
        int t = m/(z+2) + (bool)(i < m%(z+2));
        te += t;
        forj(t)
            printf("x");
        if (i==0)
            forj(n-z)
                printf("o");
        else
            printf("o");
    }
    forj(m - te)
        printf("x");
}

int main()
{
    /*freopen(FILEINPUT.append(".out").c_str(), "r", stdin);
    string s;
    cin >> s;
    cin >> s;
    cin >> s;
    ll q = 0;
    ll i = 1, j = 0;
    while (i < s.size())
    {
        while (s[i] == s[i - 1])
            i++;
        q += (ll)(i - j) * (i - j) * (s[i - 1] == 'o' ? 1 : -1);
        j = i++;
    }
    cout << q << endl;*/
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