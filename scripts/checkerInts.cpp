#include <testlib.h>
#include <bits/stdc++.h>

using namespace std;

string numberFormat = "-?[1-9][0-9]*|0";

string readAns(InStream& stream)
{
    return stream.readString(numberFormat);
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    auto ja = readAns(ans);
    auto pa = readAns(ouf);
    if (ja != pa)
        quitf(_wa, "Test %s: answer is incorrect: expected = %s, found = %s\n", argv[1], ja.c_str(), pa.c_str());
    else 
        quitf(_ok, "Test %s: answer is correct!", argv[1]);
}
