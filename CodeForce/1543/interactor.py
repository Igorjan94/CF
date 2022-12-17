import random
import sys

n = 100
x = random.randint(0, n - 1)
t = 100
print(t)
for i in range(t):
    print(n, 2)
    steps = 0
    while True:
        steps += 1
        y = int(input())
        if x == y:
            print(1)
            if steps > n:
                sys.exit(10)
            break
        else:
            x ^= y
            print(0)
            sys.stdout.flush()

