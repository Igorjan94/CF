task = 'elephant'
f = open(task + '.in', 'r')
counts = {}
n = 0
fac = [1]
strings = f.readlines()
for s in strings:
    n += 1
    fac.append(fac[-1] * n)
    s = s[:-1]
    if not s in counts:
        counts[s] = 1
    else:
        counts[s] += 1

ans = fac[-1]
for x in counts:
    ans = ans // fac[counts[x]]

g = open(task + '.out', 'w')
g.write(strings[ans % n])
g.close()
f.close()
