
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <string>
#include <stack>

#define enter printf("\n");
#define pb push_back
#define ll long long
#define fors(it, r) for (set<int>::iterator it = r.begin(); it != r.end(); it++)
#define forvit(it, r) for (vector<int>::iterator it = r.begin(); it != r.end(); it++)
#define forv(i, vector) for (int i = 0; i < vector.size(); i++)
#define forn(i, n) for (int i = 0; i < n; i++)
#define vi vector<int>
#define sigma 26

using namespace std;
int INF = 1000000007;
string FILENAME = "minimization";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

struct dsu
{
    vi a, id;
    int n, m;
    dsu(int n)
    {
        this->n = n;
        id.resize(n, n);
        forn(i, n)
            a.pb(i);
    }

    int get(int i)
    {
        return a[i] == i ? i : a[i] = get(a[i]);
    }

    void uni(int i, int j)
    {
        i = get(i);
        j = get(j);
        if (i == j)
            return;
        a[i] = a[j];
    }

    void getId()
    {
        int counter = 0;
        forn(i, n)
            if (id[get(i)] == n)
                id[get(i)] = counter++;
        m = counter;
    }
};

struct aut
{
    int n, m, k;
    vector<bool> ok, useful;
    vector< vi > a;
    vector< vector< vi > > b;

    aut(int n)
    {
        this->n = n;
        m = 0;
        k = 0;
        ok.resize(n + 2, false);
        a.resize(n + 2);
        forn(i, n)
            a[i].resize(sigma, n);
    }

    aut()
    {
        int x, y;
        char c;
        readln(n, m, k);
        ok.resize(n + 2, false);
        useful.resize(n + 2, false);
        a.resize(n + 2);
        b.resize(n + 2);
        queue<int> q;
        forn(i, n + 1)
            a[i].resize(sigma + 1, n),
            b[i].resize(sigma + 1);
        forn(i, k)
        {
            read(x);
            ok[x - 1] = true;
            q.push(x - 1);
            useful[x - 1] = true;
        }
        forn(i, m)
        {
            scanf("%d %d %c\n", &x, &y, &c);
            a[x - 1][c - 'a'] = y - 1;
            b[y - 1][c - 'a'].pb(x - 1);
        }
        while (!q.empty())
        {
            int v = q.front();
            q.pop();
            useful[v] = true;
            forn(i, sigma)
                forvit(j, b[v][i])
                    if (*j != n && !useful[*j])
                        q.push(*j);
        }
        forn(i, n)
            forn(j, sigma)
                if (a[i][j] == n)
                    b[n][j].pb(i);
//        forn(i, n)
  //          printf("%d ", (int)useful[i]);
    //    cout << endl;
    }

    void write()
    {
        writeln(n, m, k);
        forn(i, n)
            if (ok[i])
                printf("%d ", i + 1);
        printf("\n");
        forn(i, n)
            forn(j, sigma)
                if (a[i][j] != n)
                    printf("%d %d %c\n", i + 1, a[i][j] + 1, 'a' + j);
    }
};

void debug(aut& a, vector< vector<bool> >& p)
{
    printf("  ");
    forn(i, a.n + 1)
        printf("%c ", 'A' + i);
    printf("\n");
    forn(i, a.n + 1)
    {
        printf("%c ", 'A' + i);
        forn(j, a.n + 1)
            printf("%d%c", (int)p[i][j], j == a.n ? '\n' : ' ');
    }
}

aut minimization(aut& a)
{
    //aut b(a.n);
    vector< vector<bool> > p;
    vi id;
    p.resize(a.n + 1);
    id.resize(a.n, -1);
    forn(i, a.n)
        p[i].resize(a.n, false);
    queue< pair<int, int> > q;
    forn(i, a.n)
        p[i][i] = true;
    forn(i, a.n + 1)
        for (int j = i + 1; j <= a.n; j++)
            if (a.ok[i] != a.ok[j] || !a.useful[i] || !a.useful[j])
                q.push({i, j}),
                p[i][j] = true,
                p[j][i] = true;
    debug(a, p);
    int l, f;
    while (!q.empty())
    {
        f = q.front().first;
        l = q.front().second;
        q.pop();
        forn(i, sigma)
            if (a.b[f][i].size() > 0 && a.b[l][i].size() > 0)
                forvit(j, a.b[f][i])
                    forvit(k, a.b[l][i])
                        if (!p[*j][*k])
                            q.push({*j, *k}),
                            p[*j][*k] = true,
                            p[*k][*j] = true;
    }
    debug(a, p);
    /*dsu ds(a.n);
    forn(i, a.n)
        forn(j, a.n)
            if (!p[i][j])
                ds.uni(i, j);*/
    int counter = 0;
    forn(i, a.n)
    {
        if (id[i] == -1)
            id[i] = counter++;

        forn(j, a.n)
            if (!p[i][j])
                id[j] = id[i];
    }
//    writeln(b.n, counter);
    forn(i, a.n)
        if (!a.useful[i])
            counter--;
    aut b(counter);//b.n = counter;
    forn(i, a.n)
    {
        if (!a.useful[i])
            continue;
        if (a.ok[i])
            if (!b.ok[id[i]])
                b.ok[id[i]] = true,
                b.k++;
        forn(j, sigma)
            if (a.a[i][j] != a.n && b.a[id[i]][j] == a.n && a.useful[a.a[i][j]])
                    b.a[id[i]][j] = id[a.a[i][j]],
                    b.m++;
    }
//    writeln(100500);
//    debug(a, p);
    return b;
}

void run()
{
    aut a;
    aut mn = minimization(a);
    mn.write();
}

int main()
{
    freopen(FILEINPUT.append(".in").c_str(), "r", stdin); //freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
