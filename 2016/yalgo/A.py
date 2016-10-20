import re
s = input()

c = re.sub(r'[aeiouy]', '', s)
v = re.sub(r'[^aeiouy]', '', s)
print('Vowel' if c < v else 'Consonant')
