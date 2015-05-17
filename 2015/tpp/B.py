s = input()
t = "1" * 4
if len(s) == 80 and (s[:4] == t) ^ (s[-4:] == t):
    print(s if s[:4] == t else s[::-1])
else:
    print("0" * 80)
