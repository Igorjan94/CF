import sys
import collections
import re

def get(s):
    m = collections.defaultdict(lambda: 0)
    for c in re.sub(f'[^\w]', '', s.lower()):
        m[c] += 1
    return m

def output(f):
    for k in sorted(f.keys()):
        if f[k] != 0:
            print(k, f[k])
    print("==========================")

def sub(f, t):
    ans = collections.defaultdict(lambda: 0)
    for k in f:
        ans[k] = f[k]
    for k in t:
        ans[k] -= t[k]
    return ans

d = get(open("./dict.txt").readline()[:-1])
output(d)
for s in sys.stdin:
    output(sub(d, get(s[:-1])))
