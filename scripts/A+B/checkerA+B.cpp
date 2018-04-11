#include <testlib.h>
#include <bits/stdc++.h>

using namespace std;

string numberFormat = "-?[1-9][0-9]*|0";

tuple<string, string, string> readAns(InStream& stream)
{
    string first = stream.readString(numberFormat);
    string second = stream.readString(numberFormat);
    string third = stream.readString(numberFormat);
    return {first, second, third};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    auto [ja, js, jm] = readAns(ans);
    auto [pa, ps, pm] = readAns(ouf);
    if (ja != pa)
        quitf(_wa, "Test %s: summ is incorrect: expected = %s, found = %s\n", argv[1], ja.c_str(), pa.c_str());
    else if (js != ps)
        quitf(_wa, "Test %s: difference is incorrect: expected = %s, found = %s\n", argv[1], js.c_str(), ps.c_str());
    else if (jm != pm)
        quitf(_wa, "Test %s: product is incorrect: expected = %s, found = %s\n", argv[1], jm.c_str(), pm.c_str());
    else
        quitf(_ok, "Test %s: summ, difference and product are correct!", argv[1]);
}
