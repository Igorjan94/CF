#
# Implement function get_result
#

def orientation(ax, ay, bx, by, cx, cy):
    return ax*by-ay*bx-ax*cy+ay*cx+bx*cy-by*cx
def get(x):
    if x >= 0:
        return 1
    return -1
def get_result(a):
    n = len(a)
    used = [0 for i in range(n)]
    ans = 0
    for i in range(0, n, 2):
        if used[i] == 1:
            continue
        used[i] = 1
        ans += 1
        for j in range(i, n, 2):
            if used[j] == 1:
                continue

            bx = get(a[i])
            by = get(a[i + 1])
            cx = get(a[j])
            cy = get(a[j + 1])
            if bx == cx and by == cy and orientation(0, 0, a[i], a[i + 1], a[j], a[j + 1]) == 0:
                used[j] = 1

    return ans

print(get_result([2, 2, -2, 2, -2, -2, 2, -2]))
print(get_result([2,2,-2,2,-2,-2,2,-2,1,1,-1,3]))
