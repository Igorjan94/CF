#include <testlib.h>
#include <bits/stdc++.h>

using namespace std;

string numberFormat = "-?[1-9][0-9]*|0";

pair<string, string> readAns(InStream& stream)
{
    string first = stream.readString(numberFormat);
    string second = stream.readString(numberFormat);
    return {first, second};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    auto jans = readAns(ans);
    auto pans = readAns(ouf);
    if (jans.first != pans.first)
        quitf(_wa, "Test %s: summ is incorrect: expected = %s, found = %s\n", argv[1], jans.first.c_str(), pans.first.c_str());
    else if (jans.second != pans.second)
        quitf(_wa, "Test %s: difference is incorrect: expected = %s, found = %s\n", argv[1], jans.second.c_str(), pans.second.c_str());
    else if (jans == pans)
        quitf(_ok, "Test %s: summ and difference are correct!", argv[1]);
}
