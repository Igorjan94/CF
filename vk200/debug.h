#ifndef DEBUG_H
#define DEBUG_H


#include "includes.h"
#include "message.h"

using namespace std;

ostream& operator<<(ostream& os, qs s) { return os << s.toStdString(); }
ostream& operator<<(ostream& os, message& m) { return os << qs(m); }

void writeln() { cout << "\n"; }
template<typename Head, typename... Tail>
void writeln (Head head, Tail... tail)
{
    cout << head << " ";
    cout.flush();
    writeln(tail...);
}

void error(qs reason)
{
    cout << "Fatal error occured:\n\t" << reason << "\n";
    exit(1);
}

#endif // DEBUG_H
