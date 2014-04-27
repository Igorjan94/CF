#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
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
string FILENAME = "start";
string FILEINPUT = FILENAME;

void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

struct pii
{
    int first, second, i;
    pii(int i, int j)
    {
        first = i;
        second = j;
    }
};

bool cmp(pii i, pii j)
{
    return i.first < j.first;
}
bool cmp2(pii i, pii j)
{
    return i.second < j.second;
}

void run()
{
    int n, s1 = 0, s2 = 0, x, y;
    readln(n);
    vector< pii > a;
    int m[101];
    for (int i = 0; i <= 100; i++)
        m[i] = 0;
    forn(i, 2 * n)
        read(x),
        a.pb(pii(x, i)),
        m[x]++;
    int count = 0;
    for (int i = 0; i <= 100; i++)
        count += m[i] > 0;
    sort(a.begin(), a.end(), cmp);
    int k = 0, j2 = 0;
    int i = 0;
    int c1 = 0, c2 = 0;
    for (int jj = 0; jj < count; jj++)
    {
        int t = m[a[i].first];
        if (t > 1)
        {
            if (t % 2 == 0)
            {
                for (int j = 0; j < t / 2; j++)
                    a[i++].i = 0;
                for (int j = 0; j < t / 2; j++)
                    a[i++].i = 1;
                c1 += t / 2;
                c2 += t / 2;
            } else
            {
                if (c1 >= c2)
                {
                    for (int j = 0; j < t / 2; j++)
                        a[i++].i = 0;
                    for (int j = 0; j < t - t / 2; j++)
                        a[i++].i = 1;
                    c1 += t / 2;
                    c2 += t - t / 2;
                } else
                {
                    for (int j = 0; j < t / 2; j++)
                        a[i++].i = 1;
                    for (int j = 0; j < t - t / 2; j++)
                        a[i++].i = 0;
                    c1 += t - t / 2;
                    c2 += t / 2;
                }
            }
            k++;
            j2++;
        } else
        {
            if (c1 <= c2)
            {
                a[i++].i = 0;
                k++;
                c1++;
            } else
            {
                a[i++].i = 1;
                j2++;
                c2++;
            }
        }
    }
    sort(a.begin(), a.end(), cmp2);
    writeln(j2 * k);
    forn(i, 2 * n)
        printf("%d ", a[i].i + 1);
}

int main()
{
//    freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
  //  freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
