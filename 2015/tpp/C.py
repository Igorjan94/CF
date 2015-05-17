import re
n = int(input())
s = input()
print("YES" if len(s) >= n and re.search("^([a-z]|[A-Z]|[0-9])*$", s) != None and re.search("[a-z]", s) != None and re.search("[A-Z]", s) != None and re.search("[0-9]", s) != None else "NO")
