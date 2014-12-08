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

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

int n, m, k;
int ans = 0;
vector<pii> trace;
struct tri
{
    int a, b, c;
    tri(){};
    tri(int a, int b, int c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};
queue<tri> q;
bool u[51][51];

void bfs()
{
    while (true)
    {
        int i = q.front().a;
        int j = q.front().b;
        int d = q.front().c;
        q.pop();
        if (u[i][j] || i >= n || j >= m)
            continue;
        --k;
        u[i][j] = true;
        ans += d;
        trace.pb({i + 1, j + 1});
        if (!k)
            return;

        q.push(tri(i + 1, j, d + 1));
        q.push(tri(i, j + 1, d + 1));
    }
}

void run()
{
    readln(n, m, k);
    q.push(tri(0, 0, 1));
    bfs();
    cout << ans << endl;
    for(int i = trace.size() - 1; i >= 0; --i)
    {
        auto t = trace[i];
        printf("(1,1) ");
        for (int i = 2; i <= t.second; i++)
            printf("(%d,%d) ", 1, i);
        for (int i = 2; i <= t.first; i++)
            printf("(%d,%d) ", i, t.second);
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
