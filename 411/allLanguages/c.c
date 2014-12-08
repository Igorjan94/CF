#include<stdio.h>
#include<string.h>

int main()
{
    int i, ok = 0, ok1 = 0, ok2 = 0, ok3 = 0;
    char s[101];
    scanf("%s", s);
    for (i = 0; i < strlen(s); i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            ok = 1;
        if (s[i] >= 'A' && s[i] <= 'Z')
            ok1 = 1;
        if (s[i] >= '0' && s[i] <= '9')
            ok2 = 1;
    }
    if (strlen(s) >= 5)
        ok3 = 1;;
    printf(ok + ok1 + ok2 + ok3 == 4 ? "Correct" : "Too weak");
    return 0;
}
