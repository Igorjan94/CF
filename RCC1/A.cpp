#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
vector<int> a;
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

int main()
{
//   freopen("input.txt", "r", stdin);
    a.resize(6);
    while (true)
    {
        int c = 0;
        int s = 0;
        for (int i = 0; i < 6; i++)
            scanf("%d", &a[i]),
            a[i] == 0 ? c++ : c += 0;
        if (c == 6)
            break;
        for (int i = 0; i < 6; i += 2)
            if (a[i] > a[i + 1])
                swap(a[i], a[i + 1]);
        int mx = -1, j;
        for (int i = 0; i < 6; i += 2)
            if (a[i] > mx)
            mx = a[i],
            j = i;
        s = s + a[j] * a[j + 1];
        swap(a[j], a[0]);
        swap(a[j + 1], a[1]);
        s = s + a[2] * a[3];
        s = s + a[4] * a[5];
        if (a[2] < a[4])
            swap(a[2], a[4]),
            swap(a[3], a[5]);
        //printf("%I64d\n", s);

        s = s - min(a[0], a[2]) * min(a[1], a[3]);
        s = s - max(min(a[0], a[4]) * min(a[1], a[5])
        ,min(a[4], a[2]) * min(a[3], a[5]));
        printf("%d\n", s);
    }
   return 0;
}
