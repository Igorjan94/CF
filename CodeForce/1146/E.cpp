#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

#include <stdio.h>

#define fori(n) for (int i = 0; i < n; ++i)
#define BS 8192

int n, q;
int a[100001];
int x[100001];
char c[100001];

int main()
{
    scanf("%d%d", &n, &q);
    fori(n)
        scanf("%d", &a[i]);
    fori(q)
        scanf(" %c%d", &c[i], &x[i]);
    for (int i = 0; i + BS < n; i += BS)
        for (int t = 0; t < q; ++t)
            if (c[t] == '<')
                for (int j = i; j < i + BS; ++j)
                    a[j] = a[j] < x[t] ? -a[j] : a[j];
            else
                for (int j = i; j < i + BS; ++j)
                    a[j] = a[j] > x[t] ? -a[j] : a[j];
    for (int t = 0; t < q; ++t)
        if (c[t] == '<')
            for (int j = n / BS * BS; j < n; ++j)
                a[j] = a[j] < x[t] ? -a[j] : a[j];
        else
            for (int j = n / BS * BS; j < n; ++j)
                a[j] = a[j] > x[t] ? -a[j] : a[j];
    fori(n)
        printf("%d ", a[i]);
    return 0;
}
