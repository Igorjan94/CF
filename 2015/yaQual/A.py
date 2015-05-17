strings = input().split()
input()
corr = input().split()
count = 0
for s in strings:
    if not s in corr:
        count += 1
print("Correct" if count == 0 else "Misspell")
