#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <math.h>
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
#define con 100000

using namespace std;
int INF = 1000000007;
string FILENAME = "jenny";
string FILEINPUT = FILENAME;
int mx = 0;
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}
void readln(vector<int> &f, int n){int x;for (int i = 1; i <= n; i++){read(x);f.push_back(x);mx=max(mx,x);}}void writeln(vector<int> &f){for (int i = 0; i < f.size(); i++)printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');}

vi a, date, indexes;
int n, k;
char s[11];
int years[300];
int month[13] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
bool is[200000];

int g(int i)
{
    return (1900 + i) / 4 == 0 && ((1900 + i) % 100) || (1900 + i) / 400 == 0;
}

int f(char s[])
{
    int d = (s[0] - '0') * 10 + s[1] - '0',
        m = (s[3] - '0') * 10 + s[4] - '0',
        y = (s[6] - '0') * 1000 + (s[7] - '0') * 100 + (s[8] - '0') * 10 + s[9] - '0';
    y -= 1900;
    int ans = years[y] + d + (m > 2 ? g(y) : 0);
    ans += month[m];
    return ans;
}

bool cmp(int i, int j)
{
    if (date[i] < date[j])
        return true; else
        if (date[i] > date[j])
        return false;
            else return a[i] < a[j];
}

void toDate(int k)
{
    int tt = 0, count = 0;
    while (tt >= k)
        tt -= years[tt],
        count++;
    int xy = 11;
    while (tt - month[xy] < k)
        xy--;
    tt -= month[xy];
    printf("%d:%d:%d\n", tt, xy, count + 1900 - 1);
}


int yy[1000000], mm[1000000], dd[1000000];
void run()
{
    years[0] = 0;
    int t;
    for (int i = 1; i <= 12; i++)
        month[i] = month[i - 1] + month[i];
    for (int i = -202; i < 202; i++)
    {
        years[i + 203] = years[i - 1 + 203] + 365;
        if (g(i))
            years[i]++;
    }
    readln(n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s\n", s);
        scanf("%s\n", s);
        date.pb(f(s));
        //writeln(f(s));
        is[date[i]] = true;
        readln(k);
        a.pb(k);
        indexes.pb(i);
    }
    sort(indexes.begin(), indexes.end(), cmp);
    int k = INF;
    for (int i = 0; i < n; i++)
    {
        bool f = false;
        for (int j = 0; j < a[indexes[i]]; j++)
            if (is[date[indexes[i]] - j - 1 + con])
                continue; else
                {
                    is[date[indexes[i]] - j - 1 + con] = true;
                    f = true;
//                    writeln(date[indexes[i]] - j - 1, k);
                    k = min(date[indexes[i]] - j - 1 + con, k);
                    break;
                }
        if (!f)
        {
            printf("Impossible\n");
            return;
        }
    }
    toDate(k);
}

int main()
{
    freopen(FILEINPUT.append(".in").c_str(), "r", stdin);
    freopen(FILENAME.append(".out").c_str(), "w", stdout);
    run();
    return 0;
}
