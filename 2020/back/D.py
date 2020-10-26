import json

n, m = map(int, input().split())
s = []
for i in range(n):
    s += json.loads(input())['offers']

s.sort(key = lambda x: (x['price'], x['offer_id']))
print(json.dumps({'offers': list(s)[:m]}))
