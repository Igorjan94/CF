#include <testlib.h>
#include <bits/stdc++.h>

using namespace std;

string numberFormat = "-?[1-9][0-9]*|0";

tuple<string, string, string, string, string> readAns(InStream& stream)
{
    string first = stream.readString(numberFormat);
    string second = stream.readString(numberFormat);
    string third = stream.readString(numberFormat);
    string forth = stream.readWord(numberFormat);
    stream.readSpace();
    string fifth = stream.readWord(numberFormat);
    return {first, second, third, forth, fifth};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    auto [ja, js, jm, jdiv, jmod] = readAns(ans);
    auto [pa, ps, pm, pdiv, pmod] = readAns(ouf);
    if (ja != pa)
        quitf(_wa, "Test %s: summ is incorrect: expected = %s, found = %s\n", argv[1], ja.c_str(), pa.c_str());
    else if (js != ps)
        quitf(_wa, "Test %s: difference is incorrect: expected = %s, found = %s\n", argv[1], js.c_str(), ps.c_str());
    else if (jm != pm)
        quitf(_wa, "Test %s: product is incorrect: expected = %s, found = %s\n", argv[1], jm.c_str(), pm.c_str());
    else if (jdiv != pdiv)
        quitf(_wa, "Test %s: div is incorrect: expected = %s, found = %s\n", argv[1], jdiv.c_str(), pdiv.c_str());
    else if (jmod != pmod)
        quitf(_wa, "Test %s: mod is incorrect: expected = %s, found = %s\n", argv[1], jmod.c_str(), pmod.c_str());
    else
        quitf(_ok, "Test %s: summ, difference, product and divmod are correct!", argv[1]);
}
