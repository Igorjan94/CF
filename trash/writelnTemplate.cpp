#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void writeln_1()
{
    printf("\n");
    return;
}

template <class... Tail>
void writeln_1(int head, Tail... tail)
{
    printf(" %d", head);
    writeln_1(tail...);
}

template <class... Tail>
void writeln(int head, Tail... tail)
{
    printf("%d", head);
    writeln_1(tail...);
}

constexpr int INF = 100;

constexpr int factorial (int n)
{
    return n > 0 ? n * factorial(n - 1) : 1;
}
int main()
{
    constexpr int x = factorial(11);
    writeln(x);
    vector<int> a;
    for (int i = 0; i < 12; i++)
        a.push_back(factorial(i));
    for (int s : a)
        writeln(s);
    writeln(1, 2, 3, 4, 5);
    return 0;
}
