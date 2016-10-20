m = int(input())
money = list(map(int, input().split()))

mx = 0
lower = 500
for i in range(11):
    if money[i] <= m:
        for j in range(i + 1, 12):
            temp = (m // money[i]) * money[j] - (m // money[i]) * money[i]
            if temp > mx or temp == mx and lower > money[i]:
                mx = temp
                lower = money[i]
                I = i
                J = j

if mx <= 0:
    print("IMPOSSIBLE")
else:
    print(I + 1, J + 1, mx)
