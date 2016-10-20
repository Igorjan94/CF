from decimal import *

n, k = list(map(int, input().split()))
getcontext().prec = k + 10
getcontext().rounding = ROUND_FLOOR

print(Decimal(n).sqrt())


