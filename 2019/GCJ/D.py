import sys
import random

def randString(n):
    s = ['0'] * (n // 2) + ['1'] * ((n + 1) // 2)
    for i in range(n - 1, 0, -1):
        j = random.randint(0, i)
        s[i], s[j] = s[j], s[i]
    return s
    # return [chr(random.randint(48, 49)) for i in range(n)]

def main():
    n, b, f = map(int, input().split())
    # sys.stderr.write(str(n) + " " + str(b) + " " + str(f) + "\n")
    s = [randString(n) for i in range(f)]
    t = [''] * f
    for i in range(f):
        print(''.join(s[i]))
        # sys.stderr.write(''.join(s[i]) + '\n')
        sys.stdout.flush()
        t[i] = input()

    ans = []
    i = 0
    for j in range(n - b):
        while True:
            ok = True
            for k in range(f):
                ok = ok and (s[k][i] == t[k][j])
            i += 1
            if ok:
                break
            ans += [i - 1]
    while i < n:
        i += 1
        ans += [i - 1]

    print(' '.join(map(str, ans)))
    # sys.stderr.write(' '.join(map(str, ans)) + '\n')
    sys.stdout.flush()
    # s = input()
    if input() == "-1":
        sys.stderr.write("WA\n")

random.seed(100000007)
for t in range(int(input())):
    main()
