t = int(input())
for q in range(t):
    h, n = map(int, input().split())
    ans = 0.0
    for s in input().split():
        z = 0
        a = s.split('+')
        if len(a) == 2:
            z = int(a[1])
            s = a[0]
        else:
            a = s.split('-')
            if len(a) == 2:
                z = -int(a[1])
                s = a[0]
        x, y = map(int, s.split('d'))

        l = x * y + 1
        res = [0] * l
        res[0] = 1
        for i in range(x):
            nex = [0] * l
            for j in range(l - y):
                if res[j] > 0:
                    for k in range(1, y + 1):
                        nex[j + k] += res[j]
            res = nex
        ok = sum(res)
        d = 0
        for i in range(l):
            if i + z >= h:
                d += res[i]
        ans = max(ans, d / ok)


    print("Case #{:d}: {:.10f}".format(q + 1, ans))
