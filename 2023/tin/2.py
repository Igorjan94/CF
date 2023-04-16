
# python 3.10

m = {
    'РҐ': 'Х',
    'Рѕ': 'а',
    'С‰': 'к',
    'Сѓ': 'е',
    'СЏ': 'р',
    'СЋ': 'п',
    'СЉ': 'л',
    'РЅ': 'я',
    'Р¶': 'ш',
    'Р±': 'т',
    'С‘': 'ч',
    'С€': 'й',
    'СЊ': 'н',
    'С‡': 'и'
}

def decrypt(text: str) -> str:
    l = len(text)
    ret = ''
    p = ''
    for i in range(l):
        c = text[i]
        if c in [' ', ',', '.']:
            ret += c
        else:
            if p == '':
                p = c
            else:
                ret += m[p + c]
                p = ''
    return ret

if __name__ == "__main__":
    input_str = input()
    print(decrypt(input_str))
