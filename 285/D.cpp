#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <algorithm>
#define enter printf("\n");

using namespace std;
int INF = 1000000007;
vector<int> a, b;
vector<long long> fac;
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
   //freopen("input.txt", "r", stdin);

   fac.push_back(1);
   fac.push_back(1);
   for (int i = 2; i < 17; i++)
        fac.push_back(fac[i - 1] * i);
//   for (int i = 1; i < 17; i++)
   long long ans = 0;
   //for (int i = 1; i <= 15; i = i + 2)
   b.resize(16 + 1);
   vector<bool> d;
   int i = 13;
   {
       a.clear();
       for (int s = 1; s <= i; s++)
            a.push_back(s);
       ans = 0;
       for (int q = 1; q <= i; q++)
            b[q - 1] = q;
       for (long long q = 1; q <= fac[i]; q++)
       {
           d.clear();
           d.resize(i + 2, false);
           bool f = true;
           for (int w = 0; w < i; w++)
                if (d[(a[w] - 1 + b[w] - 1) % i + 1])
                {
                    f = false;
                    break;
                } else
                    d[(a[w] - 1 + b[w] - 1) % i + 1] = true;
            if (f)
                ans++;
            next_permutation(b.begin(), b.begin() + i);
        }
       printf("%I64d ", ans);
   }
   return 0;
}
