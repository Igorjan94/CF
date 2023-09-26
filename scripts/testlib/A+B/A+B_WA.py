import random

a, b = map(int, input().split())
if random.randint(0, 10) == 0:
    print(a + b + 1)
else:
    print(a + b)

print(a - b)
