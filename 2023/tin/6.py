# python 3.10


def compress_sequence(text: str) -> list[tuple[int, int]]:
    i = 0
    a = list(map(int, text.split(', ')))
    n = len(a)
    ans = []
    while i < n:
        j = i
        c = 0
        while j < n and a[i] == a[j]:
            j += 1
            c += 1

        ans.append((a[i], c))
        i = j
    return ans


if __name__ == "__main__":
    input_str = input()
    # Необходимо преобразовать список в строку перед выводом.
    print(', '.join(map(str, compress_sequence(input_str))))

