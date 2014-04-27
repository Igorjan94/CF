import std.algorithm, std.stdio;

void main()
{
    int ok = 0, ok1 = 0, ok2 = 0, ok3 = 0;
    string s;
    readf("%s", &s);
    int length = s.length;
    for (int i = 0; i < s.length; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z')
            ok = 1;
        if (s[i] >= 'A' && s[i] <= 'Z')
            ok1 = 1;
        if (s[i] >= '0' && s[i] <= '9')
            ok2 = 1;
        if (s[i] == '\n')
        {
            length = i;
            break;
        }
    }
    if (length >= 5)
        ok3 = 1;
    writeln((ok + ok1 + ok2 + ok3 == 4) ? "Correct" : "Too weak");
}
