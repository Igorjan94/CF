
# python 3.10


def get_answer_mask(text: str) -> list[int]:
    got, ans = text.split(', ')
    ret = [0] * 5
    s = set()
    for i in range(5):
        if got[i] == ans[i]:
            ret[i] = 1
            s.add(got[i])
        elif got[i] in ans and not got[i] in s:
            ret[i] = 0
            s.add(got[i])
        else:
            ret[i] = -1
    return ret


if __name__ == "__main__":
    input_str = input()
    # Необходимо преобразовать список в строку перед выводом.
    print(', '.join(map(str, get_answer_mask(input_str))))
