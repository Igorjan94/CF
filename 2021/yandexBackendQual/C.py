def read():
    return list(map(int, input().split()))

def get(a):
    return '.'.join(map(str, a))

[n, m] = read()
[w] = read()
whites = [read() for i in range(w)]
[b] = read()
blacks = [read() for i in range(b)]
who = input()
if who == 'black':
    whites, blacks = blacks, whites
    w, b = b, w

bb = set(map(get, blacks))
ww = set(map(get, whites))
can = False

def exists(x, y):
    return x >= 1 and y >= 1 and x <= n and y <= m

dx = [1, 1, -1, -1]
dy = [-1, 1, 1, -1]
for i in range(w):
    x, y = whites[i]
    for q in range(4):
        u = x + dx[q]
        v = y + dy[q]
        uu = u + dx[q]
        vv = v + dy[q]

        if exists(u, v) and exists(uu, vv):
            uuvv = get([uu, vv])
            if get([u, v]) in bb and not uuvv in bb and not uuvv in ww:
                can = True


if can:
    print('Yes')
else:
    print('No')
