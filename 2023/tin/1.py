
ttt = 'йцукенгшщзхъэждлорпавыфячсмитьбюё'
sss = 'ЙЦУКЕНГШЩЗХЪЭЖДЛОРПАВЫФЯЧСМИТЬБЮЁ'

def get(c):
    for i in range(33):
        if ttt[i] == c or sss[i] == c:
            return i
    return -1

def is_pangram(text: str) -> bool:
    a = [False] * 33
    for c in text:
        d = get(c)
        if d != -1:
            a[d] = True
    for i in range(33):
        if not a[i]:
            return False
    return True


if __name__ == "__main__":
    input_str = input()
    print(is_pangram(input_str))
