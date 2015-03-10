import sys
[a, b, t1, t2] = list(map(int, sys.stdin.readline().split()))
a = max(3 * a // 10, a - a // 250 * t1)
b = max(3 * b // 10, b - b // 250 * t2)
sys.stdout.write("Vasya" if a < b else ("Tie" if a == b else "Misha"))
