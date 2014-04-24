#include <cstdlib>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");
#define ll long long

using namespace std;
int INF = 1000000007;
const int size = 48;
ll ans[size] = {
1ll,
4ll,
9ll,
121ll,
484ll,
10201ll,
12321ll,
14641ll,
40804ll,
44944ll,
1002001ll,
1234321ll,
4008004ll,
100020001ll,
102030201ll,
104060401ll,
121242121ll,
123454321ll,
125686521ll,
400080004ll,
404090404ll,
10000200001ll,
10221412201ll,
12102420121ll,
12345654321ll,
40000800004ll,
1000002000001ll,
1002003002001ll,
1004006004001ll,
1020304030201ll,
1022325232201ll,
1024348434201ll,
1210024200121ll,
1212225222121ll,
1214428244121ll,
1232346432321ll,
1234567654321ll,
4000008000004ll,
4004009004004ll,
100000020000001ll,
100220141022001ll,
102012040210201ll,
102234363432201ll,
121000242000121ll,
121242363242121ll,
123212464212321ll,
123456787654321ll,
400000080000004ll};
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<int> &f, int n)
{
    int x;
    for (int i = 1; i <= n; i++)
    {
        read(x);
        f.push_back(x);
    }
}

void writeln(vector<int> &f)
{
    int x;
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

int test()
{
    ll n, m;
    cin >> n >> m;
    return upper_bound(ans, ans + size, m) - lower_bound(ans, ans + size, n);
}

int main()
{
    freopen("input.in", "r", stdin);
    freopen("output.txt", "w+", stdout);
    int T;
    readln(T);
    for (int tttt = 0; tttt < T; tttt++)
    {
        printf("Case #%d: ", tttt + 1);
        printf("%d\n", test());
    }
    for (int i = 0; i < size; i++)
    cout << (ll) sqrt(ans[i]) << "\n";
    return 0;
}
