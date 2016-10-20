import sys

n = int(input())
strings = input().split()
r = []
b = []
for s in strings:
    color = s[-1]
    s = int(s[:-1])
    r.append(s) if color == 'R' else b.append(s)

if len(r) == 0 or len(b) == 0:
    print(0)
    sys.exit()

def part(a):
    a[0] = (a[0], a[0])
    for i in range(1, len(a)):
        a[i] = (a[i], a[i - 1][1] + a[i])
    return a

r = part(list(reversed(sorted(r))))
b = part(list(reversed(sorted(b))))

l = min(len(r), len(b))
print(r[l - 1][1] + b[l - 1][1] - l * 2)
