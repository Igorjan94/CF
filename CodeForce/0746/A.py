a = int(input())
b = int(input())
c = int(input())
x = 0

for i in range(a + 1):
    if i * 2 <= b and i * 4 <= c:
        x = i

print(x * 7)
