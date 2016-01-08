#include <bits/stdc++.h>

using namespace std;

struct A
{
    int id = 1000;
    int get()
    {
        return 1;
    }
};

struct B : A
{
    int get()
    {
        return 2;
    }
};

struct C : A
{
    int get()
    {
        return -A::get() * 2;
    }
};

struct D : A {};

int main()
{
    A a;
    B b;
    C c;
    D d;
    std::cout << a.get() << " " << b.get() << " " << c.get() << " " << d.get() << "\n";
    return 0;
}
