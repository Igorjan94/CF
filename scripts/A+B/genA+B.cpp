#include <testlib.h>
#include <writeln.h>
#include <bits/stdc++.h>

using namespace std;

int counter = 0;

void printTest(string_view first, string_view second)
{
    startTest(++counter);
    writeln(first, second);
}

void all(string first, string second)
{
    printTest(first, second);
    printTest("-" + first, second);
    printTest(first, "-" + second);
    printTest("-" + first, "-" + second);
}

int main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    string first = "1";
    string second = "1";
    all(first, second);
    for (int i = 0; i < 30; i += 2)
        second += "00",
        all(second, first),
        all(first, second);
    for (int i = 0; i < 10; ++i)
    {
        first = rnd.next("[1-9][0-9]{99}");
        second = rnd.next("[1-9][0-9]{99}");
        all(first, second);
    }
}
