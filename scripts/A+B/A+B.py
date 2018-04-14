a, b = map(int, input().split())
print(a + b)
print(a - b)
print(a * b)
if a >= 0 and b >= 0:
    print(a // b, a % b)
elif a >= 0 and b <= 0:
    print(-(a // abs(b)), a % abs(b))
elif a <= 0 and b >= 2:
    print(a // b + 1, -(abs(a) % b))
elif a <= 0 and b <= 1: # -1 1 case is here!
    print(a // b, a % b)
