from bs4 import BeautifulSoup
from urllib.request import urlopen
import re
import sys

def parse(url):
	html_doc = urlopen(url).read()
	soup = BeautifulSoup(html_doc)

	for entry in soup:
		lines = re.split('\n', str(entry))
		temp = 0
		for line in lines:
			line = re.sub(r'<a href=".*?">(.*?)</a>', r'\1', line)
			line = re.sub(r'^\s+(.*?)\s+</td>', r'\1', line)
			line = re.sub(r'$nbsp;', r' ', line)
			line = re.sub(r'<span class="miniNbsp">', r'', line)
			line = re.sub(r'</span>', r'', line)
			line = re.sub(r'^\s+(\d+.*?(м|ч).*?)', r'\1', line)
			line = re.sub(r'^[#a-zA-Z-<_\s$(.{}/].*', r' ', line)
			line = re.sub(r'^\s+', r'', line)
			if not line.startswith(' ') and not line.startswith('	') and not line == '':
				if temp == 0:
					cur = '		' + line
				else:
					cur = cur + '		' + line
				temp = temp + 1
			if temp == 6:
				temp = 0
				print(cur)
sys.stdout = open('/home/igorjan/documents/timetable/Ligovo-Tai.txt', 'w+')
parse('http://www.tutu.ru/spb/rasp.php?st1=701&st2=1201&print=yes')

sys.stdout = open('/home/igorjan/documents/timetable/Tai-Ligovo.txt', 'w+')
parse('http://www.tutu.ru/spb/rasp.php?st1=1201&st2=701&print=yes')

sys.stdout = open('/home/igorjan/documents/timetable/Ligovo-Spb.txt', 'w+')
parse('http://www.tutu.ru/spb/rasp.php?st1=701&st2=101&print=yes')

sys.stdout = open('/home/igorjan/documents/timetable/Spb-Ligovo.txt', 'w+')
parse('http://www.tutu.ru/spb/rasp.php?st1=101&st2=701&print=yes')

sys.stdout = open('/home/igorjan/documents/timetable/Spb-Zele.txt', 'w+')
parse('http://www.tutu.ru/spb/rasp.php?st1=20600&st2=41405&print=yes')

sys.stdout = open('/home/igorjan/documents/timetable/Zele-Spb.txt', 'w+')
parse('http://www.tutu.ru/spb/rasp.php?st1=41405&st2=20600&print=yes')
