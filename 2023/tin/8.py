
# python 3.10
import re


def find_ban_words(text: str) -> list[str]:
    ret = set()
    for c in ['чай', 'чая', 'чаю', 'чаи', 'чае', 'чайный', 'чайного', 'чайному', 'чайным', 'чайном']:
        if c in text:
            ret.add('чай')
    if re.match(r'.*горячий .*кофе.*', text):
        ret.add('горячий кофе')
    if re.match(r'.*горячего .*кофе.*', text):
        ret.add('горячий кофе')
    if re.match(r'.*горячему .*кофе.*', text):
        ret.add('горячий кофе')
    if re.match(r'.*горячим .*кофе.*', text):
        ret.add('горячий кофе')
    if re.match(r'.*горячем .*кофе.*', text):
        ret.add('горячий кофе')
    return list(sorted(ret))


if __name__ == "__main__":
    input_str = input()
    # Необходимо преобразовать список в строку перед выводом.
    print(', '.join(find_ban_words(input_str)))
