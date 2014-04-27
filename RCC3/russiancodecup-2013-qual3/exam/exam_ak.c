#include <stdio.h>

#define SECSINDAY (24 * 60 * 60)

int main()
{
    int n;
    scanf("%d", &n);
    int i;
    for (i = 0; i < n; i++)
    {
        int h1, m1, s1, h2, m2, s2, m;
        scanf("%d:%d:%d %d:%d:%d %d", &h1, &m1, &s1, &h2, &m2, &s2, &m);
        m *= 60;
        int exam = ((h2 - h1) * 3600 + (m2 - m1) * 60 + s2 - s1 + SECSINDAY - 1) % SECSINDAY + 1;
        if (m <= exam)
            printf("Perfect\n");
        else if (m <= exam + 60 * 60)
            printf("Test\n");
        else
            printf("Fail\n");
    }
    return 0;
}
