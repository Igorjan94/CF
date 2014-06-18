#include <algorithm>
#include <cstdlib>
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <iterator>
#include <queue>

using namespace std;

int n, k, l, classes;
vector<int> s(400001), c(400001), c1(400001), head(400001), a(400001), a1(400001), temp(400001), a_1(400002);

template <class T>
void writeln(vector<T> &a)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
//    copy(a.begin(), a.end(), ostream_iterator<T>(cout, " "));
    printf("\n");
}

void read()
{
    int i = 0;
    char d;
    while (true)
    {
        scanf("%c", &d);
        if (d == '\n')
            break;
        s[i] = d - 'a' + 1;
        a[i] = i++;
    }
    s[i] = 0;
    a[i] = i++;
    n = i;
}

void radix(vector<int> &a)
{
    for (int i = 0; i < n; i++)
        head[s[a[i]] + 1]++;
    head[0] = 0;
    for (int i = 1; i < 28; i++)
        head[i] += head[i - 1];
    for (int i = 0; i < n; i++)
        temp[head[s[a[i]]]++] = a[i];
    c[a[0]] = 0;
    classes = 1;
    a = temp;
    for (int i = 1; i < n; i++)
    {
        if (s[a[i]] != s[a[i - 1]])
            classes++;
        c[a[i]] = classes - 1;
    }
}

void suffix_array(vector<int> &s)
{
    /*c.resize(n);
    head.resize(n);
    a.resize(n);
    a1.resize(n);
    c1.resize(n);
    temp.resize(n);*/
    radix(a);
    for (int l = 1; l < n; l *= 2)
    {
        head.clear();
        head.resize(classes, 0);
        for (int i = 0; i < n; i++)
            head[c[a1[i] = (a[i] - l + n) % n]]++;
        for (int i = 1; i < classes; i++)
            head[i] += head[i - 1];
        for (int i = n - 1; i >= 0; i--)
            a[--head[c[a1[i]]]] = a1[i];
        classes = 1;
        c1[a[0]] = 0;
        for (int i = 1; i < n; i++)
        {
            if (c[a[i]] != c[a[i - 1]] || c[(a[i] + l) % n] != c[(a[i - 1] + l) % n])
                classes++;
            c1[a[i]] = classes - 1;
        }
        c = c1;
     }
}

int main()
{
//    freopen("count.out", "w+", stdout);
  //  freopen("count.in", "r", stdin);
    read();
    if (n == 2)
    {
        printf("1\n");
        return 0;
    }
    suffix_array(s);
    int z = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++)
        a_1[a[i]] = i;
    int i;
    for (int j = 0; j < n; j++)
    {
        i = a_1[j];
        for (;s[a[i] + z] == s[a[(i + 1) % n] + z]; z++);
        ans = ans + n - 1 - a[i] - z;
        if (z > 0)
            z--;
    }
    printf("%I64d\n", ans);
    return 0;
}
