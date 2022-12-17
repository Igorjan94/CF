from collections import defaultdict
import sys

q = int(sys.stdin.readline())
old = defaultdict(str)
new = defaultdict(str)
for i in range(q):
    a, b = sys.stdin.readline().split()
    if a in new.values():
        old[b] = old[a]
        new[old[a]] = b
    else:
        old[b] = a
        new[a] = b
sys.stdout.write(str(new.keys().__len__()) + "\n")
for x in new.keys():
    sys.stdout.write(x + " " + new[x] + "\n")



