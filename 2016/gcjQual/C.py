import math
import sys

print("Case #1:")
input()
n, J = map(int, input().split())
n -= 1
d = 2 ** n

def f(x):
    return d + x * 2 + 1

N = 1000000
prime = [-1] * N
prime[2] = -1
primes = [-1] * N
count = 0
for i in range(2, N):
    if prime[i] == -1:
        primes[count] = i
        count += 1
        for j in range(i * i, N, i):
            prime[j] = i

def isNotPrime(x):
    if x >= N:
        s = int(math.sqrt(x) + 2)
        for qq in range(count):
            y = primes[qq]
            if x % y == 0:
                return y
            if y > s:
                return -1
        return -1
    return prime[x]

c = 0
i = 0
while c < J:
    divs = []
    x = str(bin(f(i)))[2:]
    ok = True
    for q in range(2, 11):
        divs.append(str(isNotPrime(int(x, q))))
        ok = ok and divs[-1] != '-1'
    if ok:
        c += 1
        print(c, x, ' '.join(divs))
        sys.stderr.write(str(c) + ' ' + str(x) + '\n')
    i += 1
