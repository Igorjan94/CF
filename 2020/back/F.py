import requests

url = input()
port = input()
a = input()
b = input()

res = list(reversed(sorted(requests.get(''.join([url, ':', port, '?', 'a=', a, '&b=', b])).json())))
for i in range(len(res)):
    print(res[i])
