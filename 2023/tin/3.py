# python 3.10
import itertools


ans = set()
chars = set()

def get(cc, s, i):
    if s:
        ans.add(s)
    if i == len(cc):
        return
    get(cc, s, i + 1)
    get(cc, s + cc[i], i + 1)


def find_combinations(text: str) -> list[str]:
    for c in text:
        chars.add(c)
    cc = list(chars)
    for xx in itertools.permutations(cc):
        get(xx, '', 0)
    return list(sorted(ans))


if __name__ == "__main__":
    input_str = input()
    # Необходимо преобразовать список в строку перед выводом. 
    print(', '.join(find_combinations(input_str)))
