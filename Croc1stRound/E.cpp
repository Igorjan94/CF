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
void writeln(int a){printf("%d\n", a);}void writeln(int a, int b){printf("%d %d\n", a, b);}void writeln(int a, int b, int c){printf("%d %d %d\n", a, b, c);}void writeln(int a, int b, int c, int d){printf("%d %d %d %d\n", a, b, c, d);}void write(int a){printf("%d", a);}void write(int a, int b){printf("%d %d", a, b);}void write(int a, int b, int c){printf("%d %d %d", a, b, c);}void write(int a, int b, int c, int d){printf("%d %d %d %d", a, b, c, d);}void read(int &a){scanf("%d", &a);}void read(int &a, int &b){scanf("%d %d", &a, &b);}void read(int &a, int &b, int &c){scanf("%d %d %d", &a, &b, &c);}void read(int &a, int &b, int &c, int &d){scanf("%d %d %d %d", &a, &b, &c, &d);}void readln(int &a){scanf("%d\n", &a);}void readln(int &a, int &b){scanf("%d %d\n", &a, &b);}void readln(int &a, int &b, int &c){scanf("%d %d %d\n", &a, &b, &c);}void readln(int &a, int &b, int &c, int &d){scanf("%d %d %d %d\n", &a, &b, &c, &d);}

void readln(vector<int> &a, int n)
{
    int x;
    a.push_back(0);
    for (int i = 1; i <= n; i++)
    {
        read(x);
        a.push_back(x);
    }
}

void writeln(vector<int> &f)
{
    int x;
    for (int i = 0; i < f.size(); i++)
        printf("%d%c", f[i], i == f.size() - 1 ? '\n' : ' ');
}

struct node
{
    vector<node*> v;
    int count;
    int l;
    int f;
    node(int l, int count, int f)
    {
        this->count = count;
        this->l = l;
        this->f = f;
    }
};

node *root;
node *k;

int get(int s, int temp)
{
    while (true)
    {
        int i = 0;
        while (s > temp)
        {
            temp += k->v[i]->count;
            i++;
        }
        if (k->f)
            break;
        i--;
        temp -= k->count;
        k = k->v[i];
    }
    return k->f == 1 ? a[s - temp + k->l] : b[s - temp + k->l];
}

void inser(int s, int where, int much)
{
    int temp = 0;
    while (true)
    {
        int i = 0;
        k->count += much;
        while (s > temp)
        {
            temp += k->v[i]->count;
            i++;
        }
        if (k->f)
            break;
        i--;
        temp -= k->count;
        k = k->v[i];
    }
    node *t = new node(k->l, temp - s + 1, k->f);
    k->v.push_back(t);
    t = new node(where, much, 2);
    k->v.push_back(t);
    t = new node(temp - s + k->l + 2, k->count - temp + s - 1 - much, k->f);
    k->v.push_back(t);
    k->f = 0;
 }

void writeln(node* k)
{
    writeln(k->l, k->count, k->f);
    for (int i = 0; i < k->v.size(); i++)
        writeln(k->v[i]);
}

int main()
{
    freopen("input.txt", "r", stdin);
//freopen("output.txt", "w+", stdout);
    int n, m, x, y, z, s;
    readln(n, m);
    readln(b, n);
    readln(a, n);
    node *t = new node(0, n, 1);
    root = new node(0, 0, 0);
    root->v.push_back(t);
    for (int qq = 0; qq < m; qq++)
    {
        writeln(root);
        read(s);
        k = root;
        if (s == 2)
        {
            cout << "ck\n";
            readln(x);
            writeln(get(x, 0));
        } else
        {
            cout << "ins\n";
            readln(x, y, z);
            inser(x, y - 1, z);
        }
    }
    return 0;
}
