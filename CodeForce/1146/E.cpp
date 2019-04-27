#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

#include <stdio.h>

#define fori(n) for (unsigned i = 0; i < n; ++i)
#define BS 512

unsigned n, q;
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
    for (unsigned i = 0; i + BS < n; i += BS)
        for (unsigned t = 0; t < q; ++t)
            if (c[t] == '<')
                for (unsigned j = i; j < i + BS; ++j)
                    a[j] = a[j] < x[t] ? -a[j] : a[j];
            else
                for (unsigned j = i; j < i + BS; ++j)
                    a[j] = a[j] > x[t] ? -a[j] : a[j];
    for (unsigned t = 0; t < q; ++t)
        if (c[t] == '<')
            for (unsigned j = n / BS * BS; j < n; ++j)
                a[j] = a[j] < x[t] ? -a[j] : a[j];
        else
            for (unsigned j = n / BS * BS; j < n; ++j)
                a[j] = a[j] > x[t] ? -a[j] : a[j];
    fori(n)
        printf("%d ", a[i]);
    return 0;
}
