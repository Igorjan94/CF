import sys

def fromChar(c):
    if ord(c) < 65:
        return ord(c) - 48
    else:
        return ord(c) - 65 + 10

def cmp(s, t):
    ls = len(s)
    lt = len(t)
    if ls < lt:
        return True
    if ls > lt:
        return False
    for i in range(ls - 1, -1, -1):
        if s[i] < t[i]:
            return True
    return False

def get(s, t, b):
    vs = s[1:]
    vt = t[1:]
    if s[0] == t[0]:
        return [s[0]] + add(vs, vt, b)
    elif s[0] == '-':
        return sub(vt, vs, b)
    else:
        return sub(vs, vt, b)

def add(s, t, b):
    # print('ADD', s, t, b)
    ls = len(s)
    lt = len(t)
    ans = []
    carry = 0
    for i in range(max(ls, lt)):
        l = 0 if i >= ls else s[i]
        r = 0 if i >= lt else t[i]
        c = carry + l + r
        ans.append(c % b)
        carry = c // b
    if carry != 0:
        ans.append(carry)
    # print('RES', ans)
    return ans

def sub(s, t, b):
    # print('SUB', s, t, b)
    ans = ['+']
    if cmp(s, t):
        ans = ['-']
        s, t = t, s
    ls = len(s)
    lt = len(t)

    for i in range(max(ls, lt)):
        l = 0 if i >= ls else s[i]
        r = 0 if i >= lt else t[i]
        c = l - r
        if c < 0:
            s[i + 1] -= 1
            c += b
        ans.append(c)
    while len(ans) > 2 and ans[-1] == 0:
        ans.pop()

    # print('RES', ans)
    return ans


def calc(s, b):
    res = [['+', 0]]
    nxt = ['+']
    s += '+'
    for c in s:
        if c == '+' or c == '-':
            res.append([nxt[0]] + nxt[:0:-1])
            nxt = [c]
        else:
            cur = fromChar(c)
            if cur >= b:
                return False
            nxt.append(cur)
    # res.sort()
    for i in range(1, len(res)):
        res[0] = get(res[0], res[i], b)
    return res[0]

l, r = input().replace(' ', '').split('=')
for b in range(2, 27 + 10):
    ll = calc(l, b)
    rr = calc(r, b)
    # print(b, ll, rr)
    if ll and rr and ll == rr:
        print(b)
        sys.exit()
print(-1)
