import sys
import re
file = open(sys.argv[1], 'r')
sys.stdout = open(sys.argv[2], 'w+')
xxx = sys.argv[2]
xxx = re.sub('.*\/', '', xxx)
xxx = re.sub('\..*', '', xxx)
print(xxx)
if len(sys.argv) > 3:
    flag = 1
else:
    flag = 0
Gatchina = 1
Ligovo = 1
Zele = 1
for str in file:
    if str != "":
        if str.find('Гатчина') == -1:
            Gatchina = 0
        if str.find('Лигово') == -1:
            Ligovo = 0
        if str.find('Зеленогорск') == -1:
            Zele = 0
file = open(sys.argv[1], 'r')
for str in file:

    str = str.replace('ежедневно', '')
    str = str.replace('по выходным', 'СВ')
    str = str.replace('по рабочим', 'КСВ')
    str = str.replace('по субботам', 'С')
    str = str.replace('по воскресеньям', 'В')
    str = str.replace('кроме пятн. и субб.', 'КПС')
    str = str.replace('кроме пятниц и вых.', 'КПСВ')
    str = str.replace('кроме воскресений', 'КВ')
    str = str.replace('по пятницам и выходным', 'ПСВ')

    str = re.sub(r'Санкт-Петербург-.*?(\s|$)', r'\1', str)


    if flag == 1:
        str = re.sub(r'(3|4)\d\sм', 'б/о', str)
        str = re.sub(r'.*2\sч.*', '', str)
        str = re.sub(r'.*1\sч\s\d{2}.*', '', str)
        str = re.sub(r'\d{1,2}\sм', '', str)
        str = re.sub(r'1\sч\s', '', str)
        if Zele == 1:
            str = str.replace('Зеленогорск', '')
        if Ligovo == 1:
            str = str.replace('Лигово', '')
        if Gatchina == 1:
            str = str.replace('Гатчина Балтийская', '')
            str = str.replace('Гатчина Варшавская', '')
        else:
            str = str.replace('Гатчина Балтийская', 'Г')
            str = str.replace('Гатчина Варшавская', 'Г')
        str = str.replace('Калище', '')
        str = str.replace('Лебяжье', '')
        str = str.replace('Ораниенбаум-1', '')
        str = str.replace('Новый Петергоф', '')

    str = re.sub(r'(\d{2})\s*\d{2}:\d{2}', r'\1', str)
    str = re.sub(r'б\/о\s+СВ', r'СВ,б/о', str)
    str = re.sub(r'(\s)+', r'	', str)
    str = re.sub(r'\s+$', r'', str)
    str = re.sub(r'^\s+', r'', str)
    if flag == 0:
        str = re.sub(r'(\d+)\sч\s*(.*)', r'\2	\1 ч', str)
        str = re.sub(r'(\d+)\sм\s*(.*)', r'\2	\1 м', str)
        str = re.sub(r'ч\s+', r'ч ', str)
    str = re.sub(r'(\d)\s+(\w{5,}|Г)', r'\1		\2', str)
    if str != "":
        print(str)
