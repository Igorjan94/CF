import re

t = int(input())
for i in range(t):
    n = input()
    s = input().lower()
    print('YES' if re.match(r'^m+e+o+w+$', s) else 'NO')
