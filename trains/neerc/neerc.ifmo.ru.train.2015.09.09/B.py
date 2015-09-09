import re
import sys

f = open("input.txt", "r")
w = open("output.txt", "w")
s = f.readline()[:-1]

ans = 1234123412341234
if re.sub(r"[<>\"\'&]", "", s) == s:
    w.write("-1")
else:
    if re.sub(r"[<>\"\']", "", s) != s:
        w.write("0")
    else:
        s = s.split('&')[1:]
        for t in s:
            temp = 0
            while t.startswith('amp;'):
                t = t[t.find(';') + 1:]
                temp += 1
            if t.startswith('gt;') or t.startswith('lt;') or t.startswith('apos;') or t.startswith('quot;'):
                temp += 1
            ans = min(ans, temp)

        w.write(str(ans))
